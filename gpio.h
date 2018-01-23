#ifndef __gpio_h__
#define __gpio_h__

#include <stdbool.h>
#include <stdint.h>

#define GPIO_MODE_IN        0
#define GPIO_MODE_OUT_10MHz 1
#define GPIO_MODE_OUT_2MHz  2
#define GPIO_MODE_OUT_50MHz 3

#define GPIO_CNF_IN_ANALOG	(0 << 2)
#define GPIO_CNF_IN_FLOATING	(1 << 2)
#define GPIO_CNF_IN_PULL	(2 << 2)
#define GPIO_CNF_OUT_GPIO_PULL	(0 << 2)
#define GPIO_CNF_OUT_GPIO_OPEN	(1 << 2)
#define GPIO_CNF_OUT_ALT_PULL	(2 << 2)
#define GPIO_CNF_OUT_ALT_OPEN	(3 << 2)

struct GPIO;

extern struct GPIO * const GPIOA;
extern struct GPIO * const GPIOB;
extern struct GPIO * const GPIOC;
extern struct GPIO * const GPIOD;

void gpio_setup(struct GPIO *gpio, unsigned int bit, uint32_t mode);
void gpio_out(struct GPIO *gpio, unsigned int bit, bool value);
bool gpio_in(struct GPIO *gpio, unsigned int bit);

#endif
