#include <_wrapper_macros.h>
.globl set_status

/* assembly wrapper function for invoking set_status syscall */
set_status:
    SYSCALL_4_BYTE_ARG
    int $SET_STATUS_INT /* invoke set_status syscall */
    SYSCALL_END
    ret

