/** @file rwlock_type.h
 *  @brief This file defines the type for reader/writer locks.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */

#ifndef _RWLOCK_TYPE_H
#define _RWLOCK_TYPE_H
#include <mutex.h>
#include <cond.h>


typedef struct rwlock {
    /* internal lock to protect inner data structure &*/
    mutex_t internal_lock_space;
    mutex_t *internal_lock;

    /* downgrade relevant */
    cond_t downgrade_cond_space;
    cond_t *downgrade_cond;
    int downgrading;

    /* reader conditional variable */
    cond_t reader_cond_space;
    cond_t *reader_cond;

    /* writer conditional variable */
    cond_t writer_cond_space;
    cond_t *writer_cond;

    int readers; // number of readers on the lock
    int writers; // number of writers on the lock
    int waiting_writers; // number of writers waiting on the lock

    int current_mode; // used to record current mode: READ or WRITE
} rwlock_t;

#endif /* _RWLOCK_TYPE_H */
