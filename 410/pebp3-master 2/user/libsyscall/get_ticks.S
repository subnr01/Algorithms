#include <_wrapper_macros.h>
.globl get_ticks

/* assembly wrapper function for invoking get_ticks */
get_ticks:
    int $GET_TICKS_INT /* invoke get_ticks system call */
    ret
