/** @file swexn_wrapper.S
    @brief assembly wrapper for swexn and returning to a given register state

    @author Alan Keith (arkeith)
    @author Hongchao Deng (hongchad)
    @bugs No known bugs
*/

.globl swexn_wrapper
.globl swexn_restore_reg

swexn_wrapper:
    push %esi
    call swexn_handler
    pop %esi
    iret

/* we assume that the ureg_t struct has been passed
as an argument to this function so that the 
stack can be properly manipulated */
swexn_restore_reg:
    pop %eax //remove return address
    pop %eax // cause
    pop %eax // cr2

    pop %ds
    pop %es
    pop %fs
    pop %gs
    popa

    addl $4, %esp // error code
    iret 

