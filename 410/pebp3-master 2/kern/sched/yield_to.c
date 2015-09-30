/** @file yield_to.c
 *  @brief kernel yield module implementation file
 *
 *  This is kernel internal yield implementation file.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <sched.h>
#include <tid_table.h>
#include <asm.h>
#include <scheduler.h>
#include <cpu.h>
#include <stddef.h>
#include <tcb.h>
#include <klock.h>
#include <idle.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


/** @brief kernel yield function.
 *
 *  @param tid
 *  @return 0 on success.
 *          -1 if tid is invalid.
 *          -2 if the thread's already active.
 */
int yield_to(int tid)
{
    tcb_t *next_tcb;

    if(tid < 0 || tid == __idle_tid)
        return -1;

    if(tid == -1){
        cpu_relax();
        return 0;
    }
    else{
        // find tcb of the tid
        next_tcb = tidtable_search(tid);

        if( next_tcb == NULL && next_tcb == get_cur_tcb() )
            return -1;

        // reason why it needs to disable interrupts to check:
        // There is RACE CONDITION if not doing this.
        //
        // a thread is trying to yield to another. When he checked the
        // other thread is active. but if he's interrupted at this
        // very moment and the other one's descheduled. The yield
        // function will screw up.
        //
        // So the checking and scheduling should be done together
        // atomically

        // modify the run queue and yield cpu to the next one
        disable_interrupts();{

            if( ! is_thr_active(next_tcb) ){ // not in run queue
                enable_interrupts();
                return -2;
            }

            // take the next thread from its original place in run queue and
            // insert it to the first place
            scher_delete_job(next_tcb);
            scher_add_front_job(next_tcb);
        } cpu_relax();

        return 0;
    }
}
