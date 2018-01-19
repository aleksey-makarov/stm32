#include "regs.h"

void gpio_setup(struct GPIO *gpio, unsigned int bit, uint32_t mode)
{
	volatile uint32_t *cr;
	uint32_t v;

	if (bit >= 8) {
		cr = &gpio->CRH;
		bit -= 8;
	} else {
		cr = &gpio->CRL;
	}

	v = *cr;
	v &= ~(0xf << (bit * 4));
	v |= (0xf & mode) << (bit * 4);
	*cr = v;
}
