/** @file has_ecode_wrapper.S
    @brief this file implements wrapper assembly function for exceptions
    that has error code.

*/

#include <ureg.h>
#include "../wrapper_macro.h"

.globl TS_wrapper
.globl NP_wrapper
.globl SS_wrapper
.globl GP_wrapper
.globl AC_wrapper

AC_wrapper:
        PREP_UREG
        pushl $SWEXN_CAUSE_ALIGNFAULT

        call TS_handler
        jmp return_place

GP_wrapper:
        PREP_UREG
        pushl $SWEXN_CAUSE_PROTFAULT

        call TS_handler
        jmp return_place

SS_wrapper:
        PREP_UREG
        pushl $SWEXN_CAUSE_STACKFAULT

        call TS_handler
        jmp return_place

NP_wrapper:
        PREP_UREG
        pushl $SWEXN_CAUSE_SEGFAULT

        call TS_handler
        jmp return_place

TS_wrapper:
        PREP_UREG
        pushl 0

        call TS_handler
        jmp return_place

return_place:
        pop %eax // cause
        pop %eax // cr2

        pop %ds
        pop %es
        pop %fs
        pop %gs
        popa

        addl $4, %esp // error code

        iret
