// SPDX-License-Identifier: MIT

#include "i2c.h"
#include <stdio.h>
#include "mtrace.h"
#include "dwt.h"

int main(void)
{
	int err;
	uint8_t v[] = { 0, 0xae };
	uint32_t ts;

	MTRACE("- %s", __TIMESTAMP__);

	i2c_init();
	dwt_enable();
	ts = dwt_get_cycles();
	err = i2c_write(0x3c, v, 2);

	MTRACE("- (%d) in %dms", err, dwt_ms_since(ts));

	return err;
}
