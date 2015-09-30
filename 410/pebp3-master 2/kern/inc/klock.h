/** @file klock.h
 *
 *  For my kernel I have two types of lock.
 *
 *  The first one, spin yield, while it could lengthen run queue and
 *  slow down cpu speed, could be released when interrupts are disabled.
 *
 *  The second one, which is a real lock that puts threads to sleep,
 *  could not be released when interrupts are disabled.
 *
 *  @author Hongchao Deng (hongchad)
 */
#ifndef _KLOCK_H
#define _KLOCK_H

#include <queue.h>

/******* spinlock ***********/

typedef int spinlock_t;

void spin_init(spinlock_t *lock);
void spin_lock(spinlock_t *lock);
void spin_unlock(spinlock_t *lock);
int spin_trylock(spinlock_t *lock);

/******* mutex ***********/

typedef struct _kmutex_t {
    int flag;
    spinlock_t lock;
    queue_t wait_queue;
} kmutex_t;


void kmutex_init(kmutex_t *kmu);
void kmutex_lock(kmutex_t *kmu);
void kmutex_unlock(kmutex_t *kmu);


#endif // for #ifndef _KLOCK_H
