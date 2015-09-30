#include <_wrapper_macros.h>
.globl deschedule

/* assembly wrapper function for invoking deschedule syscall */
deschedule:
    SYSCALL_4_BYTE_ARG
    int $DESCHEDULE_INT /* invoke deschedule syscall */
    SYSCALL_END
    ret

