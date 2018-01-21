// SPDX-License-Identifier: MIT

#include "regs.h"
#include "gpio.h"
#include <stdio.h>

int main(void)
{
	int i;
	int j;
	for (i = 0; 1; i++) {
		gpio_out(GPIOC, 13, i % 2);
		for (j = 0; j < 1000000; j++)
			;
	}
	return 0;
}
