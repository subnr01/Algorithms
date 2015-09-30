.globl deschedule_wrapper

deschedule_wrapper:
    push %esi
    call deschedule_handler
    pop %esi
    iret
