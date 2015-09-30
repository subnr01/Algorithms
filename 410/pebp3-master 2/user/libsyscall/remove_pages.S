#include <_wrapper_macros.h>
.globl remove_pages

/* assembly wrapper function for invoking remove_pages syscall */
remove_pages:
    SYSCALL_4_BYTE_ARG
    int $REMOVE_PAGES_INT /* invoke remove_pages syscall */
    SYSCALL_END
    ret

