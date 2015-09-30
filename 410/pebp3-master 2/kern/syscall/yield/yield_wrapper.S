.globl yield_wrapper

yield_wrapper:
    push %esi
    call yield_handler
    pop %esi
    iret
