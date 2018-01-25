// SPDX-License-Identifier: MIT

#include "liboled/oled.h"
#include "mtrace.h"
#include "uart.h"
#include "sizeof.h"

/* menu */

struct menu_entry {
	void (*f)(void);
	const char *name;
};

#define ENTRY(_n) { .f = _n, .name = # _n }

static int char_to_i(char c)
{
	if ('a' <= c && c <= 'z')
		return c - 'a';
	if ('A' <= c && c <= 'Z')
		return c - 'A';
	return -1;
}

static int _menu(struct menu_entry *entries, unsigned int entries_count)
{
	int i;

	for (i = 0; i < (int)entries_count; i++) {
		printf("%c) %s\n", 'a' + i, entries[i].name);
	}
	printf("> ");
	do {
		i = char_to_i(uart_getc());
		if (i == ('q' - 'a')) {
			putchar('\n');
			return -1;
		}
	} while (i < 0 || i >= (int)entries_count);
	putchar('\n');
	entries[i].f();
	return 0;
}

#define menu(_l) _menu(_l, SIZEOF(_l))

/* print char */

static bool print_char_inverted = false;
static unsigned char print_char_char = 'a';
static int print_char_x = 10, print_char_y = 10;

struct font_description {
	struct font *font;
	const char *name;
};

#define FONT_DESCRIPTION_ENTRY(_f) { .font = &_f, .name = # _f }

static struct font_description fonts[] = {
	FONT_DESCRIPTION_ENTRY(font_small),
	FONT_DESCRIPTION_ENTRY(font_tiny),
	FONT_DESCRIPTION_ENTRY(font_rus),
	FONT_DESCRIPTION_ENTRY(font_medium_numbers),
	FONT_DESCRIPTION_ENTRY(font_big_numbers),
	FONT_DESCRIPTION_ENTRY(font_mega_numbers),
};

static struct font_description *print_char_font = fonts;

static bool char_in_range(unsigned char c)
{
	return print_char_font->font->offset <= c &&
	       c < print_char_font->font->offset + print_char_font->font->numchars;
}

static void set_font_char(void)
{
	if (char_in_range('a'))
		print_char_char = 'a';
	else if (char_in_range('1'))
		print_char_char = '1';
	else
		print_char_char = print_char_font->font->offset;
}

static void test_print_char_left(void)
{
	if (print_char_x > 0)
		print_char_x--;
}

static void test_print_char_right(void)
{
	if (print_char_x < 200)
		print_char_x++;
}

static void test_print_char_up(void)
{
	if (print_char_y > 0)
		print_char_y--;
}

static void test_print_char_down(void)
{
	if (print_char_y < 50)
		print_char_y++;
}

static void test_print_char_next(void)
{
	unsigned char c = print_char_char + 1;
	if (char_in_range(c))
		print_char_char = c;
}

static void test_print_char_prev(void)
{
	unsigned char c = print_char_char - 1;
	if (char_in_range(c))
		print_char_char = c;
}

static void test_print_char_inverse(void)
{
	print_char_inverted = !print_char_inverted;
}

static bool font_in_range(struct font_description *f)
{
	return fonts <= f && f < fonts + SIZEOF(fonts);
}

static void test_print_char_next_font(void)
{
	struct font_description *f = print_char_font + 1;
	if (font_in_range(f)) {
		print_char_font = f;
		set_font_char();
	}
}

static void test_print_char_prev_font(void)
{
	struct font_description *f = print_char_font - 1;
	if (font_in_range(f)) {
		print_char_font = f;
		set_font_char();
	}
}

static struct menu_entry print_char_menu[] = {
	ENTRY(test_print_char_left),
	ENTRY(test_print_char_right),
	ENTRY(test_print_char_up),
	ENTRY(test_print_char_down),
	ENTRY(test_print_char_next),
	ENTRY(test_print_char_prev),
	ENTRY(test_print_char_inverse),
	ENTRY(test_print_char_next_font),
	ENTRY(test_print_char_prev_font),
};

static void test_print_char(void)
{
	do {
		printf("font: %s, char: \'%c\' at %d:%d\n", print_char_font->name, print_char_char, print_char_x, print_char_y);
		oled_clrScr();
		oled_printChar(print_char_font->font, print_char_inverted,
			       print_char_char, print_char_x, print_char_y);
		oled_update();
	} while(!menu(print_char_menu));
}

/* root menu */

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

static struct menu_entry root_menu[] = {
	ENTRY(test_upper_case),
	ENTRY(test_lower_case),
	ENTRY(test_numbers),
	ENTRY(test_special),
	ENTRY(test_print_char),
};

int main(void)
{
	oled_begin();
	set_font_char();
	while(1)
		menu(root_menu);
	return 0;
}
