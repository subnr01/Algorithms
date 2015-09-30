.globl wait_wrapper

wait_wrapper:
    push %esi
    call wait_handler
    pop %esi
    iret
