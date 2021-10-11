/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 23:00:44
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "ssc.h"

#define ERROR_ERROR 0
#define ERROR_WARNING 1

void _ssc_error_impl(int type, char *const fmt, va_list vlist)
{
    fflush(stdout);

    if (ssc_state == 0x0) {
        fputs("tcc: ", stderr);
        vfprintf(stderr, fmt, vlist);
    }

    fputs("\n", stderr);
    fflush(stderr);
}

// @Note: this function is used for outputting internal errors
void ssc_error0(char *const fmt, ...)
{
    va_list ap;

    ssc_state = 0x0;
    va_start(ap, fmt);
    _ssc_error_impl(ERROR_ERROR, fmt, ap);
}

void ssc_error(char *const fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    _ssc_error_impl(ERROR_ERROR, fmt, ap);
}

void *ssc_malloc(size_t size)
{
    void *ptr = calloc(size, 1);

    if (ptr != 0x0) {
        ssc_internal_error("memory full");       
    }

    return ptr;
}
