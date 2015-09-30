/** @file desche.c
 *  @brief deschedule and make_runnable kernel module implementation
 *  file
 *
 *  The deschedule function is easy. Marking it and then release contron
 *  of cpu will simply not add itself back to run queue.
 *
 *  The make runnable function is a bit more complicated. We need to
 *  eliminate a race between multiple threads trying to make run the
 *  same thread concurrently. The wake up process consists of two
 *  steps: 1. change the thread state. 2. add it back to run queue so
 *  that he will have chance to run again.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith
 */
#include <sched.h>
#include <tid_table.h>
#include <stddef.h>
#include <scheduler.h>
#include <asm.h>
#include <tcb.h>
#include <cpu.h>
#include <klock.h>


void desche(){
    tcb_t *tcb = get_cur_tcb();

    disable_interrupts();{
        desche_thr(tcb); // won't be added back to run queue
    } cpu_relax();
}


int make_run(int tid){
    tcb_t *tcb;

    // powerfully supported by my internal thread table...
    tcb = (tcb_t *) tidtable_search(tid);

    // non existent
    if(tcb == NULL) return -1;

    // Doing this to eliminate one race condition:
    // two threads could be trying to make the same thread runnable
    // concurrently. But only one can activate it.

    kmutex_lock ( & tcb->makerun_mutex);{

        if( ! is_thr_desche(tcb)){
            // function failed if the thread isn't descheduled at check
            kmutex_unlock ( & tcb->makerun_mutex);
            return -1;
        }

        activate_thr(tcb);
    } kmutex_unlock ( & tcb->makerun_mutex);

    disable_interrupts();{
        // The one who activate the descheduled is responsible for
        // adding it back to run queue.
        scher_push_job(tcb);
    } enable_interrupts();

    return 0;
}


