// SPDX-License-Identifier: MIT

#include "regs.h"
#include "i2c.h"
#include <stdio.h>
#include "mtrace.h"
#include "rcc.h"

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

/* FIXME: bit banging */

#define I2C_ADDR_READ(addr)	((addr << 1) | 1) 
#define I2C_ADDR_WRITE(addr)	(addr << 1) 

#define TIMEOUT 1000000

#define WAIT_FOR(x) \
	for (i = 0; !(x); i++) \
		if (i > TIMEOUT)

static int write_register(uint8_t address, uint8_t reg, uint8_t v)
{
	int i;

	MTRACE("+ address: 0x%02x, reg: 0x%02x, v: 0x%02x", (unsigned int)address, (unsigned int)reg, (unsigned int)v);

	I2C1->CR1 |= I2C_CR1_START;
	WAIT_FOR(I2C1->SR1 & I2C_SR1_SB) {
		MTRACE("!");
		return -1;
	}

	I2C1->DR = I2C_ADDR_WRITE(address);
	WAIT_FOR(I2C1->SR1 & I2C_SR1_ADDR) {
		MTRACE("!");
		return -1;
	}
	I2C1->SR2;

	WAIT_FOR(I2C1->SR1 & I2C_SR1_TxE) {
		MTRACE("!");
		return -1;
	}

	I2C1->DR = reg;

	WAIT_FOR(I2C1->SR1 & I2C_SR1_TxE) {
		MTRACE("! SR1: 0x%08lx", I2C1->SR1);
		return -1;
	}

	I2C1->DR = v;

	WAIT_FOR((I2C1->SR1 & I2C_SR1_TxE) && (I2C1->SR1 & I2C_SR1_BTF)) {
		MTRACE("!");
		return -1;
	}

	I2C1->CR1 |= I2C_CR1_STOP;

	MTRACE("-");
	return 0;
}

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

static int test_address(uint8_t address)
{
	int err;
	int i;

	MTRACE("+ 0x%02x", address);

	MTRACE("reset i2c");
	I2C1->CR1 |= I2C_CR1_SWRST;
	for (i = 0; i < TIMEOUT; i++)
		;
	I2C1->CR1 &= ~I2C_CR1_SWRST;

	MTRACE("initialize i2c");
	I2C1->CR2 = I2C_FREQRANGE(RCC_APB1_FREQ);
	I2C1->TRISE = I2C_RISE_TIME(I2C_FREQRANGE(RCC_APB1_FREQ), I2C_FREQ);
	I2C1->CCR = I2C_SPEED(RCC_APB1_FREQ, I2C_FREQ, I2C_DUTYCYCLE_2);

	MTRACE("enable i2c");
	I2C1->CR1 |= I2C_CR1_PE;

	err = write_register(address, 0, 0xae);

	MTRACE("disable i2c");
	I2C1->CR1 &= ~I2C_CR1_PE;

	MTRACE("%c", err ? '!' : '-');
	return err;
}

int main(void)
{
	MTRACE("- %s", __TIMESTAMP__);

	test_address(0x3c);

	MTRACE("-");
	return 0;
}
