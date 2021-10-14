/*
 * Created by Costa Bushnaq
 *
 * 14-10-2021 @ 22:51:46
 *
 * see LICENSE
*/

#ifndef _NODE_H
#define _NODE_H

#include <stdarg.h>
#include <stddef.h>

struct Expr;

// @Todo: remove this file and implement lists in the cons
typedef struct Node {
	struct Expr **leaves;
	size_t size;
} Node;

Node *mk_node(size_t size, ...);
Node *mk_node_va_list(size_t size, va_list al);

#endif /* _NODE_H */
