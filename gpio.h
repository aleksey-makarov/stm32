#ifndef __gpio_h__
#define __gpio_h__

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

void gpio_setup(struct GPIO *gpio, unsigned int bit, uint32_t mode);

#endif
