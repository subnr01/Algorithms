.globl set_term_color_wrapper

set_term_color_wrapper:
    push %esi
    call set_term_color_handler
    pop %esi
    iret
