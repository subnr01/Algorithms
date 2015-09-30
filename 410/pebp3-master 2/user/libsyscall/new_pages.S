#include <_wrapper_macros.h>
.globl new_pages

/* assembly wrapper function for invoking new_pages syscall */
new_pages:
    SYSCALL_MULTI_ARG
    int $NEW_PAGES_INT /* invoke new_pages system call */
    SYSCALL_END
    ret


