.globl readfile_wrapper

readfile_wrapper:
    push %esi
    call readfile_handler
    pop %esi
    iret
