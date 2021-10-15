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
// OR
// make a flag to OR into expr_type to tell not to allocate
Expr *mk_expr(int expr_type, ...)
{
    Expr *new_expr = ssc_malloc(sizeof(*new_expr));
    VA_ARG_START(al, expr_type);

    new_expr->type = expr_type;

    switch (expr_type) {
    case e_nil:
        break;
    case e_integer:
        new_expr->s_expr.integer = VA_ARG(al, int);
        break;
    case e_symbol:
        new_expr->s_expr.sym = ssc_malloc(sizeof(Sym));
        assert(0 || "haven't implemented symbols yet");
        break;
    case e_pair: {
        size_t tmp_size = VA_ARG(al, size_t);
        va_list tmp_al;
        VA_ARG_COPY(al, tmp_al);
        new_expr->s_expr.pair = mk_pair_va_list(tmp_size, tmp_al);
        VA_ARG_END(tmp_al);
        } break;
    case e_error:
        new_expr->s_expr.err = va_arg(al, Error *);
        break;
    };
    VA_ARG_END(al);

    return new_expr;
}

// @Rant: i know this is supposed to be a compiler but i wanna
// start with an repl...
// @Note: maybe we just need Env in here?
Expr *eval(SSCState *state, Expr *expr)
{
    Expr  *ret_expr = 0x0;
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
        ret_expr = expr;
        break;
    case e_symbol:
        break;
    case e_pair:
        ssc_error("cons evaluation not done yet");
        ret_expr = expr;
        break;
    case e_error:
        ret_expr = expr;
        break;
    };

    if (err) {
        ret_expr = mk_expr(e_error, 0);
        ret_expr->s_expr.err = err;
        // @Todo: return the rest of `expr` nested inside
    }

    return ret_expr;
}

void display(Expr *expr)
{
    display_nested(expr, 0);
}

void display_nested(Expr *expr, char nested)
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
    case e_pair:
        if (is_fake_list(expr)) { /* we're somekind of a list */
            if (!nested)
                printf("(");
            display(expr->s_expr.pair->car);
            printf(" ");
            display_nested(expr->s_expr.pair->cdr, 1);
            if (!nested)
                printf(")");
        } else { /* we're just a plain, old pair */
            if (!nested)
                printf("(");
            display(expr->s_expr.pair->car);
            // @Bug: from the scheme reference, should only print dot
            // if the next thing is not a '('
            // so basically if it isn't a pair or nil
            if (expr->s_expr.pair->cdr->type != e_pair &&
                expr->s_expr.pair->cdr->type != e_nil) {
                printf(" . ");
            } else {
                printf(" ");
            }
            display_nested(expr->s_expr.pair->cdr, 1);
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
    Expr *cons = mk_expr(e_pair, 2,
        mk_expr(e_integer, 111),
        mk_expr(e_integer, 112));
    Expr *cons1 = mk_expr(e_pair, 2,
        mk_expr(e_integer, 121),
        mk_expr(e_integer, 122));

    Expr *pair_of_pair = mk_expr(e_pair, 2, mk_expr(e_integer, 113), cons1);
    Expr *list_of_pair = mk_expr(e_pair, 2, cons, cons1);

    printf("pair of pair: ");
    display(pair_of_pair);
    puts("");
    printf("list of pair: ");
    display(list_of_pair);
    puts("");
}
