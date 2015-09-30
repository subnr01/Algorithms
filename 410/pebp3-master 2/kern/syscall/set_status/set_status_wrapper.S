.globl set_status_wrapper

set_status_wrapper:
    push %esi
    call set_status_handler
    pop %esi
    iret
