#include <_wrapper_macros.h>
.globl set_cursor_pos

/* assembly wrapper function for invoking set_cursor_pos syscall */
set_cursor_pos:
    SYSCALL_MULTI_ARG
    int $SET_CURSOR_POS_INT /* invoke set_cursor_pos system call */
    SYSCALL_END
    ret

