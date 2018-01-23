#include "gpio.h"

struct GPIO {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
};

struct GPIO_BB {
	volatile uint32_t CRL[32];
	volatile uint32_t CRH[32];
	volatile uint32_t IDR[32];
	volatile uint32_t ODR[32];
	volatile uint32_t BSRR[32];
	volatile uint32_t BRR[32];
	volatile uint32_t LCKR[32];
};

       struct GPIO    * const GPIOA    = ((struct GPIO *)    0x40010800);
       struct GPIO    * const GPIOB    = ((struct GPIO *)    0x40010C00);
       struct GPIO    * const GPIOC    = ((struct GPIO *)    0x40011000);
       struct GPIO    * const GPIOD    = ((struct GPIO *)    0x40011400);
// static struct GPIO_BB * const GPIOA_BB = ((struct GPIO_BB *) 0x42210000);
// static struct GPIO_BB * const GPIOB_BB = ((struct GPIO_BB *) 0x42218000);
// static struct GPIO_BB * const GPIOC_BB = ((struct GPIO_BB *) 0x42220000);
// static struct GPIO_BB * const GPIOD_BB = ((struct GPIO_BB *) 0x42228000);

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
