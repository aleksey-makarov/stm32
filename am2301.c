#include "am2301.h"
#include "dwt.h"
#include <stdbool.h>
#include "gpio.h"

// #define DEBUG

#ifdef DEBUG
# include "mtrace.h"
#else
# define MTRACE(...)
#endif

#define GPIODEV GPIOA
#define GPIOPIN 7

void am2301_init(void) {
	dwt_enable();
}

static int read_bit(bool *v)
{
	uint32_t ts = dwt_get_cycles();
	int err = 0;

	while (1) {
		if (gpio_in(GPIODEV, GPIOPIN))
			break;

		if (dwt_us_since(ts) > 60) {
			MTRACE("timeout @4");
			err = -1;
			goto error;
		}
	}
	if (dwt_us_since(ts) < 45) {
		MTRACE("too fast @4");
		err = -1;
		goto error;
	}

	ts = dwt_get_cycles();
	while (1) {
		if (!gpio_in(GPIODEV, GPIOPIN))
			break;

		if (dwt_us_since(ts) > 80) {
			MTRACE("timeout @5");
			err = -1;
			goto error;
		}
	}
	if (dwt_us_since(ts) < 20) {
		MTRACE("too fast @5");
		err = -1;
		goto error;
	}

	*v = !!(dwt_us_since(ts) > 45);

error:
	return err;
}

static int read_byte(uint8_t *v)
{
	bool b;
	int err;
	int i;

	*v = 0;
	for (i = 7; i >= 0; i--) {
		err = read_bit(&b);
		if (err)
			break;
		if (b)
			*v |= (1 << i);
	}

	return err;
}

int am2301_read(int *temp, int *hum) {
	uint8_t d[5];
	uint32_t ts;
	int err = 0;
	int i;

	MTRACE("+");

	/* Pin output */
	gpio_setup(GPIODEV, GPIOPIN, GPIO_MODE_OUT_50MHz | GPIO_CNF_OUT_GPIO_PULL);
	gpio_out(GPIODEV, GPIOPIN, 0);
	dwt_delay_us(1000);
	gpio_out(GPIODEV, GPIOPIN, 1);
	gpio_setup(GPIODEV, GPIOPIN, GPIO_MODE_IN | GPIO_CNF_IN_PULL);

	ts = dwt_get_cycles();
	while (1) {
		if (!gpio_in(GPIODEV, GPIOPIN))
			break;

		if (dwt_us_since(ts) > 25) {
			MTRACE("timeout @1");
			err = -1;
			goto error;
		}
	}
	if (dwt_us_since(ts) < 15) {
		MTRACE("too fast @1");
		err = -1;
		goto error;
	}

	ts = dwt_get_cycles();
	while (1) {
		if (gpio_in(GPIODEV, GPIOPIN))
			break;

		if (dwt_us_since(ts) > 90) {
			MTRACE("timeout @2");
			err = -1;
			goto error;
		}
	}
	if (dwt_us_since(ts) < 70) {
		MTRACE("too fast @2");
		err = -1;
		goto error;
	}

	ts = dwt_get_cycles();
	while (1) {
		if (!gpio_in(GPIODEV, GPIOPIN))
			break;

		if (dwt_us_since(ts) > 90) {
			MTRACE("timeout @3");
			err = -1;
			goto error;
		}
	}
	if (dwt_us_since(ts) < 70) {
		MTRACE("too fast @3");
		err = -1;
		goto error;
	}

	for (i = 0; i < 5; i++) {
		err = read_byte(d + i);
		if (err) {
			MTRACE("error reading byte %d", i);
			goto error;
		}
	}

#ifdef DEBUG
	for (i = 0; i < 5; i++) {
		printf("0x%02x ", (unsigned int)d[i]);
	}
	putchar('\n');
#endif

	if (((d[0] + d[1] + d[2] + d[3]) & 0xff) != d[4]) {
		MTRACE("parity error");
		err = -1;
		goto error;
	}


	if (hum) {
		*hum = d[0] << 8 | d[1];
	}

	if (temp) {
		bool tminus = false;
		if (d[2] & (1 << 7)) {
			tminus = true;
			d[2] &= ~(1 << 7);
		}
		*temp = d[2] << 8 | d[3];
		if (tminus)
			*temp = -*temp;
	}

error:
	MTRACE("-");
	return err;
}
