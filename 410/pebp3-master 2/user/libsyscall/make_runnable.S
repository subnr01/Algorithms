#include <_wrapper_macros.h>
.globl make_runnable

/* assembly wrapper function for invoking make_runnable syscall */
make_runnable:
    SYSCALL_4_BYTE_ARG
    int $MAKE_RUNNABLE_INT /* invoke make_runnable syscall */
    SYSCALL_END
    ret

