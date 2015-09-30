/** @file switch_cpustate.S
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
.globl switch_cpustate
.globl _fork_switchret


// 8(%ebp) = address of the save_esp of prev_tcb
// 12(%ebp) = save_esp value of next_tcb
switch_cpustate:
    push %ebp
    mov %esp, %ebp

    pusha
    mov 8(%ebp), %eax
    mov %esp, (%eax)

    mov 12(%ebp), %esp
    popa

    leave
    ret

_fork_switchret:
    sti
    leave
    ret

