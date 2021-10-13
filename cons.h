/*
 * Created by Costa Bushnaq
 *
 * 13-10-2021 @ 14:27:15
 *
 * see LICENSE
*/

#ifndef _CONS_H
#define _CONS_H

struct Expr;

typedef struct Cons {
	struct Expr *car;
	struct Expr *cdr;
} Cons;

Cons *mk_cons(struct Expr *car, struct Expr *cdr);
struct Expr *car(Cons *cons);
struct Expr *cdr(Cons *cons);
char is_list(struct Expr *expr);
char is_fake_list(struct Expr *expr);

#endif /* _CONS_H */
