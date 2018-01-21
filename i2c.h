#ifndef __i2c_h__
#define __i2c_h__

void i2c_init(void);
int i2c_write(uint8_t address, uint8_t reg, uint8_t v);

#endif
