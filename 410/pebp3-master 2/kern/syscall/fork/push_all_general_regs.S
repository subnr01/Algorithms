.globl push_all_general_regs

push_all_general_regs:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %esp
    pusha

    // stores the value of address before pusha to saved %ebp
    leal 32(%esp), %eax
    mov %eax, 8(%esp)

    leave
    ret
