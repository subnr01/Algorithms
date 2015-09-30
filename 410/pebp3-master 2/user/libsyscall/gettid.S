#include <_wrapper_macros.h>
.globl gettid

/* assembly wrapper function for invoking gettid syscall */
gettid:
    int $GETTID_INT /* invoke gettid system call */
    ret

