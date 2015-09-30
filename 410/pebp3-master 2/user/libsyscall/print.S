#include <_wrapper_macros.h>
.globl print

/* assembly wrapper function for invoking print syscall */
print:
    SYSCALL_MULTI_ARG
    int $PRINT_INT /* invoke print system call */
    SYSCALL_END
    ret

