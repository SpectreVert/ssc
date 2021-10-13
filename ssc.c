/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 20:58:35
*/

#include "ssc.h"
#include "util.h"

#include <stdio.h>

// @Todo: a mk_expr_hollow() or something that doesn't take the
// objects to fill up the structure.
Expr *mk_expr(int expr_type, ...)
{
    Expr *new_expr = ssc_malloc(sizeof(*new_expr));
    va_list al;

    new_expr->type = expr_type;
    va_start(al, expr_type);

    switch (expr_type) {
    case e_nil:
    case e_integer:
        new_expr->s_expr.integer = va_arg(al, int);
        break;
    case e_symbol:
        new_expr->s_expr.sym = ssc_malloc(sizeof(Sym));
        assert(0 || "haven't implemented symbols yet");
        break;
    case e_cons:
        new_expr->s_expr.cons = ssc_malloc(sizeof(Cons));
        new_expr->s_expr.cons->car = va_arg(al, Expr *);
        new_expr->s_expr.cons->cdr = va_arg(al, Expr *);
        break;
    case e_error:
        new_expr->s_expr.err  = ssc_malloc(sizeof(Error));
        new_expr->s_expr.err = va_arg(al, Error *);
        break;
    };
    
    va_end(al);

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
    Expr *newmode = mk_expr(e_cons,
        mk_expr(e_cons,
            mk_expr(e_integer, 111),
            mk_expr(e_integer, 112)),
        mk_expr(e_cons,
            mk_expr(e_integer, 121),
            mk_expr(e_integer, 122)));

    display(newmode, 0);
}
