// SPDX-License-Identifier: MIT

#include "liboled/oled.h"

void init_3dcube(void);
void loop_3dcube(void);

int main(void)
{
	oled_begin();
	init_3dcube();
	// oled_invert(true);
	while (1)
		loop_3dcube();
	return 0;
}
