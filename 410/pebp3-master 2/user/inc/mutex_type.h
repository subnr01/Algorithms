/** @file mutex_type.h
 *  @brief This file defines the type for mutexes.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */

#ifndef MUTEX_TYPE_H
#define MUTEX_TYPE_H
#include <thread_queue.h>

/** @brief mutex data structure
 */
typedef struct _mutex_t{
    int slot; //!< free for all lock
    int duel; //!< 1 vs 1 lock

    /*
     * last_final_thread and next_first_thread are global values for
     * on very specific case that only the last thread in the last
     * group and the first thread in the next group will compete
     * and notify each other
     */
    int last_final_thread; //!< id of first thread of last group
    int next_first_thread; //!< id of first thread of next group

    /* two players' id for duel */
    int player_lock, player_unlock;

    /* first in first out queue to run thread one by one */
    q_node * head;

    /*
     * Reserved variable space. Queue head will points to this variable.
     * The reason why I do this is that I wanna keep pointer all round
     * and malloc should not be called in this library. Just a little trick..
     */
    q_node head_space;


} mutex_t;

#endif /* _MUTEX_H */
