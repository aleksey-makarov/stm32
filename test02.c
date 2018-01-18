// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2017 Andrea Loi                                                *
 */

#include "regs.h"

#define USART_SR_TXE (1 << 7)

void serial_putc(int c)
{
	while (!(USART1->SR & USART_SR_TXE))
		;
	USART1->DR = c & 0xff;
}

int main(void)
{
	int i;
	while(1) {
		for(i = 0; i < 26; i++) {
			serial_putc('a' + i);
		}
		serial_putc('\n');
	}
}
