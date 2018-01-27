// SPDX-License-Identifier: MIT

#include "mtrace.h"
#include "gpio.h"
#include "am2301.h"
#include "dwt.h"

#define DEGREE_CELSIUS "\xe2\x84\x83"
#define DEGREE_SIGN "\xc2\xb0"

int main(void)
{
	int hum, temp;
	int err;

	MTRACE("+");

	am2301_init();
	while (1) {
		/*
		 * Опрашивать можно не чаще чем раз в 2 секунды,
		 * задержка должна быть до первого опроса
		 */
		dwt_delay_us(2000000);
		err = am2301_read(&temp, &hum);
		MTRACE("err: %d, temp: %d.%1d" DEGREE_SIGN "C, hum: %d.%1d%%RH",
		       err, temp / 10, temp % 10, hum / 10, hum % 10);
	}

	MTRACE("- %d", err);

	return err;
}
