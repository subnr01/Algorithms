/** @file exception.c
 *  @brief contains the generic exception handler for most exceptions
 *
 *  This is the common  exception handler, it will attempt to pass things to a
 *  user handler if one is installed, otherwise it kills the thread
 *
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 *  @bugs No known bugs
 */
#include <ureg.h>
#include <tcb.h>
#include <vanish.h>

void
exception_handler(ureg_t *context)
{
    tcb_t *tcb;

    tcb = get_cur_tcb();

    if (tcb->user_handler != 0){
        //deregister handler and invoke
        swexn_handler_t handler = tcb->user_handler;
        tcb->user_handler = 0;

        uintptr_t esp3 = tcb->swexn_esp3;
        tcb->swexn_esp3 = 0;

        void *args = tcb->args;
        tcb->args = 0;

        user_handler_launcher(args, context, esp3, handler);
    }
    else{
        // kill the thread
        set_status_handler(-2);
        vanish_handler();
    }
}
