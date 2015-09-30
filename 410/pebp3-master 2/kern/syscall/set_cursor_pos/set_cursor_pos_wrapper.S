.globl set_cursor_pos_wrapper

set_cursor_pos_wrapper:
    push %esi
    call set_cursor_pos_handler
    pop %esi
    iret
