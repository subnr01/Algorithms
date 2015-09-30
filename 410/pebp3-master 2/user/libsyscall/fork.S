#include <_wrapper_macros.h>
.globl fork

/* assembly wrapper function for invoking fork syscall */
fork:
    int $FORK_INT /* invoke fork system call */
    ret

