// SPDX-License-Identifier: MIT

#include "regs.h"
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
