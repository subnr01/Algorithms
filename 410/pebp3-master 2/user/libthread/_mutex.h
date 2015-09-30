/** @file _mutex.h
 *  @brief private function prototypes and macros for mutex.c
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */

#ifndef _MUTEX_H
#define _MUTEX_H

#include <mutex_type.h>
#include <thr_internals.h>
#include <thread_queue.h>
#include <stddef.h>
#include <syscall.h>
#include <atomic_swap.h>

/** @brief Constants which indicate victory in various lock races
 */
#define SLOT_WIN (0)  //!< many competitors
#define DUEL_WIN (1) //!< only two competitors
#define DUEL_TRY (0) //!< only two competitors

/** @brief Constant used to mark a mutex as destroyed
 */
#define MUTEX_DESTROYED (-1)

/* there is no race condition doing this check.
 *   1. if I had the lock before, there is no race condition against
 *   myself.
 *   2. If I didn't, no race condition is going to put me there.
 */
#define VERIFY_LOCK(mutexp) \
    (q_get_runthread(mutexp->head) == thr_getid())

void mutex_queue_lock(mutex_t *, q_node *);
void mutex_queue_unlock(mutex_t *, q_node *);

/* The reason why we have this two functions is caused by the race
 * condition between make_runnable() and deschedule().
 * These two functions couldn't and shouldn't be put in any mutex,
 * especially deschedule().
 * Calling run_next_thread implicates that you are absolutely sure the
 * thread passed to the function is descheduled or going to be
 * descheduled. And shouldn't take too long.
 */
void run_next_thread(int next_tid);
void yield_until_desche(int next_tid);
void set_slot(q_node *, int slot);
int  get_slot(q_node *);

#endif /* _MUTEX_H */
