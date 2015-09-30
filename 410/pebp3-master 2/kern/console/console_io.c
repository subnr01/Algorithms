/** @file console_io.c
 *  @brief console io module implementation file
 *
 *  During readline, the calling thread must block and wait if there's
 *  no keys left in the keyboard buffer. Additionally, other threads
 *  must block and wait its turn to access the input stream if there has
 *  some other already descheduled previously.
 *
 *  This module is intended to handle these issues. It has a io wait
 *  queue to record blocked threads. It wakes threads up in the order
 *  they were descheduled one by one.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs
 */
#include <console_io.h>
#include <scheduler.h>
#include <tcb.h>
#include <cpu.h>
#include <queue.h>


static queue_t io_wait;

/** @brief console io init function
 */
void console_io_init()
{
    q_init(& io_wait);
}

/** @brief check is there anyone in IO wait queue
 *  @return 1 if there is. 0 if no one.
 */
int console_io_has_waiting()
{
    return !q_empty(&io_wait);
}

/** @brief IO block calling thread
 */
void console_io_wait(tcb_t *tcb)
{
    q_push( & io_wait, & tcb->thr_sched);
    ioblock_thr(tcb);
    cpu_relax();
}

/** @brief add the first item in wait queue to first place in run queue
 *  and context switch him in.
 */
void console_io_wakeup_next()
{
    qnode_t *thr_sched;
    tcb_t *tcb;

    thr_sched = q_pop(& io_wait);
    tcb = get_tcb_from_qnode(thr_sched);

    scher_add_front_job(tcb);
    cpu_relax(); // current thread yield to woken-up one
}
