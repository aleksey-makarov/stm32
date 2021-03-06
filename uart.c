#include "uart.h"
#include "rcc.h"
#include <stdint.h>

#define USART_SR_TXE	(1 << 7)
#define USART_SR_RXNE	(1 << 5)

#define USART_CR_SBK	(1 << 0)
#define USART_CR_RWU	(1 << 1)
#define USART_CR_RE	(1 << 2)
#define USART_CR_TE	(1 << 3)
#define USART_CR_IDLEIE	(1 << 4)
#define USART_CR_RXNEIE	(1 << 5)
#define USART_CR_TCIE	(1 << 6)
#define USART_CR_TXEIE	(1 << 7)
#define USART_CR_PEIE	(1 << 8)
#define USART_CR_PS	(1 << 9)
#define USART_CR_PCE	(1 << 10)
#define USART_CR_WAKE	(1 << 11)
#define USART_CR_M	(1 << 12)
#define USART_CR_UE	(1 << 13)

struct USART {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
};

struct USART_BB {
	volatile uint32_t SR[32];
	volatile uint32_t DR[32];
	volatile uint32_t BRR[32];
	volatile uint32_t CR1[32];
	volatile uint32_t CR2[32];
	volatile uint32_t CR3[32];
	volatile uint32_t GTPR[32];
};

#define USART1        ((struct USART *) 0x40013800)
#define USART2        ((struct USART *) 0x40004400)
#define USART3        ((struct USART *) 0x40004800)
#define USART1_BB     ((struct USART_BB *) 0x42270000)
#define USART2_BB     ((struct USART_BB *) 0x42088000)
#define USART3_BB     ((struct USART_BB *) 0x42090000)

void uart_init(void)
{
	USART1->CR1 = USART_CR_UE | USART_CR_TE | USART_CR_RE;
	USART1->CR2 = 0;
	USART1->CR3 = 0;
	USART1->GTPR = 0;
	USART1->BRR = RCC_APB2_FREQ / 115200;
}

void uart_putc(char c)
{
	while (!(USART1->SR & USART_SR_TXE))
		;
	USART1->DR = (uint32_t)c;
}

char uart_getc(void)
{
	while (!(USART1->SR & USART_SR_RXNE))
		;
	return USART1->DR & 0xff;
}
