/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 22:58:42
 *
 * see LICENSE
*/

#ifndef _UTIL_H
#define _UTIL_H

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>

#define PRINTF_LIKE(x, y) __attribute__ ((format (printf, (x), (y))))

#define VA_ARG_START(name, last_arg) va_list name; va_start(name, last_arg)
#define VA_ARG(name, type)           va_arg(name, type)
#define VA_ARG_END(name)             va_end(name)
#define VA_ARG_COPY(src, dest)       va_copy(dest, src)

// for now is a copy of assert but can be changed in the future for debug
#define ssc_assert(x) assert(x)

#define ssc_internal_error(msg) ssc_error0("internal compiler error\n"\
	"%s:%d: in %s(): " msg, __FILE__, __LINE__, __FUNCTION__)

void  ssc_error0(char *const fmt, ...) PRINTF_LIKE(1, 2);
void  ssc_error(char *const fmt, ...)  PRINTF_LIKE(1, 2);
void *ssc_malloc(size_t size);
void  ssc_free(void *ptr);
char *ssc_strdup(char const *s);

#endif /* _UTIL_H */
