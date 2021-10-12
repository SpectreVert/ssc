/*
 * Created by Costa Bushnaq
 *
 * 12-10-2021 @ 14:10:40
 *
 * see LICENSE
*/

#ifndef _ERR_H
#define _ERR_H

#include <stddef.h>

#define ERROR_BUFFER_SIZE 256

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
	// @Todo: maybe find a way to send the entire object (Expr)
	// will have to see if this is needed
	char *obj; /* the thing on where error occured */
	char *ctx; /* optional context */
} Error;

extern char *err_msgs[];

Error *mk_error(int error_type, char const *obj, char const *ctx);
char *get_err_msg(Error err);

#endif /* _ERR_H */
