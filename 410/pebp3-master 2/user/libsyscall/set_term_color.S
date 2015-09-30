#include <_wrapper_macros.h>
.globl set_term_color

/* assembly wrapper function for invoking set_term_color syscall */
set_term_color:
    SYSCALL_4_BYTE_ARG
    int $SET_TERM_COLOR_INT /* invoke set_term_color syscall */
    SYSCALL_END
    ret

