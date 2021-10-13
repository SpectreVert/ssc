/*
 * Created by Costa Bushnaq
 *
 * 13-10-2021 @ 14:45:27
*/

#include "cons.h"
#include "util.h"
#include "ssc.h"

Cons *mk_cons(Expr *car, Expr *cdr)
{
    Cons *cons = ssc_malloc(sizeof(*cons));

    cons->car = car;
    cons->cdr = cdr;
    return cons;
}

Expr *car(Cons *cons)
{
    return cons->car;
}

Expr *cdr(Cons *cons)
{
    return cons->cdr;
}

char is_list(Expr *expr)
{
    if (expr->type == e_nil)
        return 1;
    else if (expr->type == e_cons)
        return is_list(expr->s_expr.cons->cdr);
    else
        return 0;
}

// @Note: what i call a "fake" list is when the cdr of the cons
// is another cons
char is_fake_list(Expr *expr)
{
    // if it isn't a cons we don't even look at it
    if (expr->type != e_cons)
        return 0;

    return expr->s_expr.cons->cdr->type == e_cons;
}
