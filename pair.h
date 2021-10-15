/*
 * Created by Costa Bushnaq
 *
 * 13-10-2021 @ 14:27:15
 *
 * see LICENSE
*/

#ifndef _PAIR_H
#define _PAIR_H

#include <stdarg.h>
#include <stddef.h>

struct Expr;

// @Todo: rename all of this to Pair
typedef struct Pair {
	struct Expr *car;
	struct Expr *cdr;
} Pair;

Pair *mk_pair(size_t size, ...);
Pair *mk_pair_va_list(size_t size, va_list al);
struct Expr *car(Pair *pair);
struct Expr *cdr(Pair *pair);
char is_list(struct Expr *expr);
char is_fake_list(struct Expr *expr);

#endif /* _CONS_H */
