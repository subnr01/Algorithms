#include <_wrapper_macros.h>
.globl halt

/* assembly wrapper function for invoking halt syscall */
halt:
    int $HALT_INT /* invoke halt syscall */
    ret

