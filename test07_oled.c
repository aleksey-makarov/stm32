// SPDX-License-Identifier: MIT

#include "liboled/oled.h"
#include <stdio.h>
#include "mtrace.h"
#include "dwt.h"
#include "i2c.h"

int main(void)
{
	oled_begin();
	oled_drawCircle(10, 10, 10);
	oled_update();
	return 0;
}
