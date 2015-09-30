#include <_wrapper_macros.h>
.globl wait

/* assembly wrapper function for invoking wait syscall */
wait:
    SYSCALL_4_BYTE_ARG
    int $WAIT_INT /* invoke wait system call */
    SYSCALL_END
    ret

