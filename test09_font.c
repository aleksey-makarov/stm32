// SPDX-License-Identifier: MIT

#include "liboled/oled.h"
#include "mtrace.h"
#include "uart.h"
#include "sizeof.h"

static void test_upper_case(void)
{
	puts("upper case");
	oled_clrScr();
	oled_print(&font_small, false, "Upper case:",   OLED_LEFT, 0);
	oled_print(&font_small, false, "ABCDEFGHIJKLM", OLED_CENTER, 16);
	oled_print(&font_small, false, "NOPQRSTUVWXYZ", OLED_CENTER, 24);
	oled_update();
}

static void test_lower_case(void)
{
	puts("lower case");
	oled_clrScr();
	oled_print(&font_small, false, "Lower case:",   OLED_LEFT, 0);
	oled_print(&font_small, false, "abcdefghijklm", OLED_CENTER, 16);
	oled_print(&font_small, false, "nopqrstuvwxyz", OLED_CENTER, 24);
	oled_update();
}

static void test_numbers(void)
{
	puts("numbers");
	oled_clrScr();
	oled_print(&font_small, false, "Numbers:",   OLED_LEFT, 0);
	oled_print(&font_small, false, "0123456789", OLED_CENTER, 16);
	oled_update();
}

static void test_special(void)
{
	puts("special");
	oled_clrScr();
	oled_print(&font_small, false, "Special:",        OLED_LEFT, 0);
	oled_print(&font_small, false, "!\"#$%&'()*+,-.", OLED_CENTER, 16);
	oled_print(&font_small, false, "/:;<=>?@[\\]^_`", OLED_CENTER, 24);
	oled_print(&font_small, false, "{|}~",            OLED_CENTER, 32);
	oled_update();
}

struct menu_entry {
	void (*f)(void);
	const char *name;
};

#define ENTRY(_n) { .f = _n, .name = # _n }

static struct menu_entry root_menu[] = {
	ENTRY(test_upper_case),
	ENTRY(test_lower_case),
	ENTRY(test_numbers),
	ENTRY(test_special),
};

static int char_to_i(char c)
{
	if ('a' <= c && c <= 'z')
		return c - 'a';
	if ('A' <= c && c <= 'Z')
		return c - 'A';
	return -1;
}

static void menu(struct menu_entry *entries, unsigned int entries_count)
{
	int i;

	while (1) {
		for (i = 0; i < (int)entries_count; i++) {
			printf("%c: %s\n", 'a' + i, entries[i].name);
		}
		printf("> ");
		do
			i = char_to_i(uart_getc());
		while (i < 0 || i >= (int)entries_count);
		if (i == ('q' - 'a'))
			break;
		putchar('\n');
		entries[i].f();
	}
}

int main(void)
{
	oled_begin();
	menu(root_menu, SIZEOF(root_menu));
	return 0;
}
