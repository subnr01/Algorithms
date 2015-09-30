#include <_wrapper_macros.h>
.globl sleep

/* assembly wrapper function for invoking sleep syscall */
sleep:
    SYSCALL_4_BYTE_ARG
    int $SLEEP_INT /* invoke sleep syscall */
    SYSCALL_END
    ret

