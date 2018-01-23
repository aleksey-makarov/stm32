#include <stdint.h>
#include "rcc.h"

/* FIXME: bit banging */

#define I2C_CR1_PE		(1 << 0)
#define I2C_CR1_SMBUS		(1 << 1)
#define I2C_CR1_SMBTYPE		(1 << 3)
#define I2C_CR1_ENARP		(1 << 4)
#define I2C_CR1_ENPEC		(1 << 5)
#define I2C_CR1_ENGC		(1 << 6)
#define I2C_CR1_NO_STRETCH	(1 << 7)
#define I2C_CR1_START		(1 << 8)
#define I2C_CR1_STOP		(1 << 9)
#define I2C_CR1_ACK		(1 << 10)
#define I2C_CR1_POS		(1 << 11)
#define I2C_CR1_PEC		(1 << 12)
#define I2C_CR1_ALERT		(1 << 13)
#define I2C_CR1_SWRST		(1 << 15)

#define I2C_CR2_FREQ_SHIFT	0
#define I2C_CR2_ITERREN		(1 << 8)
#define I2C_CR2_ITEVTEN		(1 << 9)
#define I2C_CR2_ITBUFEN		(1 << 10)
#define I2C_CR2_DMAEN		(1 << 11)
#define I2C_CR2_LAST		(1 << 12)

#define I2C_CCR_CCR_SHIFT	0
#define I2C_CCR_DUTY		(1 << 14)
#define I2C_CCR_FS		(1 << 15)

#define I2C_SR1_SB		(1 << 0)
#define I2C_SR1_ADDR		(1 << 1)
#define I2C_SR1_BTF		(1 << 2)
#define I2C_SR1_ADD10		(1 << 3)
#define I2C_SR1_STOPF		(1 << 4)
#define I2C_SR1_RxNE		(1 << 6)
#define I2C_SR1_TxE		(1 << 7)
#define I2C_SR1_BERR		(1 << 8)
#define I2C_SR1_ARLO		(1 << 9)
#define I2C_SR1_AF		(1 << 10)
#define I2C_SR1_OVR		(1 << 11)
#define I2C_SR1_PEC_ERR		(1 << 12)
#define I2C_SR1_TIME_OUT	(1 << 14)
#define I2C_SR1_SMB_ALERT	(1 << 15)

struct I2C {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
};

struct I2C_BB {
	volatile uint32_t CR1[32];
	volatile uint32_t CR2[32];
	volatile uint32_t OAR1[32];
	volatile uint32_t OAR2[32];
	volatile uint32_t DR[32];
	volatile uint32_t SR1[32];
	volatile uint32_t SR2[32];
	volatile uint32_t CCR[32];
	volatile uint32_t TRISE[32];
};

#define I2C1    ((struct I2C *)0x40005400)
#define I2C2    ((struct I2C *)0x40005800)
#define I2C1_BB ((struct I2C_BB *)0x420A8000)
#define I2C2_BB ((struct I2C_BB *)0x420B0000)

#define I2C_DUTYCYCLE_2		0
#define I2C_DUTYCYCLE_16_9	I2C_CCR_DUTY

#define I2C_CCR_CCR		0xfff

#define I2C_FREQRANGE(__PCLK__) \
	((__PCLK__)/1000000U)
#define I2C_RISE_TIME(__FREQRANGE__, __SPEED__) \
	(((__SPEED__) <= 100000U) ? ((__FREQRANGE__) + 1U) : ((((__FREQRANGE__) * 300U) / 1000U) + 1U))
#define I2C_SPEED_STANDARD(__PCLK__, __SPEED__) \
	(((((__PCLK__)/((__SPEED__) << 1U)) & I2C_CCR_CCR) < 4U)? 4U:((__PCLK__) / ((__SPEED__) << 1U)))
#define I2C_SPEED_FAST(__PCLK__, __SPEED__, __DUTYCYCLE__) \
	(((__DUTYCYCLE__) == I2C_DUTYCYCLE_2)? ((__PCLK__) / ((__SPEED__) * 3U)) : (((__PCLK__) / ((__SPEED__) * 25U)) | I2C_DUTYCYCLE_16_9))
#define I2C_SPEED(__PCLK__, __SPEED__, __DUTYCYCLE__) \
	(((__SPEED__) <= 100000U)? (I2C_SPEED_STANDARD((__PCLK__), (__SPEED__))) : \
	((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__)) & I2C_CCR_CCR) == 0U)? 1U : \
	((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__))) | I2C_CCR_FS))

#define I2C_FREQ  50000

void i2c_init(void)
{
	I2C1->CR2 = I2C_FREQRANGE(RCC_APB1_FREQ);
	I2C1->TRISE = I2C_RISE_TIME(I2C_FREQRANGE(RCC_APB1_FREQ), I2C_FREQ);
	I2C1->CCR = I2C_SPEED(RCC_APB1_FREQ, I2C_FREQ, I2C_DUTYCYCLE_2);

	I2C1->CR1 |= I2C_CR1_PE;
}

#define I2C_ADDR_READ(addr)	((addr << 1) | 1)
#define I2C_ADDR_WRITE(addr)	(addr << 1)

#define TIMEOUT 1000000

#define WAIT_FOR(x) \
	for (i = 0; !(x); i++) \
		if (i > TIMEOUT)

int i2c_write(uint8_t address, uint8_t *values, unsigned long values_length)
{
	unsigned long i;

	I2C1->CR1 |= I2C_CR1_START;
	WAIT_FOR(I2C1->SR1 & I2C_SR1_SB) {
		return -1;
	}

	I2C1->DR = I2C_ADDR_WRITE(address);
	WAIT_FOR(I2C1->SR1 & I2C_SR1_ADDR) {
		return -1;
	}
	I2C1->SR2;

	for (; values_length; values_length--, values++) {
		WAIT_FOR(I2C1->SR1 & I2C_SR1_TxE) {
			return -1;
		}
		I2C1->DR = *values;
	}

	WAIT_FOR((I2C1->SR1 & I2C_SR1_TxE) && (I2C1->SR1 & I2C_SR1_BTF)) {
		return -1;
	}

	I2C1->CR1 |= I2C_CR1_STOP;

	return 0;
}
