/** @file sem.c
 *  @brief semaphore library implementation
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */
#include <_sem.h>

/** @brief semaphore initialization function
 *
 *  @param sem semaphore data structure pointer
 *  @param count count number of semaphore
 *  @return 0 if success; less than 0 if failure.
 */
int
sem_init( sem_t *sem, int count)
{
    sem->internal_lock = & sem->lock_space;
    if( mutex_init(sem->internal_lock) < 0 ){
        return -1;
    }

    if(count <= 0){
        return -1;
    }
    sem->count = count;

    sem->wait_queue = & sem->queue_space;
    q_init( sem->wait_queue );

    return 0;
}

/** @brief semaphore destroying function
 *
 *  @param sem semaphore data structure pointer
 *  @return Void.
 */
void sem_destroy(sem_t *sem)
{
    mutex_destroy(sem->internal_lock);
    if( !q_empty(sem->wait_queue) ){
        THR_EXCEPTION();
    }
}

/** @brief semaphore wait (lock) function
 *
 *  @param sem semaphore data structure pointer
 *  @return Void.
 */
void
sem_wait(sem_t *sem)
{
    q_node thread_node;
    thread_node.slot = thr_getid();

    mutex_lock(sem->internal_lock);
    sleep(100);

    if(sem->count > 0){
        sem->count --;
        mutex_unlock(sem->internal_lock);
    }
    else { // count == 0;
        q_push( sem->wait_queue, & thread_node);
        mutex_unlock(sem->internal_lock);
        Deschedule();
    }

}

/** @brief semaphore signal (unlock) function
 *
 *  @param sem semaphore data structure pointer
 *  @return Void.
 */
void
sem_signal(sem_t *sem)
{
    q_node *node;
    mutex_lock(sem->internal_lock);
    if(sem->count == 0){
        if( (node = q_pop(sem->wait_queue)) == NULL ){
            sem->count ++;
        }
        else{
            run_next_thread(node->slot);
        }
        mutex_unlock(sem->internal_lock);
    }
    else{
        sem->count ++;
        mutex_unlock(sem->internal_lock);
    }
}
