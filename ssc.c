/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 20:58:35
*/

#include "ssc.h"
#include "util.h"

#include <stdio.h>

Expr *mk_expr(int expr_type)
{
    Expr *new_expr = ssc_malloc(sizeof(*new_expr));

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

// @Rant: i know this is supposed to be a compiler but i wanna
// start with an repl...
// @Note: maybe we just need Env in here?
void eval(SSCState *state, Expr *expr)
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
}

int main()
{
    Error *err = mk_error(e_bad_arg, "foo", "an integer");
    Error *err2 = mk_error(e_unk_var, "foo");

    ssc_error(get_err_msg(*err2));
}
