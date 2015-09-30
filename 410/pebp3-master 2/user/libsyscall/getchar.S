#include <_wrapper_macros.h>
.globl getchar

/* assembly wrapper function for invoking getchar syscall */
getchar:
    int $GETCHAR_INT /* invoke getchar syscall */
    ret

