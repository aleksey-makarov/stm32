#ifndef __mtrace_h__
#define __mtrace_h__

#include <stdio.h>

#define MTRACE_STRINGIFY_(x) #x
#define MTRACE_STRINGIFY(x) MTRACE_STRINGIFY_(x)
#define MTRACE_WHERE "-- " __FILE__ ":" MTRACE_STRINGIFY(__LINE__) " (%s) : "

#define MTRACE( format, ... ) printf( MTRACE_WHERE format "\n" , __FUNCTION__, ##__VA_ARGS__ )

#endif
