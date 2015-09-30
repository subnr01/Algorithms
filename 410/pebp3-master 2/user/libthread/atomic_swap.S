.globl atomic_swap

/** Assembly for atomic swap
 * we atomically exchange value (second arg)
 * with the number stored in lock address (first arg)
 *
 * we put the value obtained from lock address in eax and ret
 */
atomic_swap:
    /* we use %ecx here because it's caller saved register and we wanna
     * use as few instructions as possible.
     *
     * Stack:
     *       |First Argument  |
     *       |Second Argument |
     *       |Return Address  | <- %ebp
     */
    movl 4(%esp), %ecx     /* put the lock address into ecx */
    movl 8(%esp), %eax     /* put the value into eax */
    LOCK XCHG %eax, (%ecx) /* atomically swap with value dereferenced by ecx */
    ret                    /* value from lock already in eax */
