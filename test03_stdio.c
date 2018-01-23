// SPDX-License-Identifier: MIT

#include <stdio.h>

int main(void)
{
	int i = 0;

	puts(__TIMESTAMP__);
	putchar('\n');

	while(1) {
		printf("%d: lalala\r", i++);
	}
}
