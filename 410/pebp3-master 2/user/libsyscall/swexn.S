#include <_wrapper_macros.h>
.globl swexn

/* assembly wrapper function for invoking swexn syscall */
swexn:
    SYSCALL_MULTI_ARG
    int $SWEXN_INT /* invoke swexn system call */
    SYSCALL_END
    ret 

