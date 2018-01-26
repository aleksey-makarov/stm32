// SPDX-License-Identifier: MIT

#include "mtrace.h"
#include "gpio.h"
#include "am2301.h"
#include "dwt.h"

int main(void)
{
	int hum, temp;
	int err;

	MTRACE("+");

	am2301_init();
	while (1) {
		/*
		 * Опрашивать можно не чаще чем раз в 3 секунды,
		 * задержка должна быть до первого опроса
		 */
		dwt_delay_us(4000000);
		err = am2301_read(&temp, &hum);
		MTRACE("err: %d, temp x10: %5d'C, hum x10: %5d%%RH", err, temp, hum);
	}

	MTRACE("- %d", err);

	return err;
}
