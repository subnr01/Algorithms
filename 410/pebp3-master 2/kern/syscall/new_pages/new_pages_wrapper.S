.globl new_pages_wrapper

new_pages_wrapper:
    push %esi
    call new_pages_handler
    pop %esi
    iret
