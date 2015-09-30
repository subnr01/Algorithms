/** @file sem_type.h
 *  @brief This file defines the type for semaphores.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */
#ifndef _SEM_TYPE_H
#define _SEM_TYPE_H

#include <mutex.h>
#include <thread_queue.h>


typedef struct sem {
    /* semaphore internal lock */
    mutex_t lock_space;
    mutex_t* internal_lock;

    int count;

    /* queue for those who have to wait */
    q_node queue_space;
    q_node *wait_queue;

} sem_t;

#endif /* _SEM_TYPE_H */
