/** @file scheduler.c
 *  @brief scheduler module implementation file
 *
 *  This is the scheduler module. The scheduler is a shared resources
 *  between all processes and threads around the kernel. In order to
 *  protect it, we're ensuring interrupts disabled when adding or deleting
 *  entities for the scheduler run queue.
 *
 *  The scheduler has a run queue. The run queue contains all the runnable
 *  threads except the running one which is in cpu. When timer goes off
 *  or the running thread voluntarily or involuntarily gives up cpu (i.e.,
 *  keyboard input, thread vanished), the scheduler will decide the next
 *  one to run. Normally it's the head item in FIFO queue.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <scheduler.h>
#include <stddef.h>
#include <tcb.h>
#include <queue.h>
#include <cpu.h>
#include <eflags.h>
#include <asm.h>


#define KERNLOG_L1_ON
#include <kernlog.h>

static scheduler_t scheduler;

/** @brief schedueler init function
 *  @return Void.
 */
void
scher_init()
{
    q_init( & scheduler.run_queue );
}

/** @brief ask schedueler to do rescheduling.
 *
 *  This will switch the currently running thread out and switch the
 *  next thread in run queue into the cpu.
 *
 *  @return Void.
 */
void scher_resche()
{
    cpu_relax();
}

/** @brief Pop the next thread in run queue.
 *
 *  @return The next thread in run queue. NULL if there's no one.
 */
tcb_t*
scher_pop_job()
{
    if( q_empty( & scheduler.run_queue ) ) {
        return NULL;
    }

    return get_tcb_from_qnode(
      q_pop(& scheduler.run_queue) );
}

/** @brief Add the very important thread to be the next one in run queue
 *
 *  @param tcb The thread to be added
 *  @return Void.
 */
void
scher_add_front_job(tcb_t *tcb)
{
    q_insert_front( & scheduler.run_queue, & tcb->thr_sched);
}


/** @brief Add the thread to run queue (last place).
 *
 *  @param tcb The thread to be added
 *  @return Void.
 */
void
scher_push_job(tcb_t *tcb)
{
    q_push( & scheduler.run_queue, & tcb->thr_sched );
}

/** @brief delete the thread from run queue.
 *
 *  This is useful in yield when a thread is taken from the run queue
 *  and then added into the first place.
 *
 *  @param tcb The thread to be deleted
 *  @return Void.
 */
void
scher_delete_job(tcb_t *tcb)
{
    q_remove( & scheduler.run_queue, & tcb->thr_sched);
}

/** @brief Add the newly forked thread to run queue.
 *
 *  This is different because we need to disable the interrupts to
 *  protect it.
 *
 *  @param tcb The thread to be deleted
 *  @return Void.
 */
void
scher_add_newlycreated(tcb_t *tcb)
{
    disable_interrupts(); {
        scher_push_job(tcb);
    } enable_interrupts();

}

/** @brief Test if there's other running thread in runqueue.
 *
 *  @return 1 if having some other running thread. 0 if not.
 */
int
scher_no_other_runthr()
{
    return q_empty(&scheduler.run_queue);
}


