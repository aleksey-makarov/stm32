// SPDX-License-Identifier: MIT

#include "dwt.h"
#include "mtrace.h"

int main(void)
{
	uint32_t ts;
	
	MTRACE("%s", __TIMESTAMP__);
	dwt_enable();
	ts = dwt_get_cycles();
	while (1)
		MTRACE("%08ld", dwt_ms_since(ts));
	return 0;
}
