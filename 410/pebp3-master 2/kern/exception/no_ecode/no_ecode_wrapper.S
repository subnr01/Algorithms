/** @file has_ecode_wrapper.S
    @brief this file implements wrapper assembly function for exceptions
    that has error code.

*/

#include <ureg.h>
#include "../wrapper_macro.h"

.globl DE_wrapper
.globl DB_wrapper
.globl BP_wrapper
.globl OF_wrapper
.globl BR_wrapper
.globl UD_wrapper
.globl NM_wrapper
.globl MF_wrapper
.globl MC_wrapper
.globl XF_wrapper

XF_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_SIMDFAULT

        call DE_handler
        jmp return_place
MC_wrapper:
        pushl 0
        PREP_UREG
        pushl 0

        call DE_handler
        jmp return_place
MF_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_FPUFAULT

        call DE_handler
        jmp return_place
NM_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_NOFPU

        call DE_handler
        jmp return_place
UD_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_OPCODE

        call DE_handler
        jmp return_place
BR_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_BOUNDCHECK

        call DE_handler
        jmp return_place
OF_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_OVERFLOW

        call DE_handler
        jmp return_place
BP_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_BREAKPOINT

        call DE_handler
        jmp return_place
DB_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_DEBUG

        call DE_handler
        jmp return_place
DE_wrapper:
        pushl 0
        PREP_UREG
        pushl $SWEXN_CAUSE_DIVIDE

        call DE_handler
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



