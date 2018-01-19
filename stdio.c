#include <stdarg.h>
#include "uart.h"

int putchar(int c)
{
	if (c == '\n')
		uart_putc('\r');
	uart_putc(c);
	return 0;
}

int puts(char *s)
{
	while(*s != '\0') {
		putchar(*s);
		s++;
	}
	putchar('\n');
	return 0;
}

int vprintf(const char *fmt, va_list ap);

int printf(const char *fmt, ...)
{
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = vprintf(fmt, ap);
    va_end(ap);

    return ret;
}
