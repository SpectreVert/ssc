/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 20:35:42
 *
 * see LICENSE
*/

#ifndef _SSC_H
#define _SSC_H

// @Todo move this downstairs in the file
typedef struct {
	unsigned char verbose;
} SSCState;

extern SSCState *ssc_state;

/* ============================================================ */

extern char const ident_chars[];

enum Type {
	e_nil,
	e_integer,
	e_symbol,
	e_cons,
};

// @Note: list should be implemented as a list of cons
// so don't try to be clever and make a O(1) complexity
// list type. For this will implement vector

// @Note: symbol has to be implemented as a pointer- whatever that means
// @Note2: symbols should be implemented using a hash table.

typedef struct Sym {
	// @Todo
} Sym;

// @Todo: (maybe) put this in another file so that we can have a lot
// of error enums and messages without messing up ssc.h
// @Rant: I don't really like the concept of exceptions so we'll make-do
// with that Error type
typedef struct Error {
	enum {
		e_default,  /* if you don't know better */
		e_bad_expr, /* evaluating stuff that doesn't belong */
		e_unk_var,  /* variable is not bound */
		e_non_proc, /* attempting to apply non-procedure */
		e_num_args, /* wrong number of arguments */
		e_bad_arg,  /* bad argument type */
	} type;
	char *ctx; /* some additional context */
} Error;

typedef struct Expr {
	enum Type type;
	union {
		int  integer;
		struct Sym   *sym;
		struct Expr  *cons;
		struct Error *err;
	} s_expr;
} Expr;

typedef struct Env {
	// @Todo
	struct Env *parent;
} Env;

/* ============================================================ */

Expr *mk_expr(enum Type expr_type);
Expr *eval(SSCState *state, Expr *expr);

#endif /* _SSC_H */
