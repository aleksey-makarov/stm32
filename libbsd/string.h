#ifndef __string_h__
#define __string_h__

#include <stdlib.h>

char *strchr(const char *s, int c);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t count);
void *memcpy(void *dest, const void *src, size_t count);
void *memchr(const void *s, int c, size_t n);
int memcmp(const void *cs, const void *ct, size_t count);
void *memmove(void *dest, const void *src, size_t count);
void *memset(void *s, int c, size_t count);
void bzero(void *s, size_t n);

#endif
