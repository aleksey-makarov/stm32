// SPDX-License-Identifier: MIT

#include "regs.h"
#include "uart.h"

int main(void)
{
	int i;
	char *c;
	char *timestamp = __TIMESTAMP__;

	while(1) {
		for (c = timestamp; *c; c++)
			uart_putc(*c);
		uart_putc(' ');
		uart_putc('-');
		uart_putc(' ');
		for(i = 0; i < 26; i++) {
			uart_putc('a' + i);
		}
		uart_putc('\r');
		uart_putc('\n');
	}
}
