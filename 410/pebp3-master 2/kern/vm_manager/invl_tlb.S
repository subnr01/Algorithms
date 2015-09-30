/** @file invl_tlb.S
 *  @brief invalidate tlb entry module implementation file
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs 
 */
.globl invl_tlb

invl_tlb:
    mov 4(%esp), %eax
    invlpg (%eax)
    ret
