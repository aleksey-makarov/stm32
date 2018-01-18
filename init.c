// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2017 Andrea Loi                                                *
 */

#include "regs.h"

void reset_handler(void); // This is the first function to be executed.
extern int main(void);   // ResetHandler will call main after initialization.

void halt(void) __attribute__ ((noreturn));
void halt(void)
{
	for(;;) {}
}

// *****************************************************************************
// * Define what to do if the cpu receives an interrupt for a peripheral that  *
// * doesn't exist. This doesn't make sense and it should never happen.        *
// *****************************************************************************
#define ISR_NOT_IMPL ((uint32_t *) halt)

// *****************************************************************************
// * Define the default interrupt function.                                    *
// *****************************************************************************
#define ISR_NOT_SET ((uint32_t *) halt)

// *****************************************************************************
// * Define where the stack starts.                                            *
// * ARM Cortex-M CPUs use a Full Descending stack, meaning the stack starts   *
// * at the end of the RAM and grows towards the beginning of the RAM.         *
// * An STM32F103C8 has 20KB of RAM, from 0x20000000 to 0x20004FFF.            *
// * The stack bottom is set to 0x20005000 because the SP register is          *
// * decremented BEFORE storing a value, therefore the first byte pushed to    *
// * the stack will be at address 0x20004FFF.                                  *
// *****************************************************************************
#define STACK_START_ADDR 0x20005000

// *****************************************************************************
// * Set the vector table and store it in the .isrvectors section.             *
// *****************************************************************************
uint32_t (* const vectortable[]) __attribute__ ((section(".isrvectors"))) = {
  /* Function Pointer                  Name              Addr    IRQn  EXn */
  (uint32_t *) STACK_START_ADDR,    /* SP                0x0000  N/A   N/A */
  (uint32_t *) reset_handler,       /* Reset             0x0004  N/A     1 */
  ISR_NOT_SET,                      /* NMI               0x0008  -14     2 */
  ISR_NOT_SET,                      /* HardFault         0x000C  -13     3 */
  ISR_NOT_SET,                      /* MemManage         0x0010  -12     4 */
  ISR_NOT_SET,                      /* BusFault          0x0014  -11     5 */
  ISR_NOT_SET,                      /* UsageFault        0x0018  -10     6 */
  ISR_NOT_IMPL,                     /* Reserved          0x001C   -9     7 */
  ISR_NOT_IMPL,                     /* Reserved          0x0020   -8     8 */
  ISR_NOT_IMPL,                     /* Reserved          0x0024   -7     9 */
  ISR_NOT_IMPL,                     /* Reserved          0x0028   -6    10 */
  ISR_NOT_SET,                      /* SVCall            0x002C   -5    11 */
  ISR_NOT_SET,                      /* DebugMonitor      0x0030   -4    12 */
  ISR_NOT_IMPL,                     /* Reserved          0x0034   -3    13 */
  ISR_NOT_SET,                      /* PendSV            0x0038   -2    14 */
  ISR_NOT_SET,                      /* SysTick           0x003C   -1    15 */
  ISR_NOT_SET,                      /* WWDG              0x0040    0    16 */
  ISR_NOT_SET,                      /* PVD               0x0044    1    17 */
  ISR_NOT_SET,                      /* TAMPER            0x0048    2    18 */
  ISR_NOT_SET,                      /* RTC               0x004C    3    19 */
  ISR_NOT_SET,                      /* FLASH             0x0050    4    20 */
  ISR_NOT_SET,                      /* RCC               0x0054    5    21 */
  ISR_NOT_SET,                      /* EXTI0             0x0058    6    22 */
  ISR_NOT_SET,                      /* EXTI1             0x005C    7    23 */
  ISR_NOT_SET,                      /* EXTI2             0x0060    8    24 */
  ISR_NOT_SET,                      /* EXTI3             0x0064    9    25 */
  ISR_NOT_SET,                      /* EXTI4             0x0068   10    26 */
  ISR_NOT_SET,                      /* DMA1_Channel1     0x006C   11    27 */
  ISR_NOT_SET,                      /* DMA1_Channel2     0x0070   12    28 */
  ISR_NOT_SET,                      /* DMA1_Channel3     0x0074   13    29 */
  ISR_NOT_SET,                      /* DMA1_Channel4     0x0078   14    30 */
  ISR_NOT_SET,                      /* DMA1_Channel5     0x007C   15    31 */
  ISR_NOT_SET,                      /* DMA1_Channel6     0x0080   16    32 */
  ISR_NOT_SET,                      /* DMA1_Channel7     0x0084   17    33 */
  ISR_NOT_SET,                      /* ADC1_2            0x0088   18    34 */
  ISR_NOT_SET,                      /* USB_HP_CAN_TX     0x008C   19    35 */
  ISR_NOT_SET,                      /* USB_LP_CAN_RX0    0x0090   20    36 */
  ISR_NOT_SET,                      /* CAN_RX1           0x0094   21    37 */
  ISR_NOT_SET,                      /* CAN_SCE           0x0098   22    38 */
  ISR_NOT_SET,                      /* EXTI9_5           0x009C   23    39 */
  ISR_NOT_SET,                      /* TIM1_BRK          0x00A0   24    40 */
  ISR_NOT_SET,                      /* TIM1_UP           0x00A4   25    41 */
  ISR_NOT_SET,                      /* TIM1_TRG_COM      0x00A8   26    42 */
  ISR_NOT_SET,                      /* TIM1_CC           0x00AC   27    43 */
  ISR_NOT_SET,                      /* TIM2              0x00B0   28    44 */
  ISR_NOT_SET,                      /* TIM3              0x00B4   29    45 */
  ISR_NOT_SET,                      /* TIM4              0x00B8   30    46 */
  ISR_NOT_SET,                      /* I2C1_EV           0x00BC   31    47 */
  ISR_NOT_SET,                      /* I2C1_ER           0x00C0   32    48 */
  ISR_NOT_SET,                      /* I2C2_EV           0x00C4   33    49 */
  ISR_NOT_SET,                      /* I2C2_ER           0x00C8   34    50 */
  ISR_NOT_SET,                      /* SPI1              0x00CC   35    51 */
  ISR_NOT_SET,                      /* SPI2              0x00D0   36    52 */
  ISR_NOT_SET,                      /* USART1            0x00D4   37    53 */
  ISR_NOT_SET,                      /* USART2            0x00D8   38    54 */
  ISR_NOT_SET,                      /* USART3            0x00DC   39    55 */
  ISR_NOT_SET,                      /* EXTI15_10         0x00E0   40    56 */
  ISR_NOT_SET,                      /* RTCAlarm          0x00E4   41    57 */
  ISR_NOT_SET,                      /* USBWakeup         0x00E8   42    58 */
  ISR_NOT_IMPL,                     /* TIM8_BRK          0x00EC   43    59 */
  ISR_NOT_IMPL,                     /* TIM8_UP           0x00F0   44    60 */
  ISR_NOT_IMPL,                     /* TIM8_TRG_COM      0x00F4   45    61 */
  ISR_NOT_IMPL,                     /* TIM8_CC           0x00F8   46    62 */
  ISR_NOT_IMPL,                     /* ADC3              0x00FC   47    63 */
  ISR_NOT_IMPL,                     /* FSMC              0x0100   48    64 */
  ISR_NOT_IMPL,                     /* SDIO              0x0104   49    65 */
  ISR_NOT_IMPL,                     /* TIM5              0x0108   50    66 */
  ISR_NOT_IMPL,                     /* SPI3              0x010C   51    67 */
  ISR_NOT_IMPL,                     /* UART4             0x0110   52    68 */
  ISR_NOT_IMPL,                     /* UART5             0x0114   53    69 */
  ISR_NOT_IMPL,                     /* TIM6              0x0118   54    70 */
  ISR_NOT_IMPL,                     /* TIM7              0x011C   55    71 */
  ISR_NOT_IMPL,                     /* DMA2_Channel1     0x0120   56    72 */
  ISR_NOT_IMPL,                     /* DMA2_Channel2     0x0124   57    73 */
  ISR_NOT_IMPL,                     /* DMA2_Channel3     0x0128   58    74 */
  ISR_NOT_IMPL,                     /* DMA2_Channel4     0x012C   59    75 */
  ISR_NOT_IMPL,                     /* DMA2_Channel5     0x0130   60    76 */
  ISR_NOT_IMPL,                     /* ETH               0x0134   61    77 */
  ISR_NOT_IMPL,                     /* ETH_WKUP          0x0138   62    78 */
  ISR_NOT_IMPL,                     /* CAN2_TX           0x013C   63    79 */
  ISR_NOT_IMPL,                     /* CAN2_RX0          0x0140   64    80 */
  ISR_NOT_IMPL,                     /* CAN2_RX1          0x0144   65    81 */
  ISR_NOT_IMPL,                     /* CAN2_SCE          0x0148   66    82 */
  ISR_NOT_IMPL                      /* OTG_FS            0x014C   67    83 */
};

static void gpio_setup(struct GPIO *gpio, unsigned int bit, uint32_t flags)
{
	volatile uint32_t *cr;
	uint32_t v;

	if (bit >= 8) {
		cr = &gpio->CRH;
		bit -= 8;
	} else {
		cr = &gpio->CRL;
	}

	v = *cr;
	v &= 0xf << (bit * 4);
	v |= (0xf & flags) << (bit * 4);
	*cr = v;
}

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
#define  RCC_CFGR_PLLMUL_x9	(0xf << RCC_CFGR_PLLMUL_SHIFT)
#define RCC_CFGR_OTGFS_PRE	(1 << 22)
#define RCC_CFGR_MCO_SHIFT	24

#define FLASH_ACR_LATENCY_SHIFT	0
#define FLASH_ACR_HLFCYA	(1 << 3)
#define FLASH_ACR_PRFTBE	(1 << 4)
#define FLASH_ACR_PRFTBS	(1 << 5)

static void rcc_init(void)
{
	RCC->CFGR = RCC_CFGR_PLL_SRC | RCC_CFGR_PLLMUL_x9 | RCC_CFGR_SW_HSI | RCC_CFGR_PPRE1_div2;
	RCC->CR = RCC_CR_HSION | RCC_CR_HSEON | (0x10 << RCC_CR_HSITRIM_SHIFT) | RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY))
		;
	FLASH->ACR = FLASH_ACR_PRFTBE | (2 << FLASH_ACR_LATENCY_SHIFT);
	RCC->CFGR = RCC_CFGR_PLL_SRC | RCC_CFGR_PLLMUL_x9 | RCC_CFGR_SW_PLL | RCC_CFGR_PPRE1_div2;
	RCC->APB2ENR |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 14);
}

static void uart1_init(void)
{
	gpio_setup(GPIOA, 9, 3 | 8);

	USART1->CR1 = 0x340c;
	USART1->CR2 = 0;
	USART1->CR3 = 0;
	USART1->GTPR = 0;
	USART1->BRR = 72000000;
}

void reset_handler(void) __attribute__ ((noreturn));
void reset_handler(void)
{
	extern char _sdata;    // .data section start
	extern char _edata;    // .data section end
	extern char _sbss;     // .bss  section start
	extern char _ebss;     // .bss  section end
	extern char _ldata;    // .data load address

	char *dst = &_sdata;
	char *src = &_ldata;

	/* enable 8-byte stack alignment to comply with AAPCS */
	SCB->CCR |= 1 << 9;

	/* copy initialized variables data */
	while ( dst < &_edata ) { *dst++ = *src++; }

	/* clear uninitialized variables */
	for ( dst = &_sbss; dst < &_ebss; dst++ ) { *dst = 0; }

	rcc_init();
	uart1_init();

	main();
	halt();
}
