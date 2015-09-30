.globl print_wrapper

print_wrapper:
    push %esi
    call print_handler
    pop %esi
    iret
