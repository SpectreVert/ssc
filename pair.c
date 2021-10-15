/*
 * Created by Costa Bushnaq
 *
 * 13-10-2021 @ 14:45:27
*/

#include "pair.h"
#include "util.h"
#include "ssc.h"

Pair *mk_pair(size_t size, ...)
{
    Pair *pair;
    VA_ARG_START(al, size);

    pair = mk_pair_va_list(size, al);
    VA_ARG_END(al);

    return pair;
}

// @About: taks as much elements as you want
Pair *mk_pair_va_list(size_t size, va_list al)
{
    Pair *pair = ssc_malloc(sizeof(*pair));
    ssc_assert(size >= 2 && "mk_list() takes at least 2 Expr * as arguements");

    for (size_t i = 2; i < size; ++i) {
        pair->car = VA_ARG(al, Expr *);
        pair->cdr = ssc_malloc(sizeof(Expr));
        pair->cdr->type = e_pair;
        pair = pair->cdr->s_expr.pair;
    }
    pair->car = VA_ARG(al, Expr *);
    pair->cdr = VA_ARG(al, Expr *);

    return pair;
}

Expr *car(Pair *pair)
{
    return pair->car;
}

Expr *cdr(Pair *pair)
{
    return pair->cdr;
}

char is_list(Expr *expr)
{
    if (expr->type == e_nil)
        return 1;
    else if (expr->type == e_pair)
        return is_list(expr->s_expr.pair->cdr);
    else
        return 0;
}

// @Note: what i call a "fake" list is when the cdr of the pair
// is another pair
char is_fake_list(Expr *expr)
{
    // if it isn't a pair we don't even look at it
    if (expr->type != e_pair)
        return 0;

    return expr->s_expr.pair->cdr->type == e_pair;
}
