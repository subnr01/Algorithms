#include <_wrapper_macros.h>
.globl vanish

/* assembly wrapper function for invoking vanish syscall */
vanish:
    int $VANISH_INT /* invoke vanish system call */
    ret

