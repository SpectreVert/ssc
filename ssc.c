/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 20:58:35
*/

#include "ssc.h"
#include "util.h"

#include <stdio.h>

Expr *mk_expr(int expr_type, int prealloc)
{
    Expr *new_expr = ssc_malloc(sizeof(*new_expr));

    new_expr->type = expr_type;

    if (!prealloc)
        return new_expr;

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
    case e_error:
        new_expr->s_expr.err  = ssc_malloc(sizeof(Error));
        break;
    };

    return new_expr;
}

// @Rant: i know this is supposed to be a compiler but i wanna
// start with an repl...
// @Note: maybe we just need Env in here?
Expr *eval(SSCState *state, Expr *expr)
{
    Expr  *rsexpr = 0x0;
    Error *err = 0x0;

    switch (expr->type) {
    case e_nil: {
        // @Rant: actually we should never be able to reach this;
        // the parser should know this is not valid syntax and
        // throw  it as so during his phase. But i guess this could
        // be useful if we wanna support direct AST providing.
        err = mk_error(e_bad_expr, "()");
    } break;
    case e_integer:
        break;
    case e_symbol:
        break;
    case e_cons:
        break;
    case e_error:
        break;
    };

    if (err) {
        rsexpr = mk_expr(e_error, 0);
        rsexpr->s_expr.err = err;
        // @Todo: return the rest of `expr` nested inside
        return rsexpr;
    }

    return 0x0;
}

void display(Expr *expr, char nested)
{
    switch (expr->type) {
    case e_nil:
        printf("()");
        break;
    case e_integer:
        printf("%d", expr->s_expr.integer);
        break;
    case e_symbol:
        printf("%s", expr->s_expr.sym->name);
        break;
    case e_cons:
        if (is_fake_list(expr)) { /* we're somekind of a list */
            if (!nested)
                printf("(");
            display(expr->s_expr.cons->car, 0);
            printf(" ");
            display(expr->s_expr.cons->cdr, 1);
            if (!nested)
                printf(")");
        } else { /* we're just a plain, old pair */
            if (!nested)
                printf("(");
            display(expr->s_expr.cons->car, 0);
            printf(" . ");
            display(expr->s_expr.cons->cdr, 1);
            if (!nested)
                printf(")");
        } break;
    case e_error:
        printf("%s", get_err_msg(*expr->s_expr.err));
        break;
    };
}

int main()
{
    Expr *expr1 = mk_expr(e_cons, 0);
    Expr *expr11 = mk_expr(e_cons, 0);
    Expr *expr111 = mk_expr(e_integer, 0);
    Expr *expr112 = mk_expr(e_integer, 0);
    Expr *expr12 = mk_expr(e_cons, 0);
    Expr *expr121 = mk_expr(e_integer, 1);
    Expr *expr122 = mk_expr(e_integer, 0);

    expr111->s_expr.integer = 111;
    expr112->s_expr.integer = 112;
    expr11->s_expr.cons = mk_cons(expr111, expr112);
    expr121->s_expr.integer = 121;
    expr122->s_expr.integer = 122;
    expr12->s_expr.cons = mk_cons(expr121, expr122);
    expr1->s_expr.cons = mk_cons(expr11, expr12);

    display(expr1, 0);
}
