/** @file thread.c
 *  @brief contains misc. functions for thread library
 *  @author Alan Keith (arkeith) Hongchao Deng (hongchad) 
 *
 *  Contains basic functions used throughout the thread library:
 *
 *  thr_gettid()
 *  thr_yield()
 *  void Deschedule(){
 */
#include <thr_internals.h>
#include <simics.h>


/** @brief get the thread id of currently running thread
 *
 *  NOTE: at the moment this is just a wrapper as we are
 *  using a 1 to 1 thread model
 *  @return the thread id of the invoking thread
 */
int thr_getid( void ){
    return gettid();
}

/** @brief search the thread list and return thread data pointer
 *
 *  In our specific implementation. The node space in the thread list
 *  happens to be the first place of the thread data structure. So when
 *  we found the node pointer in the thread list, we also cast it the
 *  thread data structure pointer the return it.
 *
 *  @param tid id of thread whose data is being searched for
 *  @return pointer to the thread data;
 *          NULL if thread is not in the list.
 */
thd_data_t *
get_thd_dataptr(int tid)
{
    q_node *thread_node;

    TLIST_RLOCK();
    thread_node = q_find(tlist_head, tid);
    TLIST_UNRLOCK();

    return (thd_data_t *) thread_node;
}


/** @brief defer execution of invoking thread in favor of tid
 *
 *  When tid is -1 we yield to some unspecified thread
 *
 *  @param tid thread we are yielding to
 *  @return 0 on success, negative number on error
 *
 *  NOTE: at the moment this is just a wrapper to yield as we
 *  are using a 1 to 1 thread model
 */
int thr_yield( int tid ){
    return yield(tid);
}



/** @brief wrapper function for affirmative deschedule */
void Deschedule(){
    int reject = 0;
    deschedule(&reject);
}

