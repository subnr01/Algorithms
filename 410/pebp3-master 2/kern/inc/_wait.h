/** @file _wait.h
 *  @brief Main wait functionality module header file.
 *
 *  @author Hongchao Deng (hongchad)
 */
#ifndef __WAIT_H
#define __WAIT_H

#include <queue.h>
#include <klock.h>

typedef struct _wait_t{
    int exit_status;

    kmutex_t vanish_mutex;
    kmutex_t wait_mutex;
    spinlock_t wait_lock;
    spinlock_t thr_vanish_lock;

    queue_t wait_queue;

    queue_t zombie_queue;
    qnode_t zombie_qnode;
} wait_t;

void set_init_pcb(void *pcb);

void wait_item_init( wait_t *wait_item, void *pcb);
void wait_set_status(wait_t* wait_item, int status);

void _vanish();
int _wait(int *);

void thr_vanish_lock(wait_t *);
void thr_vanish_unlock(wait_t *);

#endif // for #ifndef __WAIT_H
