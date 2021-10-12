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

Expr *mk_expr(enum Type expr_type)
{
    Expr *new_expr = ssc_malloc(sizeof(new_expr));

    new_expr->type = expr_type;
    switch (expr_type) {
    case e_nil:
    case e_integer:
        break;
    case e_symbol:
        new_expr->sexpr.sym = ssc_malloc(sizeof(Sym));
        break;
    case e_cons:
        new_expr->sexpr.cons = ssc_malloc(sizeof(Expr) * 2);
        break;
    };

    return new_expr;
}

int main()
{
    ssc_malloc(20);
}
