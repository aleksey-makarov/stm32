// SPDX-License-Identifier: MIT

#include "i2c.h"
#include <stdio.h>
#include "mtrace.h"
#include "dwt.h"

static void test(uint8_t cmd)
{
	uint32_t ts;
	uint8_t v[] = { 0, cmd };
	int err;

	MTRACE("+");
	ts = dwt_get_cycles();
	err = i2c_write(0x3c, v, 2);
	MTRACE("- cmd: 0x%02x, err: %d, time: %d ms", (unsigned int)cmd, err, dwt_ms_since(ts));
}

int main(void)
{
	MTRACE("+ %s", __TIMESTAMP__);

	i2c_init();
	dwt_enable();
	
	test(0xae);
	test(0xae);

	MTRACE("-");
	return 0;
}
