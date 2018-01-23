// SPDX-License-Identifier: MIT

#include "uart.h"

int main(void)
{
	char *c;
	char v;
	char *timestamp = __TIMESTAMP__;

	uart_putc('2');
	uart_putc(' ');

	for (c = timestamp; *c; c++)
		uart_putc(*c);

	while(1) {
		v = uart_getc();
		uart_putc('>');
		uart_putc(' ');
		uart_putc(v);
		uart_putc('\r');
		uart_putc('\n');
	}
}
