/** @file mutex.c
 *
 *  The mutex puts threads to sleep when they don't acquire the lock.
 *  But the mutex could not be released when interrupts are disabled.
 *
 *  The mutex design:
 *  1. every mutex have a spin lock to mainly prevent race between lock
 *  and unlock.
 *  2. mutex has wait queue to push those threads who didn't acquire the
 *  lock successfully.
 *
 *  """ NOTE:
 *  3. At first, I have made a bad decision and I don't have time to fix
 *  it later. However, this thing works fine. The bad decision is that I
 *  use the same qnode for the scheduler in the wait queue of mutex.
 *  However, a better alternative would be to allocate a qnode on the
 *  stack and when it gets blocked, the stack still exists. This will
 *  disable the interrupts in smaller scale and split the coarse
 *  coupling between lock module and tcb.
 *
 *
 *  @author Hongchao Deng (hongchad)
 */
#include <klock.h>
#include <queue.h>
#include <scheduler.h>
#include <cpu.h>
#include <tcb.h>
#include <asm.h>
#include <assert.h>
#include <stddef.h>

void kmutex_init(kmutex_t *kmu)
{
    assert(kmu != NULL);
    kmu->flag = 0;
    spin_init(& kmu->lock);
    q_init( & kmu->wait_queue);
}

void kmutex_lock(kmutex_t *kmu)
{
    assert(kmu != NULL);
    tcb_t *tcb;
    spin_lock( & kmu->lock);
    if(! kmu->flag ){
        kmu->flag = 1;
        spin_unlock( & kmu->lock);
    }
    else{
        tcb = get_cur_tcb();

        // enqueue to wait queue
        disable_interrupts();{
            // protect run queue (taken from)
            q_push( &kmu->wait_queue, & tcb->thr_sched );

            // once the thread got out of cpu, there is a chance that he
            // would never release the spinlock. We need to make sure it
            // does.
            spin_unlock( & kmu->lock);

            block_thr(tcb); // mark it
        } cpu_relax(); // will enable interrupts after waken up
    }
}

void kmutex_unlock(kmutex_t *kmu)
{
    assert(kmu != NULL);
    qnode_t *thr_sched;
    tcb_t *tcb;

    spin_lock( & kmu->lock);

    if( ! q_empty(&kmu->wait_queue) ){
        // dequeue next one to run queue

        // this is protected by the spinlock
        thr_sched = q_pop(&kmu->wait_queue);
        tcb = get_tcb_from_qnode(thr_sched);

        unblock_thr(tcb); // unmark it

        disable_interrupts();{
            // protect run queue (inserted into)
            scher_push_job( tcb );
        } enable_interrupts();

        spin_unlock( & kmu->lock);
    }
    else{
        kmu->flag = 0;
        spin_unlock( & kmu->lock);
    }

}
