.globl readline_wrapper

readline_wrapper:
    push %esi
    call readline_handler
    pop %esi
    iret
