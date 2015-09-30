.globl sleep_wrapper

sleep_wrapper:
    push %esi
    call sleep_handler
    pop %esi
    iret
