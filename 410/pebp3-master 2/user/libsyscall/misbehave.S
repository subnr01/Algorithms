#include <_wrapper_macros.h>
.globl misbehave

/* assembly wrapper function for invoking misbehave syscall */
misbehave:
    SYSCALL_4_BYTE_ARG
    int $MISBEHAVE_INT /* invoke misbehave syscall */
    SYSCALL_END
    ret

