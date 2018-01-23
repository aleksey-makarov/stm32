#ifndef __dwt_h__
#define __dwt_h__

#include <stdint.h>

void dwt_enable(void);
void dwt_disable(void);
uint32_t dwt_get_cycles(void);
unsigned long dwt_ms_since(uint32_t ts);

#endif
