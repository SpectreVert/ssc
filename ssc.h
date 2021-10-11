/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 20:35:42
 *
 * see LICENSE
*/

#ifndef _SSC_H
#define _SSC_H

struct SSCState {
	unsigned char verbose;
};

typedef struct SSCState SSCState;

extern SSCState *ssc_state;

/* ============================================================ */

extern char const ident_chars[];

// @Todo: red-black tree or something for storing the symbols

enum Type {
	e_nil,
	e_symbol,
	e_integer,
	e_cons,
};

// @Note: list should be implemented as a list of cons
// so don't try to be clever and make a O(1) complexity
// list type. For this will implement vector

// @Note: symbol has to be implemented as a pointer- whatever that means
// @Note2: symbols should be implemented using a hash table.

struct Expr {
	enum Type type;
	union {
		int         integer;
		struct Sym  *sym;
		struct Expr *cons;
	} expr;
};

struct Env {
	// @Todo
	struct Env *parent;
};

/* ============================================================ */

struct Expr *mk_expr(enum Type);

#endif /* _SSC_H */
