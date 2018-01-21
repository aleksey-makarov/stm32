#include "regs.h"
#include "gpio.h"

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

void gpio_out(struct GPIO *gpio, unsigned int bit, bool value)
{
	uint32_t v;

	v = gpio->ODR;

	if (value)
		v |= (1 << bit);
	else
		v &= ~(1 << bit);

	gpio->ODR = v;
}

bool gpio_in(struct GPIO *gpio, unsigned int bit)
{
	return gpio->IDR & (1 << bit);
}
