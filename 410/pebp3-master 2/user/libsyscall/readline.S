#include <_wrapper_macros.h>
.globl readline

/* assembly wrapper function for invoking readline syscall */
readline:
    SYSCALL_MULTI_ARG
    int $READLINE_INT /* invoke readline system call */
    SYSCALL_END
    ret

