#include <_wrapper_macros.h>
.globl readfile

/* assembly wrapper function for invoking readfile syscall */
readfile:
    SYSCALL_MULTI_ARG
    int $READFILE_INT /* invoke readfile system call */
    SYSCALL_END
    ret

