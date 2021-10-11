/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 22:58:42
 *
 * see LICENSE
*/

#ifndef _UTIL_H
#define _UTIL_H

#include <stddef.h>

#define PRINTF_LIKE(x, y) __attribute__ ((format (printf, (x), (y))))

#define ssc_internal_error(msg) ssc_error0("internal compiler error\n"\
	"%s:%d: in %s(): " msg, __FILE__, __LINE__, __FUNCTION__)

void  ssc_error0(char *const fmt, ...) PRINTF_LIKE(1, 2);
void  ssc_error(char *const fmt, ...)  PRINTF_LIKE(1, 2);
void* ssc_malloc(size_t size);

#endif /* _UTIL_H */
