#include <_wrapper_macros.h>
.globl task_vanish

/* assembly wrapper function for invoking task_vanish syscall */
task_vanish:
    SYSCALL_4_BYTE_ARG
    int $TASK_VANISH_INT /* invoke task_vanish syscall */
    SYSCALL_END
    ret

