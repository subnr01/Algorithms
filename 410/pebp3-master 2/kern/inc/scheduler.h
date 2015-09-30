/** @file scheduler.h
 *  @brief scheduler header file
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @bug No known bugs.
 */
#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <queue.h>
#include <tcb.h>


typedef struct _scheduler_t {
    // run queue
    queue_t run_queue;

} scheduler_t;

void scher_init();
void scher_resche();
void scher_add_front_job(tcb_t *tcb);
tcb_t* scher_pop_job();
void scher_push_job(tcb_t *);
void scher_add_newlycreated(tcb_t *tcb);
int scher_no_other_runthr();
void scher_delete_job(tcb_t *tcb);

#endif // for #ifndef _SCHEDULER_H
