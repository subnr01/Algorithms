#include <_wrapper_macros.h>
.globl get_cursor_pos

/* assembly wrapper function for invoking get_cursor_pos syscall */
get_cursor_pos:
    SYSCALL_MULTI_ARG
    int $GET_CURSOR_POS_INT /* invoke get_cursor_pos system call */
    SYSCALL_END
    ret

