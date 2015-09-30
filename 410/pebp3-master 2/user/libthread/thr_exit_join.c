/** @file the_exit_join.c
 *  @brief contains functions for joining and exiting threads
 *
 *  One thing of note is are use of deschedule and yield
 *  to synchronize joiners and exiters
 *
 *  @author Alan Keith (arkeith) Hongchao Deng (hongchad)
 */
#include <thr_internals.h>

q_node zombie_head_space; //!<space for the head of the zombie queue
q_node *zombie_head; //!<head of the zombie queue

/** @brief cleanup after a thread
 *
 *  There are two cases: the thread needed to be joined is dead or
 *  still being running.
 *    1. if dead, it is in the zombie queue. reap it
 *    2. if not in the zombie queue, meaning it's still alive, tell him
 *    we want to join him and wait for him.
 *
 *  Only one thread can join any given thread. otherwise we will return
 *  immediately.
 * 
 *  If the thread does not exist we return an error
 *
 *  Once we are sure the joined thread has vanished we de-allocate its memory,
 *  and remove the pages it had used for its stack. We update _search_start 
 *  which is used for thread creation if the free'd stack location is 
 *  higher than current _search_start
 *
 *
 *  @param tid thread id we are cleaning up
 *  @param **statusp location to write return value of exit_status
 *
 *  @return 0 on success, number less than 0 on error
 */
int thr_join( int tid, void **statusp ){

    int zombie_tid;
    q_node *node;
    thd_data_t *zombie_data;

    mutex_lock(&cleanup_lock);
    CRITICAL_SECTION {
        /* we search the zombie queue, if the thread isn't in the zombie queue
         * we register ourselves as the joining thread */
        if( (node = q_find(zombie_head, tid)) == NULL ){
            if( set_join_tid(tid) < 0){ //tid does not exist or already joined
                mutex_unlock(&cleanup_lock);
                return THR_ERROR;
            }
        }
    }
    
    if(node == NULL){
        mutex_unlock(&cleanup_lock);
        Deschedule();

        mutex_lock(&cleanup_lock);
        node = q_find(zombie_head, tid); // will definitely find
        /* wake up */
    }


    if(node == NULL){
        mutex_unlock(&cleanup_lock);
        return THR_ERROR;
    }
    zombie_tid = node->slot;
    zombie_data = (thd_data_t *) node;
    
    if (statusp != NULL)
        *statusp = zombie_data->status;

    mutex_unlock(&cleanup_lock);

    dealloc_thread(zombie_tid);



    /* only the main thread can set single thread environment */
    TLIST_RLOCK();
    if( q_count(tlist_head) == 1 ){ // move back to single thread environment
        SET_SINGLE_THREAD_ENV();
        _search_start = GET_THRSTACK_SEARCH_BASE(); //optimization for thr
        
    }
    TLIST_UNRLOCK();

    return THR_SUCCESS;
}

/** @brief registers running thread as the joiner for target tid
 *  @param tid the target thread
 *  @return 0 on success, a negative number on error
 *
 *  We consider an error to occur if the thread doesn't exist or there is already
 *  a joiner for the given thread
 */
int set_join_tid(int tid) {
    int val = THR_ERROR;

    TLIST_WLOCK();
    thd_data_t *dptr =  (thd_data_t *)
        q_find(tlist_head, tid);//search for thread id
    
    if (dptr != NULL && dptr->join_tid == THR_NULL){
        val = THR_SUCCESS;
        dptr->join_tid = thr_getid();
    }

    TLIST_UNWLOCK();
    return val;
}

/** @brief de-allocates space reserved for thread-tid
 *  @param tid the thread id we are deallocating
 *
 *  NOTE: we assume that the thread is in the zombie queue
 *  NOTE: cleanup mutex protects zombie queue
 */
void dealloc_thread(int tid) {
    q_node *thread_node;
    thd_data_t *thread_data;

    /* remove from zombie queue */
    mutex_lock(&cleanup_lock);
    thread_node = q_remove(zombie_head, tid);
    mutex_unlock(&cleanup_lock);

    thread_data = (thd_data_t *) thread_node;

    while (thr_yield(tid) == 0) //wait until thread calls vanish
        continue;
    /* free the space */
    
    mutex_lock(&cleanup_lock); //making space available
    if (thread_data->base > _search_start)
        _search_start = thread_data->base;

    remove_pages( (void *) (thread_data->base) );
    mutex_unlock(&cleanup_lock);

    free(thread_node);
}

/** @brief exit the thread with exit status status
 *
 *  There are two cases: we are exiting before join or joining before exit
 *    1. If we have someone joining on us we wake him up
 *    2. If we don't, we add ourselves to the zombie queue
 *
 *  @param *status return value to pass to thread joining on me
 */
void thr_exit( void *status ){
    int tid = gettid();
    //lprintf("thr_exit start for thread %d", tid);
    int join_tid;
    q_node *thread_node;

    mutex_lock(&cleanup_lock);
    CRITICAL_SECTION {
        //remove ourselves from thread list
        TLIST_WLOCK();
        thread_node = q_remove(tlist_head, tid);
        TLIST_UNWLOCK();
        //put out tid in slot
        thread_node-> slot = thr_getid();
        //add to zombie queue
        q_push(zombie_head, thread_node);
        
        //record the exit status
        ((thd_data_t *) thread_node)->status = status;
        
        //get the tid of the person waiting on us
        join_tid = ((thd_data_t *) thread_node)->join_tid;

    }
    mutex_unlock(&cleanup_lock);

    if(join_tid != THR_NULL){
        /* yield  guy has been descheduled */
        while (make_runnable(join_tid) != 0){
            while (thr_yield(join_tid) == 0)
                continue; //wait until he deschedules
        }
    }

    /* even if thread stops executing, the stack space is also there. so
     * thread_node should also exist before being destroyed in thr_join.
     */
    vanish();
}
