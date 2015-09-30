.globl remove_pages_wrapper

remove_pages_wrapper:
    push %esi
    call remove_pages_handler
    pop %esi
    iret
