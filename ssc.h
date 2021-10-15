/*
 * Created by Costa Bushnaq
 *
 * 11-10-2021 @ 20:35:42
 *
 * see LICENSE
*/

#ifndef _SSC_H
#define _SSC_H

#include "err.h"
#include "pair.h"

// @Todo move this to another file (i.e: ssclib.h)
typedef struct {
	unsigned char verbose;
} SSCState;

static SSCState *ssc_state = 0x0;

/* ============================================================ */

// @Note: maybe put this in the source code
static char const ident_chars[] =\
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOP1234567890"\
    "1234567890"\
    "!$%&*+-./:<=>?@^_~";

// @Note: list should be implemented as a list of pair
// so don't try to be clever and make a O(1) complexity
// list type. For this will implement vector

// @Note: symbol has to be implemented as a pointer- whatever that means
// @Note2: symbols should be implemented using a hash table.

typedef struct Sym {
	char const *name;
	// @Todo move this to another file
} Sym;

typedef struct Expr {
	enum {
		e_nil,
		e_integer,
		e_symbol,
		e_pair,
		e_error,
	} type;
	union {
		int       integer;
		struct Sym   *sym;
		struct Pair  *pair;
		struct Error *err;
	} s_expr;
} Expr;

typedef struct Env {
	// @Todo
	struct Env *parent;
} Env;

/* ============================================================ */

Expr *mk_expr(int expr_type, ...);

Expr *eval(SSCState *state, Expr *expr);

void  display(Expr *expr);
void  display_nested(Expr *expr, char nested);

#endif /* _SSC_H */
