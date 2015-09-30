/** @file wait.c
 *  @brief internal wait and vanish modules.
 *
 *  This is the internal wait and vanish functions.
 *
 *  In this module, the vanish is refered as process vanish, not thread
 *  vanish.
 *
 *  For the vanish, if a process die, he's going to detect if his parent
 *  is alive. If not, he's going to be reaped by 'init' process, as a
 *  result being added to 'init' zombie queue. If his parent's alive,
 *  then he's added himself to his parent's zombie queue.
 *
 *  For wait, a process is going to detect if anyone's in his zombie
 *  queue. if not, then wait. If yes, then reap it. Note that he need to
 *  detect if he has any children first.
 *
 *  There's an important decision I made for the process control. Each
 *  process has a child queue. When a child is created, he's been added
 *  to the child queue; when a child dies, he's been removed from it.
 *  This at first glance might look like shared resources between child
 *  processes. However, in my implementation only the parent has
 *  authorization to access the child queue. So only the parent can add,
 *  remove, or scan the child queue. The child's resources could only be
 *  freed by parent as well. Because there's only one parent, there's no
 *  race condition in this case.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bug No known bugs.
 */
#include <stddef.h>
#include <_wait.h>
#include <klock.h>
#include <queue.h>
#include <pcb.h>
#include <asm.h>
#include <tcb.h>
#include <cpu.h>
#include <malloc.h>
#include <scheduler.h>
#include <assert.h>
#include <vmm.h>
#include <tid_table.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

static pcb_t *__init_pcb;

/** @brief set 'init' process's pcb
 *
 *  @param pcb
 *  @return Void.
 */
void set_init_pcb(void *pcb)
{
    __init_pcb = pcb;
}

/** @brief wait type item init
 *
 *  @param wait_item
 *  @param pcb
 *  @return Void.
 */
void wait_item_init( wait_t *wait_item, void *pcb)
{
    kmutex_init( & wait_item->wait_mutex);
    kmutex_init( & wait_item->vanish_mutex);
    spin_init( & wait_item->thr_vanish_lock);
    spin_init( & wait_item->wait_lock );

    q_init( & wait_item->zombie_queue);
    q_init( & wait_item->wait_queue);

    qnode_setitem(& wait_item->zombie_qnode, pcb);
}

/** @brief set status
 *
 *  @param wait_item
 *  @param status
 *  @return Void.
 */
void wait_set_status(wait_t* wait_item, int status)
{
    wait_item->exit_status = status;
}

/** @brief Notify all the children that parent's died by setting their
 *  parent to NULL. There could be race in the vanishing process
 *  between children and parent. So we're using vanish mutex to protect
 *  this.
 *
 *  The vanish mutex is used to ensure atomicity of entire vanish process.
 *
 *  @param pcb The parent process pcb
 *  @return Void.
 */
static void
notify_children(pcb_t *pcb)
{
    pcb_t *child_pcb;
    qnode_t *iter;

    iter = q_start( & pcb->child_queue);

    while( iter != q_end( & pcb->child_queue) ) {

        child_pcb = qnode_getitem(iter);

        kmutex_lock( & child_pcb->wait_item.vanish_mutex);{
            kernlog(5, "  vanish: notify child (%d)", child_pcb->pid);
            child_pcb->parent = NULL;
        } kmutex_unlock(& child_pcb->wait_item.vanish_mutex);

        iter = q_next(iter);
    }
}

/** @brief handles process vanish.
 *
 *  When a process vanish, he will try to add himself to his parent's
 *  zombie queue. After that, if he detects his parent is blocked on
 *  waiting, he will also wake him up.
 *
 *  @return Void.
 */
void _vanish()
{
    int trylock;
    #ifdef KERNLOG_ON
        tcb_t *tcb = get_cur_tcb();
    #endif
    pcb_t *parent_pcb;
    pcb_t *self_pcb = get_cur_pcb();

    kernlog(5, "entering _vanish: tid(%d)", tcb->tid);

    assert(self_pcb != __init_pcb);

    // There is race condition if not doing this. both the child and
    // parent are going to vanish and the issue happens when child tries
    // to add himself to parent's zombie queue. In order to eliminate
    // that, we use a mutex and update the relevant information.
    notify_children(self_pcb);

    // This entire vanish process needs to be protected from race so
    // that either the parent couldn't die until child has vanished or
    // the parent died and notified the child to be reaped by 'init'
    kmutex_lock( & self_pcb->wait_item.vanish_mutex);{

        kernlog(5, "get self vanish mutex: tid(%d)", tcb->tid);

        parent_pcb = (self_pcb->parent != NULL)? self_pcb->parent:
                                                __init_pcb;

        // this must be done within the vanish mutex so that when the
        // parent also die, child's been added to the parent's zombie
        // queue already
        kmutex_lock( & parent_pcb->wait_item.wait_mutex);{

            kernlog(5, "vanish q_push, parent: %d, self: %d",
              parent_pcb->pid, self_pcb->pid);
            // test
            q_push( & parent_pcb->wait_item.zombie_queue,
              & self_pcb->wait_item.zombie_qnode);

            trylock = spin_trylock(& parent_pcb->wait_item.wait_lock);

        } kmutex_unlock( & parent_pcb->wait_item.wait_mutex);

        // protect the wait queue
        if(!trylock)
            spin_lock( & parent_pcb->wait_item.wait_lock);
        /* spin lock */{
            // wake up waiting parent thread
            if( ! q_empty( & parent_pcb->wait_item.wait_queue) ){
                qnode_t * thr_sched = q_pop(
                  & parent_pcb->wait_item.wait_queue);
                tcb_t *wait_tcb = get_tcb_from_qnode(thr_sched);

                activate_thr(wait_tcb);

                kernlog(5, "  vanish: wake up wait (%d)", wait_tcb->tid);
                disable_interrupts(); {
                    scher_push_job(wait_tcb);
                } enable_interrupts();
            }
        } spin_unlock( & parent_pcb->wait_item.wait_lock);

    } kmutex_unlock( & self_pcb->wait_item.vanish_mutex);


    kernlog(5, "  vanish: finish (%d)", tcb->tid);
}

/** @brief Reap the process's resources
 *
 *  It needs to wait for the process to vanish completely.
 *
 *  @param pcb Process to be reaped.
 *  @return Void.
 */
static void
reap_pcb(pcb_t *pcb)
{
    thr_vanish_lock(& pcb->wait_item);{
        kernlog(5, "reap children (%d)", pcb->pid);
        release_vm(pcb->cr3);
        free(pcb);
    }
    /*
     * Doesn't need to release the lock here.
     * All the resources will be recycled.
     */
}


/** @brief delegate to reap the children. This is for 'init' only.
 *
 *  @param pcb Process whose children to be reaped.
 *  @return Void.
 */
static void
delegate_reap(pcb_t *pcb)
{
    pcb_t *child_pcb;
    qnode_t *iter = q_start( & pcb->wait_item.zombie_queue);

    while( iter != q_end( & pcb->wait_item.zombie_queue) ) {

        child_pcb = qnode_getitem(iter);

        iter = q_next(iter);

        delegate_reap(child_pcb);
        reap_pcb(child_pcb);
    }
}

/** @brief reap the child process or wait if none has died.
 *
 *  @param status_ptr
 *  @return pid of the reaped process. -1 if it doesn't have any child
 *  process.
 */
int _wait(int *status_ptr)
{
    int res;
    int trylock;
    pcb_t *child_pcb;

    tcb_t *tcb = get_cur_tcb();
    pcb_t *pcb = tcb->pcb;
    wait_t *wait_item = & pcb->wait_item;

    if( q_empty( & pcb->child_queue) &&
      q_empty( & pcb->wait_item.zombie_queue)){
        if(q_empty( & pcb->child_queue)){
            kernlog(5, "child queue empty (%d)", tcb->tid);
        }
        if(q_empty( & pcb->wait_item.zombie_queue)){
            kernlog(5, "zombie queue empty (%d)", tcb->tid);
        }
        return -1;
    }

    kernlog(5, "entering _wait: tid(%d)", tcb->tid);

    // 1. take an item from the zombie queue
    //    This step is protected by ait_mutex; the child cannot add
    //    himself to the zombie queue unless he acquired the mutex.
    // 2. if taking an itme from zombie queue, reap it.
    //    if self is init process, it's an obligation to reap all its
    //    zombie children as well.
    // 3. if not taking any item, block itself to the wait queue.

    do{
        // the wait mutex could be used to just protect the zombie queue.
        // which should make wait a little faster theoretically.
        kmutex_lock( & wait_item->wait_mutex);{

            kernlog(5, "get self wait mutex: tid(%d)", tcb->tid);

            // taking item from zombie queue
            child_pcb = q_empty( & wait_item->zombie_queue)? NULL:
                qnode_getitem( q_pop( & wait_item->zombie_queue) );

            if(child_pcb != NULL){ // has zombie to reap
                // retrieve status and free the resource of the child
                if(status_ptr != NULL)
                    *status_ptr = child_pcb->wait_item.exit_status;

                // the process could die without reaping its child
                // processes. Then the init process should be delegated
                // to reap them.
                delegate_reap(child_pcb);


                if(child_pcb->parent == pcb){
                    q_remove( & pcb->child_queue, & child_pcb->child_qnode);
                }

                res = child_pcb->pid;

                reap_pcb(child_pcb);
            }
            else{
            /*
             *  If the waiting process doesn't reap any child, he needs
             *  to wait. In order to prevent interleaving operations of
             *  child waking up the parent and parent blocking himself
             *  to sleep, the operations of each must be done
             *  atomically. Blocking and waking up is something related
             *  to the scheduler run queue, and the run queue operations
             *  must be done within disable_interrupts. The mutex
             *  couldn't be released within it. So this is done using a
             *  spin wait lock.
             */
                trylock = spin_trylock( & wait_item->wait_lock);
            }

        } kmutex_unlock( & wait_item->wait_mutex);

        if( child_pcb == NULL){
            // protect the wait queue
            // I use this lock to protect wait queue because the kmutex
            // can't be promised to release when disabling interrupts.
            if( !trylock)
                spin_lock( & wait_item->wait_lock);
            /* spin lock */{
                kernlog(5, "wait!!!");

                disable_interrupts();{
                    spin_unlock( & wait_item->wait_lock);
                    q_push( & wait_item->wait_queue, & tcb->thr_sched);
                    block_thr(tcb);
                } cpu_relax();
            }
        }

    } while( child_pcb == NULL);

    kernlog(5, "wait: finish (%d), return: %d", tcb->tid, res);

    return res;
}

/** @brief this is thread vanish lock.
 *
 *  @param wait_item
 *  @return Void.
 */
void thr_vanish_lock(wait_t * wait_item) {
    spin_lock( & wait_item->thr_vanish_lock);
}

/** @brief this is thread vanish unlock.
 *
 *  @param wait_item
 *  @return Void.
 */
void thr_vanish_unlock(wait_t *wait_item) {
    spin_unlock( & wait_item->thr_vanish_lock);
}
