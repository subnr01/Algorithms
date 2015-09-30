#include <_wrapper_macros.h>
.globl exec

/* assembly wrapper function for invoking exec syscall */
exec:
    SYSCALL_MULTI_ARG
    int $EXEC_INT /* invoke exec system call */
    SYSCALL_END
    ret

