.globl make_runnable_wrapper

make_runnable_wrapper:
    push %esi
    call make_runnable_handler
    pop %esi
    iret
