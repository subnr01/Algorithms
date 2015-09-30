#include <_wrapper_macros.h>
.globl yield

/* assembly wrapper function for invoking yield syscall */
yield:
    SYSCALL_4_BYTE_ARG
    int $YIELD_INT /* invoke yield syscall */
    SYSCALL_END
    ret

