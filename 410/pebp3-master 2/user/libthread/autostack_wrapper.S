/** @file autostack_wrapper.S
 *  @brief autostack_wrapper implementation
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */

.globl handler_wrapper

/* I use this wrapper to pop out those things stored in ureg.
 * for more details about the layout of stack, it's in the 'autostack.c'
 * file.
 */
handler_wrapper:
    call stackgrowth_handler
