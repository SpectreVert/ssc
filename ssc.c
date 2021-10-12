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
        new_expr->s_expr.sym = ssc_malloc(sizeof(Sym));
        break;
    case e_cons:
        new_expr->s_expr.cons = ssc_malloc(sizeof(Expr) * 2);
        break;
    };

    return new_expr;
}

// @Note: maybe we just need Env in here?
Expr *eval(SSCState *state, Expr *expr)
{
    switch (expr->type) {
    case e_nil:
        break;
    case e_integer:
        break;
    case e_symbol:
        break;
    case e_cons:
        break;
    };

    return 0x0;
}

int main()
{
    ssc_assert(0);
    ssc_malloc(20);
}
