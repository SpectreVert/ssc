/*
 * Created by Costa Bushnaq
 *
 * 14-10-2021 @ 23:02:37
*/

#include "ssc.h"
#include "node.h"
#include "util.h"

Node *mk_node(size_t size, ...)
{
    Node *node = ssc_malloc(sizeof(*node));
    VA_ARG_START(al, size);

    node->size = size;
    node->leaves = ssc_malloc(sizeof(Expr *) * size);
    for (size_t i = 0; i < size; ++i) {
        node->leaves[i] = VA_ARG(al, Expr *);
    }
    VA_ARG_END(al);

    return node;
}

Node *mk_node_va_list(size_t size, va_list al)
{
    Node *node = ssc_malloc(sizeof(*node));

    node->size = size;
    node->leaves = ssc_malloc(sizeof(Expr *) * size);
    for (size_t i = 0; i < size; ++i) {
        node->leaves[i] = VA_ARG(al, Expr *);
    }

    return node;
}
