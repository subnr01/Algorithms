/** @brief contains assembly functions for
* thread create, mainly thread_fork, thr_exit_wrapper, prep_child,
* 
* this allows us to do clever little x86 tricks
*/
#include <_wrapper_macros.h>

.globl thread_fork
.globl prep_child2
.globl prep_child
.globl thr_exit_wrapper

/* assembly wrapper function for invoking fork syscall
*  arguments
* we save the child stack location in ebx so that
* regardless of if the parent overwrites the stack location
* the child will the address it needs to go to directly in
* its register
* we also save the base of the ebp as the child stack
*/
thread_fork:
    push %ebx            // callee saved register
    push %edi            // callee saved register
    mov 12(%esp), %ebx    // save esp start location
    mov 16(%esp), %edi    // save thread stack start location
    int $THREAD_FORK_INT // invoke thread_fork system call
    cmp $0, %eax         // test to see if child or parent
    je child            //go to child if eax val != 0
    pop %edi
    pop %ebx             //restore register
    ret
    child:
        mov %ebx, %esp  // move to child stack, ebp doesn't matter
        mov %edi, %ebp  // set ebp
        ret

/* pushes appropriate functions onto the childs stack
*  args: in order
*       28: function args
*       24: thr_exit_wrapper raddr
*       20: data ptr
*       16: function return address
*       12: return address data init function
*       8: location of the child stack
* returns initial esp value in the stack
*/
prep_child:
    push %ebp           //following conventions
    mov  %esp, %ebp     //we do this to make argument referencing easy
    movl  8(%ebp), %esp //move to the child thread stack
    pushl 20(%ebp)      //  function args
    pushl 16(%ebp)       //  function 
    pushl 12(%ebp)       // data pointer
    pushl 8(%ebp)        //fake return address
    pushl 24(%ebp)       //address of the child_launcher function
    mov %esp, %eax      // prep return value
    mov %ebp, %esp      // return to normal stack
    pop %ebp           //restore old ebp
    ret



