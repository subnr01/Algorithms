/** @file pagefault_wrapper.S
    @brief this file contains code for saving and restoring register
    state encountered during page fault exceptions

    @author Alan Keith (arkeith)
    @author Hongchao Deng (hongchad)
    @bugs no known bugs

    Limitations: the ureg_t object passed to the fault handler
    will not be correct if the fault was a kernellevel fault
*/

#include <ureg.h>


.globl pagefault_wrapper

pagefault_wrapper:
// SS
// ESP
// EFLAGS
// CS
// EIP
// Error Code
        pusha
        movl $0, 12(%esp)
// eax
// ecx
// edx
// ebx
// zero
// ebp
// edi
// esi
        push %gs
        push %fs
        push %es
        push %ds
// gs, fs, es, ds

        movl %cr2, %eax // %eax has been saved by 'pusha'
        push %eax
// cr2
        pushl $SWEXN_CAUSE_PAGEFAULT
// cause

        call pagefault_handler

        pop %eax // cause
        pop %eax // cr2

        pop %ds
        pop %es
        pop %fs
        pop %gs
        popa

        addl $4, %esp // error code

        iret
