#ifndef __i2c_h__
#define __i2c_h__

#include <stdint.h>

void i2c_init(void);
int i2c_write(uint8_t address, uint8_t *values, unsigned long values_length);

#endif
