.globl get_cursor_pos_wrapper

get_cursor_pos_wrapper:
    push %esi
    call get_cursor_pos_handler
    pop %esi
    iret
