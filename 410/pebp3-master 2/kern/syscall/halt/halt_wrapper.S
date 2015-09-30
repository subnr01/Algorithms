.globl halt_wrapper

halt_wrapper:
    HLT // after all, I found this
    call halt_handler
    iret
