.globl exec_wrapper

exec_wrapper:
    push %esi
    call exec_handler
    pop %esi
    iret
