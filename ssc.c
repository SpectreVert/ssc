/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 20:58:35
*/

#include "ssc.h"
#include "util.h"

#include <stdio.h>

char const ident_chars[] =\
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOP1234567890"\
    "1234567890"\
    "!$%&*+-./:<=>?@^_~";

SSCState *ssc_state = 0x0;

int main()
{
    ssc_malloc(20);
}
