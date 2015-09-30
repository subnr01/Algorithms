/** @file spinlock.c
 *
 *  The spin lock could be released when interrupts are disabled.
 *
 *  @author Hongchao Deng (hongchad)
 */
#include <klock.h>
#include <cpu.h>
#include <assert.h>
#include <stddef.h>

#define LOCK_BUSY 1

void
spin_init(spinlock_t *lock)
{
    *lock = !LOCK_BUSY;
}

void
spin_lock(spinlock_t *lock)
{
    assert(lock != NULL);
    while(1){
        if( spin_trylock(lock) ) return;
        while(*lock == LOCK_BUSY) cpu_relax();
    }
}

void
spin_unlock(spinlock_t *lock)
{
    assert(lock != NULL);
    __sync_lock_release(lock);
}

int
spin_trylock(spinlock_t *lock)
{
    assert(lock != NULL);
    return
      __sync_bool_compare_and_swap(lock, ! LOCK_BUSY, LOCK_BUSY);
}
