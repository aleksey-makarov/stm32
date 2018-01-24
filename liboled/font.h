#ifndef __font_h__
#define __font_h__

#include <stdint.h>

struct font {
	uint8_t *font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};

extern struct font font_tiny;
extern struct font font_small;
extern struct font font_rus;
extern struct font font_medium_numbers;
extern struct font font_big_numbers;
extern struct font font_mega_numbers;

#endif
