/** @file cond.c
 *  @brief contains functions and code for condition variable implementation
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */
#include <_cond.h>

/** @brief conditional variable initialization function
 *
 *  @param cv conditional variable's pointer
 *  @return 0 if success; less than 0 if failure.
 */
int cond_init( cond_t *cv ){
    if (mutex_init(&cv->internal_lock) < 0){
        return -1;
    }
    cv->wait_queue = &cv->queue;
    q_init(cv->wait_queue);
    return 0;
}

/** @brief conditional variable destroying function
 *
 *  @param cv conditional variable's pointer
 *  @return Void.
 */
void cond_destroy( cond_t *cv ){
    mutex_destroy(&cv->internal_lock);
    if( ! q_empty(cv->wait_queue) ){
        THR_EXCEPTION();
    }
}


/** @brief release *mp, wait on cond variable, and then re-acquire *mp
 *
 *  thread will wait on condition, releasing mutex *mp, and block until
 *  it is awoken. When it is woken up, the *mp is re-acquired on behalf
 *  of the thread
 *
 *  @param *cv the condition variable to wait on
 *  @param *mp the mutex lock we to acquire when signaled
 *
 *  NOTE: we prefer that *mp is locked already, but we don't require.
 *  If the thread didn't acquire the mutex, it could still wait on the
 *  conditional variable.
 *  @return Void.
 */
void cond_wait( cond_t *cv, mutex_t *mp ){
    q_node thread_node;
    thread_node.slot = thr_getid();

    mutex_lock(&cv->internal_lock);

    /* put thread into queue */
    q_push(cv->wait_queue, & thread_node );

    if ( VERIFY_LOCK(mp) ){// ensure the thread has lock before unlocking
        mutex_unlock(mp);
    }

    mutex_unlock(&cv->internal_lock);

    //block, waiting to be woken up
    Deschedule();

    //re-acquire mutex mp
    mutex_lock(mp);
}

/** @brief wake up a thread waiting on *cv, if one exists
 *  @param *cv the cond variable we are signaling
 *  @return Void.
 */
void cond_signal( cond_t *cv ){
    q_node * node;
    int tid;

    mutex_lock(&cv->internal_lock);
    node = q_pop(cv->wait_queue); //get first thread in queue to awake
    mutex_unlock(&cv->internal_lock);

    if (node != NULL){
        tid = node->slot;
        run_next_thread(tid);
    }
}

/** @brief awaken all threads waitin on *cv
 *  @param *cv the cond variable we are broadcasting
 *  @return Void.
 */
void cond_broadcast( cond_t *cv ){
    q_node * node;
    int tid;

    mutex_lock(&cv->internal_lock);

    while( (node = q_pop(cv->wait_queue)) != NULL ){
        tid = node->slot;
        run_next_thread(tid);
    }
    /* we wait to unlock here so that people who cond_wait on *cv during our
     * broadcast call do not get woken up */
    mutex_unlock(&cv->internal_lock);
}
