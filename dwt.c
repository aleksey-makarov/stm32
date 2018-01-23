#include "dwt.h"
#include "rcc.h"
#include "mtrace.h"

struct DWT {
	volatile uint32_t CTRL;
	volatile uint32_t CYCCNT;
	volatile uint32_t CPICNT;
	volatile uint32_t EXCCNT;
	volatile uint32_t SLEEPCNT;
	volatile uint32_t LSUCNT;
	volatile uint32_t FOLDCNT;
	volatile uint32_t PCSR;
};

struct DSR {
	volatile uint32_t DHCSR;
	volatile uint32_t DCRSR;
	volatile uint32_t DCRDR;
	volatile uint32_t DEMCR;
};

#define DWT ((struct DWT *)0xe0001000)
#define DSR ((struct DSR *)0xe000edf0)

void dwt_enable(void)
{
	DSR->DEMCR |= 0x01000000;
	DWT->CTRL |= 1;
}

void dwt_disable(void)
{
	DSR->DEMCR &= ~0x01000000;
}

uint32_t dwt_get_cycles(void)
{
	return DWT->CYCCNT;
}

unsigned long dwt_ms_since(uint32_t from)
{
	uint32_t to = DWT->CYCCNT;
	return (to - from) / (RCC_CPU_CLK_FREQ / 1000);
}
