/** @file autostack.c
 *  @brief Install automatic stack growth
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */
#include <_multi_thread.h>
#include <ureg.h>
#include <syscall.h>
#include <stddef.h>
#include <autostack_wrapper.h>
#include <syscall.h>
#include <simics.h>

/* the distance from the bottom of the main stack that we think is not far.
 * in this case we use 64MB as the maximum distance.
 */
#define DISTANCE_FROM_BOTTOM ( 16 * PAGE_SIZE)

/* check whether the address is far from the main stack bottom or not */
#define NOT_FAR_BELOW_BOTTOM( addr ) \
  ( ((uintptr_t) (addr) < main_stack_low ) && \
    ( main_stack_low < (uintptr_t) (addr) + DISTANCE_FROM_BOTTOM ) )

#define PAGE_ALIGN(addr) ((addr) & ~ (PAGE_SIZE -1))

/* this stack is reserved for the main stack growth handler function
 * stack.
 * Allocating by this way could make the stack run in .bss section and
 * unrelevant about the main stack (especially when the main stack run
 * into trouble like stack size not enough).
 */
#define SWEXN_STACK_SIZE (2*PAGE_SIZE)
char swexn_stack_space[SWEXN_STACK_SIZE];
#define SWEXN_STACK ( (void *) \
  ((uintptr_t)(&swexn_stack_space[SWEXN_STACK_SIZE -7] ) ))

#define RET_ADDR_SIZE 4

/** @brief handler function for the automatic stack growth
 *
 *  First, we check the fault cause reason.
 *  Second, if we are sure it's a stack growth fault, then we use the
 *  ureg passed to us.
 *  The stack layout will be:
 *      |ureg things|
 *      |*ureg      |
 *      |*arg       |
 *      |ret_addr   | the wrapper's
 *      |ret_addr   | this handler's
 *      |old %ebp   |
 *
 *
 *  @param ret_addr this is the return address of the wrapper function.
 *  @arg the first argument passed to the handler function.
 *  @ureg the ureg passed as the second argument of the handler
 *  function.
 *  @return Void.
 */
void stackgrowth_handler(void *arg, ureg_t *ureg)
{
    uintptr_t allocate_page;
    lprintf("arg %p located at %p", arg, &arg);
    lprintf("ureg_t located at %p", &ureg);
    if(ureg->cause == SWEXN_CAUSE_PAGEFAULT){
        lprintf("env %x address %p", multi_thread_flag, &multi_thread_flag);
        if( SINGLE_THREAD_ENV()) {
            if (NOT_FAR_BELOW_BOTTOM(ureg->esp) ){

            /*
             * allocate all those pages between the new address and the
             * main stack low address.
             * incrementally allocate page for stack. (some pages might
             * exist before)
             */
            allocate_page  = PAGE_ALIGN( ureg->esp );
            while(allocate_page < PAGE_ALIGN(GET_STACK_LOW_PTR())){
                new_pages((void*) allocate_page, PAGE_SIZE);
                allocate_page += PAGE_SIZE;
            }

            SET_STACK_LOW_PTR(PAGE_ALIGN(ureg->esp));


            swexn(SWEXN_STACK, &stackgrowth_handler, NULL, ureg);
            }
        }
        else if ( MULTI_THREAD_ENV() ) {
            MAGIC_BREAK;
            task_vanish(-1);
        }
    }
    else{
        task_vanish(-1);
    }

}

void
install_autostack(void *stack_high, void *stack_low)
{
    SET_SINGLE_THREAD_ENV();
    SET_STACK_LOW_PTR( stack_low );

    swexn(SWEXN_STACK, &stackgrowth_handler, NULL, NULL);
}
