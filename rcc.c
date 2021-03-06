#include "rcc.h"
#include <stdint.h>

struct RCC {
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
};

struct RCC_BB {
	volatile uint32_t CR[32];
	volatile uint32_t CFGR[32];
	volatile uint32_t CIR[32];
	volatile uint32_t APB2RSTR[32];
	volatile uint32_t APB1RSTR[32];
	volatile uint32_t AHBENR[32];
	volatile uint32_t APB2ENR[32];
	volatile uint32_t APB1ENR[32];
	volatile uint32_t BDCR[32];
	volatile uint32_t CSR[32];
};

struct FLASH {
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t AR;
	volatile uint32_t RESERVED_1;
	volatile uint32_t OBR;
	volatile uint32_t WRPR;
};

struct FLASH_BB {
	volatile uint32_t ACR[32];
	volatile uint32_t KEYR[32];
	volatile uint32_t OPTKEYR[32];
	volatile uint32_t SR[32];
	volatile uint32_t CR[32];
	volatile uint32_t AR[32];
	volatile uint32_t RESERVED_1[32];
	volatile uint32_t OBR[32];
	volatile uint32_t WRPR[32];
};

#define RCC		((struct RCC *)0x40021000)
#define RCC_BB		((struct RCC_BB *)0x42420000)
#define FLASH		((struct FLASH *)0x40022000)
#define FLASH_BB	((struct FLASH_BB *)0x42440000)

#define RCC_CR_HSION		(1 << 0)
#define RCC_CR_HSIRDY		(1 << 1)
#define RCC_CR_HSITRIM_SHIFT	3
#define RCC_CR_HSICAL_SHIFT	8
#define RCC_CR_HSEON		(1 << 16)
#define RCC_CR_HSERDY		(1 << 17)
#define RCC_CR_HSEBYP		(1 << 18)
#define RCC_CR_CSSON		(1 << 19)
#define RCC_CR_PLLON		(1 << 24)
#define RCC_CR_PLLRDY		(1 << 25)
#define RCC_CR_PLL2ON		(1 << 26)
#define RCC_CR_PLL2RDY		(1 << 27)
#define RCC_CR_PLL3ON		(1 << 28)
#define RCC_CR_PLL3RDY		(1 << 29)

#define RCC_CFGR_SW_SHIFT	0
#define  RCC_CFGR_SW_HSI	(0 << RCC_CFGR_SW_SHIFT)
#define  RCC_CFGR_SW_HSE	(1 << RCC_CFGR_SW_SHIFT)
#define  RCC_CFGR_SW_PLL	(2 << RCC_CFGR_SW_SHIFT)
#define RCC_CFGR_SWS_SHIFT	2
#define RCC_CFGR_HPRE_SHIFT	4
#define RCC_CFGR_PPRE1_SHIFT	8
#define  RCC_CFGR_PPRE1_div2	(4 << RCC_CFGR_PPRE1_SHIFT)
#define RCC_CFGR_PPRE2_SHIFT	11
#define RCC_CFGR_ADC_PRE_SHIFT	14
#define RCC_CFGR_PLL_SRC	(1 << 16)
#define RCC_CFGR_PLL_XTPRE	(1 << 17)
#define RCC_CFGR_PLLMUL_SHIFT	18
#define  RCC_CFGR_PLLMUL_x9	(7 << RCC_CFGR_PLLMUL_SHIFT)
#define RCC_CFGR_OTGFS_PRE	(1 << 22)
#define RCC_CFGR_MCO_SHIFT	24

#define RCC_APB2ENR_AFIOEN 	(1 << 0)
#define RCC_APB2ENR_IOPAEN 	(1 << 2)
#define RCC_APB2ENR_IOPBEN 	(1 << 3)
#define RCC_APB2ENR_IOPCEN 	(1 << 4)
#define RCC_APB2ENR_IOPDEN 	(1 << 5)
#define RCC_APB2ENR_IOPEEN 	(1 << 6)
#define RCC_APB2ENR_ADC1EN 	(1 << 9)
#define RCC_APB2ENR_ADC2EN 	(1 << 10)
#define RCC_APB2ENR_TIM1EN 	(1 << 11)
#define RCC_APB2ENR_SPI1EN 	(1 << 12)
#define RCC_APB2ENR_USART1EN 	(1 << 14)

#define RCC_APB1ENR_TIM2EN 	(1 << 0)
#define RCC_APB1ENR_TIM3EN 	(1 << 1)
#define RCC_APB1ENR_TIM4EN 	(1 << 2)
#define RCC_APB1ENR_TIM5EN 	(1 << 3)
#define RCC_APB1ENR_TIM6EN 	(1 << 4)
#define RCC_APB1ENR_TIM7EN 	(1 << 5)
#define RCC_APB1ENR_WWDGEN 	(1 << 11)
#define RCC_APB1ENR_SPI2EN 	(1 << 14)
#define RCC_APB1ENR_SPI3EN 	(1 << 15)
#define RCC_APB1ENR_USART2EN 	(1 << 17)
#define RCC_APB1ENR_USART3EN 	(1 << 18)
#define RCC_APB1ENR_UART4EN 	(1 << 19)
#define RCC_APB1ENR_UART5EN 	(1 << 20)
#define RCC_APB1ENR_I2C1EN 	(1 << 21)
#define RCC_APB1ENR_I2C2EN 	(1 << 22)
#define RCC_APB1ENR_CAN1EN 	(1 << 25)
#define RCC_APB1ENR_CAN2EN 	(1 << 26)
#define RCC_APB1ENR_BKPEN 	(1 << 27)
#define RCC_APB1ENR_PWREN 	(1 << 28)
#define RCC_APB1ENR_DACEN 	(1 << 29)

#define FLASH_ACR_LATENCY_SHIFT	0
#define FLASH_ACR_HLFCYA	(1 << 3)
#define FLASH_ACR_PRFTBE	(1 << 4)
#define FLASH_ACR_PRFTBS	(1 << 5)

void rcc_init(void)
{
	RCC->CFGR = RCC_CFGR_PLL_SRC | RCC_CFGR_PLLMUL_x9 | RCC_CFGR_SW_HSI | RCC_CFGR_PPRE1_div2;
	RCC->CR = RCC_CR_HSION | RCC_CR_HSEON | (0x10 << RCC_CR_HSITRIM_SHIFT) | RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY))
		;
	FLASH->ACR = FLASH_ACR_PRFTBE | (2 << FLASH_ACR_LATENCY_SHIFT);
	RCC->CFGR = RCC_CFGR_PLL_SRC | RCC_CFGR_PLLMUL_x9 | RCC_CFGR_SW_PLL | RCC_CFGR_PPRE1_div2;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN |
			RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN |
			RCC_APB2ENR_USART1EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_I2C1EN;
}
