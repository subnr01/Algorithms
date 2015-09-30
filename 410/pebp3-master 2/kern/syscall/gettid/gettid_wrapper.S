.globl gettid_wrapper

gettid_wrapper:
    call gettid_handler
    iret
