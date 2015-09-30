.globl get_ticks_wrapper

get_ticks_wrapper:
    call get_ticks_handler
    iret
