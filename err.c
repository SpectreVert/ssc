/*
 * Created by Costa Bushnaq
 *
 * 12-10-2021 @ 15:06:54
*/

#include <stdio.h>

#include "err.h"
#include "util.h"

char *err_msgs[] = {
    [e_default]  = "<default error message>",
    [e_bad_expr] = "unrecognized expression %s",   /* don't really know */
	[e_unk_var]  = "variable %s is not bound",              /* var name */
	[e_non_proc] = "attempt to apply non-procedure %s",     /* proc name */
	[e_num_args] = "incorrect argument count in call (%s)", /* proc name */
	[e_bad_arg]  = "%s is not %s", /* object name, wanted type */
};

// @Todo: make ctx argument variable argument
Error *mk_error(int error_type, char const *obj, char const *ctx)
{
    Error *new_err = ssc_malloc(sizeof(*new_err));

    new_err->type = error_type;
    new_err->obj = ssc_strdup(obj);
    if (ctx)
        new_err->ctx = ssc_strdup(ctx);

    return new_err;
}

char *get_err_msg(Error err)
{
    static char msg[ERROR_BUFFER_SIZE];

    if (err.type == e_bad_arg) {
        snprintf(msg, ERROR_BUFFER_SIZE, err_msgs[e_bad_arg], err.obj, err.ctx);
    } else {
        snprintf(msg, ERROR_BUFFER_SIZE, err_msgs[err.type], err.obj);
    }

    return msg;
}
