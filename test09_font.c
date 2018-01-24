// SPDX-License-Identifier: MIT

#include "liboled/oled.h"
#include "mtrace.h"
#include "uart.h"

int main(void)
{
	oled_begin();

	while (true) {
		MTRACE("upper case");
		oled_clrScr();
		oled_print(&font_small, false, "Upper case:",   OLED_LEFT, 0);
		oled_print(&font_small, false, "ABCDEFGHIJKLM", OLED_CENTER, 16);
		oled_print(&font_small, false, "NOPQRSTUVWXYZ", OLED_CENTER, 24);
		oled_update();
		uart_getc();

		MTRACE("lower case");
		oled_clrScr();
		oled_print(&font_small, false, "Lower case:",   OLED_LEFT, 0);
		oled_print(&font_small, false, "abcdefghijklm", OLED_CENTER, 16);
		oled_print(&font_small, false, "nopqrstuvwxyz", OLED_CENTER, 24);
		oled_update();
		uart_getc();

		MTRACE("numbers");
		oled_clrScr();
		oled_print(&font_small, false, "Numbers:",   OLED_LEFT, 0);
		oled_print(&font_small, false, "0123456789", OLED_CENTER, 16);
		oled_update();
		uart_getc();

		MTRACE("special");
		oled_clrScr();
		oled_print(&font_small, false, "Special:",        OLED_LEFT, 0);
		oled_print(&font_small, false, "!\"#$%&'()*+,-.", OLED_CENTER, 16);
		oled_print(&font_small, false, "/:;<=>?@[\\]^_`", OLED_CENTER, 24);
		oled_print(&font_small, false, "{|}~",            OLED_CENTER, 32);
		oled_update();
		uart_getc();
	}

	return 0;
}
