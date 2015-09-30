/** @file rwlock.c
 *  @brief rwlock library implementation
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug the downgrade function doesn't have writer mode check yet
 */
#include <_rwlock.h>

/** @brief rwlock initialization function
 *
 *  @param rwlock rwlock pointer
 *  @return 0 if success; less than 0 if failure.
 */
int
rwlock_init(rwlock_t *rwlock)
{
    rwlock->internal_lock = & rwlock->internal_lock_space;
    if( mutex_init(rwlock->internal_lock) < 0 ) {
        return -1;
    }

    rwlock->downgrade_cond = & rwlock->downgrade_cond_space;
    if (cond_init(rwlock->downgrade_cond) < 0 ){
        return -1;
    }

    rwlock->reader_cond = & rwlock->reader_cond_space;
    if (cond_init(rwlock->reader_cond) < 0 ){
        return -1;
    }

    rwlock->writer_cond = & rwlock->writer_cond_space;
    if (cond_init(rwlock->writer_cond) < 0 ){
        return -1;
    }

    rwlock->readers =0;
    rwlock->writers =0;
    rwlock->waiting_writers =0;
    rwlock->downgrading = 0;

    return 0;
}

/** @brief rwlock destroying function
 *
 *  @param rwlock rwlock pointer
 *  @return Void.
 */
void
rwlock_destroy(rwlock_t *rwlock)
{
    mutex_destroy(rwlock->internal_lock);
    cond_destroy(rwlock->downgrade_cond);
    cond_destroy(rwlock->reader_cond);
    cond_destroy(rwlock->writer_cond);
}

/** @brief rwlock lock function
 *
 *  @param rwlock rwlock pointer
 *  @param type the type (reader or writer) you wanna lock on
 *  @return Void.
 */
void rwlock_lock(rwlock_t *rwlock, int type)
{
    mutex_lock(rwlock->internal_lock);
    if(type == RWLOCK_READ){
        /* reader lock */
        if(rwlock->writers > 0 || rwlock->waiting_writers > 0 ){
            cond_wait(rwlock->reader_cond, rwlock->internal_lock);
        }
        rwlock->readers ++; // reader to go
        rwlock->current_mode = RWLOCK_READ;
    }
    else if(type == RWLOCK_WRITE){
        /* writer lock */
        if(rwlock->downgrading){
            cond_wait(rwlock->downgrade_cond, rwlock->internal_lock);
        }
        rwlock->waiting_writers ++; // waiting writers, block coming readers

        if(rwlock->writers > 0 || rwlock->readers > 0 ){
            cond_wait(rwlock->writer_cond, rwlock->internal_lock);
        }
        rwlock->waiting_writers --;
        rwlock->writers++; // writer to go
        rwlock->current_mode = RWLOCK_WRITE;
    }
    mutex_unlock(rwlock->internal_lock);
}

/** @brief rwlock unlock function
 *
 *  @param rwlock rwlock pointer
 *  @return Void.
 */
void rwlock_unlock(rwlock_t *rwlock)
{
    mutex_lock(rwlock->internal_lock);
    if(rwlock->current_mode == RWLOCK_READ){
        /* reader unlock */
        rwlock->readers --;
        if(rwlock->readers == 0 && rwlock->waiting_writers > 0)
            cond_signal(rwlock->writer_cond); // let writer to run
    }
    else if(rwlock->current_mode == RWLOCK_WRITE){
        /* writer unlock */
        rwlock->writers --;
        if(rwlock->waiting_writers > 0) // get another writer to run
            cond_signal(rwlock->writer_cond);
        else // get all readers to run
            cond_broadcast(rwlock->reader_cond);
    }
    mutex_unlock(rwlock->internal_lock);
}

/** @brief rwlock downgrade function
 *
 *  This function will downgrade the rwlock from writer mode to reader
 *  mode, and release all those readers at this moment.
 *
 *  @param rwlock rwlock pointer
 *  @return Void.
 */
void rwlock_downgrade( rwlock_t *rwlock )
{
    int saved_wait_writers;

    mutex_lock(rwlock->internal_lock);
    /* change its lock to reader lock */
    rwlock->current_mode = RWLOCK_READ;
    rwlock->readers ++; // metamorphiced to a reader
    rwlock->writers --; // writers = 0

    /* saved the waiting_writers, set it to zero to let all readers go,
     * and then set it back
     */
    saved_wait_writers = rwlock->waiting_writers;
    rwlock->waiting_writers = 0;

    rwlock->downgrading = 1;
    mutex_unlock(rwlock->internal_lock);

    /* only the reader can get into lock at this moment; */
    cond_broadcast(rwlock->reader_cond); // wake up every reader

    /* set the downgrading flag back to let writers come */
    mutex_lock(rwlock->internal_lock);
    rwlock->downgrading = 0;
    mutex_unlock(rwlock->internal_lock);

    /* wake up all those writers on downgrade_cond */
    cond_broadcast(rwlock->downgrade_cond);
}
