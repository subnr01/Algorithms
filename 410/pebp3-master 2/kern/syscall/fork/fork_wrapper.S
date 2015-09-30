.globl fork_wrapper
.globl _fork_forkwrapper
.globl thread_fork_wrapper

fork_wrapper:
    push %ebp
    push %ebx
    push %edi
    push %esi

    call fork_handler

    pop %esi
    pop %edi
    pop %ebx
    pop %ebp

    iret

_fork_forkwrapper:
    pop %esi
    pop %edi
    pop %ebx
    pop %ebp

    xor %eax, %eax //return 0
    iret

thread_fork_wrapper:
    push %ebp
    push %ebx
    push %edi
    push %esi

    call thread_fork_handler

    pop %esi
    pop %edi
    pop %ebx
    pop %ebp

    iret
