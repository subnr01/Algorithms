/** @file tcb.c
 *  @brief thread control block module implementation file
 *
 *  This is the thread module file. It provides all the interfaces
 *  relevant to thread or tcb.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <tcb.h>
#include <malloc.h>
#include <kernstk.h>
#include <id_counter.h>
#include <cr.h>
#include <klock.h>
#include <tid_table.h>
#define KERNLOG_L1_ON
#include <kernlog.h>

/******************************************************/
/******************** thread state ********************/

/*
 * ACTIVE:
 *     ANY
 * BLOCKED:
 *     ACTIVE
 * DEAD:
 *
 * IOBLOCKED:
 *     ACTIVE
 * DESCHE:
 *     ACTIVE
 */

#define THR_ACTIVE 0
#define THR_BLOCKED 1 // for mutex
#define THR_DEAD 2    // vanish
#define THR_IOBLOCKED 3 // readline
#define THR_DESCHE 4    // descheduled

int is_thr_blocked(tcb_t *tcb)
{ return tcb->state == THR_BLOCKED; }

void block_thr(tcb_t *tcb)
{ tcb->state = THR_BLOCKED; }

void unblock_thr(tcb_t *tcb)
{ tcb->state = THR_ACTIVE; }

void activate_thr(tcb_t *tcb)
{ tcb->state = THR_ACTIVE; }

int is_thr_dead(tcb_t *tcb)
{ return tcb->state == THR_DEAD; }

void die_thr(tcb_t *tcb)
{ tcb->state = THR_DEAD;}

int is_thr_active(tcb_t *tcb)
{ return tcb->state == THR_ACTIVE; }

int is_thr_ioblocked(tcb_t *tcb)
{ return tcb->state == THR_IOBLOCKED; }

void ioblock_thr(tcb_t *tcb)
{ tcb->state = THR_IOBLOCKED; }

int is_thr_desche(tcb_t *tcb)
{ return tcb->state == THR_DESCHE; }

void desche_thr(tcb_t *tcb)
{ tcb->state = THR_DESCHE; }

/**************** thread state ends *******************/
/******************************************************/



/** @brief create new thread
 *
 *  It will allocate kernel space, initialize thread resources, then
 *  insert it into the tid table.
 *
 *  @param pcb The pcb of the process of which a thread is created
 *  @return tcb of the new thread
 */
tcb_t*
create_thread(pcb_t *pcb)
{
    kernlog(5, "entering create_thread!");
    tcb_t *tcb;

    if( (tcb = (tcb_t *) malloc(KERNSTK_SIZE)) == NULL){
        return NULL;
    }

    init_thread( tcb, pcb );

    // Registering the new thread in tid table. It could fail in two
    // ways:
    //   1. not enough space. malloc failed.
    //   2. the tid already existed
    if(tcb->tid < 0 || tidtable_insert(tcb) < 0){
        free(tcb);
        return NULL;
    }

    kernlog(5, "leaving create_thread with success: tid(%d)!", tcb->tid);
    return tcb;
}

/** @brief initialize the tcb.
 *
 *  @param pcb
 *  @return Void.
 */
void
init_thread(tcb_t *tcb, pcb_t *pcb)
{

    tcb->tid = get_tid_counter();
    tcb->pcb = pcb;
    tcb->state = THR_ACTIVE;

    // qnode points back
    qnode_setitem( & tcb->thr_sched, tcb);
    qnode_setitem( & tcb->thr_qnode, tcb);

    kmutex_init( & tcb->makerun_mutex);
    tcb->swexn_esp3 = 0;
    tcb->user_handler = 0;
    tcb->args = 0;
    pcb_add_tcb(pcb, tcb);

}

/** @brief thread finish function
 *
 *  It will remove the thread entry in tid table and remove itself from
 *  process's thread queue. At last, it will judge whether it's the last
 *  thread to take action in vanish.
 *
 *  @param tcb
 *  @return boolean whether the thread calling the finish function is
 *  the last thread in its own process. This is used for vanish and also
 *  protected by a mutex in vanish.
 */
int
fini_thread(tcb_t *tcb)
{
    int thr_num;

    // remove entry in tid_table
    tidtable_remove(tcb->tid);
    // remove itself from pcb record
    thr_num = pcb_del_tcb(tcb->pcb, tcb);

    return thr_num == 0;
}

/** @brief Add thread to process's thread queue
 *
 *  @param pcb
 *  @param tcb
 *  @return Void.
 */
void pcb_add_tcb(pcb_t* pcb, tcb_t* tcb)
{
    kmutex_lock(& pcb->thr_mutex);{
        q_push(& pcb->thr_queue, & tcb->thr_qnode);
    } kmutex_unlock(& pcb->thr_mutex);
}

/** @brief remove thread to process's thread queue
 *
 *  @param pcb
 *  @param tcb
 *  @return number of threads left in the process
 */
int pcb_del_tcb(pcb_t* pcb, tcb_t* tcb)
{
    int thr_num;

    kmutex_lock(& pcb->thr_mutex);{
        q_remove( & pcb->thr_queue, & tcb->thr_qnode );
        thr_num = q_count( & pcb->thr_queue);
    } kmutex_unlock(& pcb->thr_mutex);

    return thr_num;
}

int get_tid_fromtcb(void *tcb)
{
    return ((tcb_t *)tcb)->tid;
}


/** @brief get tcb from qnode
 *
 *  The qnode's item is set to point to tcb at the initialization of
 *  tcb.
 *
 *  @param thr_qnode
 *  @return tcb pointer
 */
tcb_t*
get_tcb_from_qnode(qnode_t *thr_qnode)
{
    return (tcb_t *) qnode_getitem(thr_qnode);
}

tcb_t* get_cur_tcb()
{
    return (tcb_t *) esp0_to_tcb( (uintptr_t) get_esp0());
}

qnode_t*
get_cur_thr_sched()
{
    return  (& (get_cur_tcb()->thr_sched ) );
}


/***************************************/
/********** KERN STACK *****************/

/*
 *  These address translation things are described in 'kernstk.h' file.
 */
uintptr_t
esp0_to_tcb(uintptr_t esp0)
{
    return (esp0 - KERNSTK_SIZE );
}

uintptr_t
tcb_to_esp0(uintptr_t tcb)
{
    return (tcb + KERNSTK_SIZE );
}


