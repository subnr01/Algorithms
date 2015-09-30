/** @file mutex.c
 *  @brief Implementation of the mutex library.
 *
 *  Our mutex library has an internal mutex. the internal mutex is based
 *  on the atomic swapping operation and the nature of determining
 *  sequence by doing those swaps:
 *  1 (1), 2 (2), 3 (3), mutex (0)
 *
 *  everyone will try to swap the 0 in mutex, but the result will
 *  probably be like:
 *  1 (0), 2 (1), 3 (2), mutex (3)
 *
 *  However, there is a sequence determined by this way: 1 -> 3 -> 2.
 *
 *  Based on the observation and result of swapping, we implement our
 *  mutex by determining the sequence and then descheduling those who can't
 *  run, waking up the one that runs next, etc.
 *
 *  This mutex achieves mutual exclusion and bounded waiting (a thread
 *  will wait at most n-1 times where n is the number of threads at any
 *  time).
 *
 *  REASONING: why we did it that way?
 *  1. it scales. We don't have to know the number of threads trying to
 *  acquire the lock ahead of time. The slot is in the thread's private
 *  area (in our implementation it's on the thread stack).
 *  2. use of deschedule and make_runnable. This is very specific to the
 *  kernel interface given to us. We can deschedule the threads who
 *  didn't get the lock and wake them up later by calling the kernel
 *  interface.
 *
 *  This implementation doesn't support double mutex, so we still need a
 *  queue to push those waiting threads in the queue. The way to protect
 *  the queue from race condition is by our internal mutex.
 *
 *  NOTES: thr_init() is required to be called before calling any mutex library
 *  functions.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */
#include <_mutex.h>
#include <simics.h>

/** @brief initialize mutex referenced by mp
 *
 *  For initialization we simply need to zero out the memory
 *
 *  @param *mp the mutex we initialize
 *  @return 0 on success, a number less than 0 on error
 *
 */
int mutex_init(mutex_t *mp){
    /* TODO: duplicate init check */
    /* TODO: Invalid address of mp */


    if(mp == NULL){
        return THR_ERROR;
    }

    mp->slot = SLOT_WIN;
    mp->duel = DUEL_WIN;
    mp->last_final_thread = THR_NULL;
    mp->next_first_thread = THR_NULL;

    mp->head = &mp->head_space;

    q_init(mp->head);

    return THR_SUCCESS;
}

/** @brief deactivates the mutex pointed to by *mp
 *
 *  We are destroying the lock by moving a MUTEX_DESTROYED
 *  into the mutex slot. When other threads try to acquire
 *  this lock, they will obtain the MUTEX_DESTROYED value
 *  and throw an exception.
 *
 * @param *mp the mutex we are destroying
 */
void mutex_destroy(mutex_t *mp){
    /* TODO: duplicate destroy check */

    int mutex_slot;

    /* Destroying something that doesn't exist is not deadly to our
     * library. We could just return.
     */
    if(mp == NULL){
        return;
    }
    /* make the mutex dead now */
    mutex_slot = atomic_swap( (uintptr_t) &mp->slot, MUTEX_DESTROYED);

    /* if the slot has been occupied by someone or
     * if the there is still thread in the q.
     * Note:
     *      no one can acquire the queue_mutex at this moment. so it's
     *      safe to check the queue without lock. There is still race
     *      condition here caused by user misbehavior. It will cause the
     *      all threads to die.
     */
    if(mutex_slot != SLOT_WIN || !q_norunthread(mp->head) ){
        THR_EXCEPTION();
    }
}

/** @brief Try to lock on mutex
 *
 *  The program will first try get into a critical section which is
 *  protected by a internal bounded-waiting mutex.
 *
 *  The reason we can't use that mutex implementation as mutex_lock is
 *  because that one needs a single unique place on each thread. And
 *  this could be a problem when trying to do double mutex.
 *
 *  So a queue is used here to record the threads that have been locked
 *  on the mutex. The logic on queue is:
 *    1. if the queue has no thread running on it, set has thread
 *    running on it and get the lock.
 *    2. if the queue has thread running on it, push the thread itself
 *    to the queue.
 *
 *  @param *mp the mutex that's being tried to lock
 */
void
mutex_lock(mutex_t *mp)
{
    int run;
    int tid = thr_getid();

    q_node thread_node;
    thread_node.slot = tid;

    if(mp == NULL){
        THR_EXCEPTION();
    }

    /* duplicate lock */
    if( VERIFY_LOCK(mp) ){
        return; //I already have the lock
    }

    mutex_queue_lock(mp, &thread_node);
    CRITICAL_SECTION {
        if( q_norunthread(mp->head)){
            run = 1;
            q_set_runthread(mp->head, tid);
        }
        else{
            run = 0;
            q_push(mp->head, &thread_node);
        }
    }
    mutex_queue_unlock(mp, &thread_node);

    if(!run){
        Deschedule();
        q_set_runthread(mp->head, tid);
    }
}

/** @brief Try to unlock on mutex
 *
 *  The program will first try get into a critical section which is
 *  protected by a internal bounded-waiting mutex.
 *
 *  The reason we can't use that mutex implementation as mutex_lock is
 *  described above in mutex_lock description.
 *
 *  The logic about queue in unlock is:
 *    1. if the queue has thread items pushed on it (queue not empty),
 *    then pop the next one to run.
 *    2. if the queue has no items, unset the thread running to mark
 *    that other thread that tries next could set and run.
 *
 *  @param *mp the mutex that's being tried to unlock
 */
void
mutex_unlock(mutex_t *mp)
{
    q_node *node = NULL;
    int next_tid;
    int tid = thr_getid();

    q_node thread_node;
    thread_node.slot = tid;

    if(mp == NULL){
        THR_EXCEPTION();
    }

    /* This thread didn't lock mutex before */
    if(! VERIFY_LOCK(mp)) {
        return;
    }

    mutex_queue_lock(mp, &thread_node);
    CRITICAL_SECTION{
        if( (node = q_pop(mp->head) ) == NULL ){
            q_unset_runthread(mp->head);
        }
    }
    mutex_queue_unlock(mp, &thread_node);

    if(node != NULL){
        next_tid = node->slot;
        run_next_thread( next_tid );
    }
}

/** @brief function for activating the next thread
 *
 *  NOTE: This occurs in the rare case that there is competition
 *  for the lock, thus it is okay if it is slower
 *
 *  First we need to make sure that thread_id is descheduled
 *
 *  We can spin yield until next id  deschedules itself, which
 *  we can detected when the return value is -1. The other cases where
 *  thread < 0 should not occur (thread not existing or waiting on
 *  an external event in a system call).
 *
 *  Thus when we get -1, we can then attempt to reschedule
 *
 *  We will continue to call make_runnable until we succeed
 *
 *  We expect to fail make_runnable when it is called on a running thread,
 *  but we don't have access to the error codes so this becomes an assumption.
 *
 *  @param tid tid of next thread to acquire the lock.
 *
 */
void run_next_thread(tid) {
    while (make_runnable((tid)) != 0){
        yield_until_desche(tid);
    }
}

/** @brief function for yielding the thread until it's descheduled
 *  @param tid tid of thread that will be descheduled somehow.  *
 *  ASSUMPTION: tid is a thread which will be descheduled. If it's still
 *  runnable now, we keep yielding and it will be descheduled in this
 *  way.
 */
void yield_until_desche(tid)
{
    /* NOTE:
     * It will be better if we have error code to differentiate the
     * error we expect. That is, error in yield() that comes from
     * descheduled thread could be detected.
     *
     */
    while (thr_yield((tid)) == 0)
        continue;
}


/********* internal bounded waiting lock mechanism ***********/

/** @brief internal lock functions
 *
 *  This function will try to do atomic swap with the mutex's slot and
 *  determine the running sequence using the number it gets.
 *
 *  @param mp the mutex pointer
 *  @param node the thread's node which has the slot of thread's id.
 *  @return Void.
 */
void
mutex_queue_lock(mutex_t *mp, q_node *node)
{
    int thread_slot, tid, duel;

    thread_slot = tid = thr_getid();
    thread_slot = atomic_swap( (uintptr_t) &mp->slot, thread_slot);

    /* this will make the queue to determine what to run next */
    set_slot(node, thread_slot);

    /* lock doesn't exist */
    if (thread_slot == MUTEX_DESTROYED) {
        THR_EXCEPTION();
    }

    if(thread_slot == SLOT_WIN){
        /*
         * entering this means this thread gets the winning slot. it
         * should be the first thread to run in this group. We need to
         * check if there is any other group running now before that.
         */
        duel = DUEL_TRY;
        mp->player_lock = tid;

        /* we are doing while loop here because those who unlock could
         * continue
         */
        while( (duel = atomic_swap( (uintptr_t) &mp->duel, duel))
          != DUEL_WIN){
            /*
             * This happens only in case that current group's last thread
             * won the duel and was trying to finish it up.
             */
            thr_yield(mp->player_unlock);
        }

        CRITICAL_SECTION{
            if( mp->last_final_thread != THR_NULL ){
                /* we need to wait */

                mp->next_first_thread = tid;
                Deschedule();
                /* waits until someone else wakes this thread up. */
            }
            /*
             * ready to go
             * No one else will get the win slot at this moment.
             * Thus we know we are the first thread in this group and
             * set things for it.
             */
            mp->next_first_thread = THR_NULL;
            mp->last_final_thread = tid;
            /* duel = DUEL_WIN; swap it back */
            atomic_swap((uintptr_t) &mp->duel, duel);
        }

    }
    else{
        /*
         * this thread will be in a queue waiting for the previous run
         * thread waking it up.
         */
        Deschedule();
    }

}

/** @brief internal unlock function
 *
 *  This function will try to signal the next thread in the sequence
 *  determined in lock function.
 *
 *  @param mp the mutex pointer
 *  @param node the thread's node which should be put thread id back
 *  @return Void.
 */
void
mutex_queue_unlock(mutex_t *mp, q_node *node)
{
    int thread_slot, tid, duel;

    tid = thr_getid();

    thread_slot = get_slot(node);

    /*  It didn't call mutex_queue_lock() */
    if( thread_slot == tid ){
        THR_EXCEPTION();
    }

    /* release the internal lock, set the id back */
    set_slot(node, tid);

    if(thread_slot == SLOT_WIN){
        /* the first thread of lock list need to swap win slot to:
         *   1. let other threads wait and form the next group
         *   2. get the next thread to run
         */
        thread_slot = atomic_swap( (uintptr_t) &mp->slot, thread_slot);
    }

    if(thread_slot != mp->last_final_thread){
        /* This thread is not the last thread in this group .
         * Continue to run the next one in lock list
         */
        run_next_thread(thread_slot);
        return; /* just wanna make sure */
    }

    /* last thread in this round
     * This is the else branch of previous if.
     * Just wanna be clear what we are expecting.
     */
    if(thread_slot == mp->last_final_thread){
        duel = DUEL_TRY;
        mp->player_unlock = tid;
        duel = atomic_swap( (uintptr_t) &mp->duel, duel);

        if(duel != DUEL_WIN){
            /*
             * first thread in next round get the lock.
             * he will deschedule since we still have the last_final_thread value
             * set. Just wait.
             */
            yield_until_desche(mp->player_lock);
        }

        /*
         * The critical section contains two global values in mutex
         * passed into this function.
         *
         * There's a specific case entering this critical section. That
         * is, the first thread in next round get descheduled and yield
         * the control to us.
         */
        CRITICAL_SECTION{
            if(mp->next_first_thread == THR_NULL){
                /* there is no thread running next. Just set value and
                 * continue
                 */
                mp->last_final_thread = THR_NULL;
                atomic_swap( (uintptr_t) &mp->duel, duel);
            }
            else{
                /* there is a thread that needs to be run. run it
                 * In fact here we don't need to keep yielding it.
                 * A stronger assumption could be made: entering this
                 * place indicates the next thread was already descheduled.
                 */
                run_next_thread(mp->next_first_thread);
                /*
                 * Making sure this thread will jump out of critical
                 * section immediately after waking up the next thread
                 */
            }
        }

    }
}

void set_slot(q_node *node, int slot)
{
    node->slot = slot;
}

int get_slot(q_node *node)
{
    return node->slot;
}
