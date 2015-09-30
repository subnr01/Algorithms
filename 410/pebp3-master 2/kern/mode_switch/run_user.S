/** @file run_user.S
    @brief contains code for launching a user process for the first time
*/
#include <seg.h>
#include <eflags.h>

.globl run_user

/** @brief preps the stack for an iret instruction and envokes iret

    This function will set up the stack like so
    SS
    ESP
    EFLAGS
    CS
    EIP <-esp points here

    we also change the user data segment before envoking iret
*/
iret_airship:
    push $SEGSEL_USER_DS  // SS
    push 12(%ebp)         // user process ESP
    pushf                 // EFlags

    // arrange eflags for user mode
    mov $EFL_RESV1, %eax   // set reversed bit 1
    or $EFL_IF, %eax // set interrupt flag
    or $EFL_IOPL_RING0, %eax // set IOPL_KERNEL to ring 0
    or %eax, (%esp)

    mov $EFL_AC, %eax
    not %eax
    and %eax, (%esp) // set alignment checking off

    push $SEGSEL_USER_CS  // CS
    push 8(%ebp)          // EIP: entry point

    mov $SEGSEL_USER_DS, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %fs
    mov %eax, %gs

    iret
    jmp run_user_error //we shouldn't get here



/** @brief launch user process for the first time
    takes two arguments
    ret
    old ebp
    one is function entry point (ebp+8)
    the other is stack location (ebp+12)
*/

run_user:
    // we need to disable interrupts:
    // There could be a race that when we're doing mode switch and
    // setting register values other than the general 8 ones, a context
    // switch happens!
    cli
    push %ebp
    mov %esp, %ebp

    jmp iret_airship

run_user_error:
    mov %ebp, %esp //something went very very wrong if we get here
    pop %ebp
    ret

