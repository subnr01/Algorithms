/** @file pcb.c
 *  @brief process module implementation file
 *
 *  This is the process module file. It provides all the interfaces
 *  relevant to process or pcb.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <pcb.h>
#include <tcb.h>
#include <queue.h>
#include <stdint.h>
#include <stddef.h>
#include <malloc.h>
#include <kernstk.h>
#include <cr.h>
#include <stdio.h>
#include <_wait.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


/** @brief create the process
 *
 *  We're allocating resources for the new process and initialize it.
 *  When creating a new process, we are also creating a new thread.
 *
 *  @param parent pcb of parent process
 *  @param cr3
 *  @return pcb pointer to the newly created process
 */
pcb_t*
create_process(pcb_t *parent, int cr3)
{
    pcb_t *pcb;
    tcb_t *tcb;

    kernlog(5, "pcb: malloc");
    if( (pcb = (pcb_t *) malloc(sizeof(pcb_t))) == NULL){
        return NULL;
    }

    // init pcb
    pcb->cr3 = cr3;
    pcb->parent = parent;

    q_init(& pcb->child_queue);
    q_init(& pcb->thr_queue); // thread queue
    qnode_setitem(& pcb->child_qnode, pcb);


    kmutex_init( & pcb->thr_mutex);
    kmutex_init( & pcb->pf_mutex);
    kmutex_init( & pcb->page_mutex);

    wait_item_init( & pcb->wait_item, pcb);

    kernlog(5, "pcb: create thread");
    if( (tcb = create_thread(pcb)) == NULL ){
        free(pcb);
        return NULL;
    }

    // pid could be initialized only after we have first tid
    pcb->pid = tcb->tid ;


    kernlog(5, "pcb: return: %08x", (unsigned)pcb);
    return pcb;
}

/** @brief get the only thread (first thread in thread queue)
 *
 *  This is mainly used for creating the process and adding its thread
 *  block into run queue.
 *
 *  @param pcb
 *  @return pcb pointer to the newly created process
 */
tcb_t*
get_only_thread(pcb_t *pcb)
{
    return (tcb_t *) qnode_getitem(
      q_index( & pcb->thr_queue, 0) );
}

/** @brief get current pcb
 *
 *  @return pcb pointer to current pcb
 */
pcb_t *
get_cur_pcb()
{
    return get_cur_tcb()->pcb ;
}

/** @brief get number of threads in process
 *
 *  @param pcb The pcb of the process to be checked
 *  @return Number of the threads.
 */
int
get_thr_num(pcb_t *pcb)
{
    int res;
    kmutex_lock( & pcb->thr_mutex);{
        res = q_count(&pcb->thr_queue);
    } kmutex_unlock( & pcb->thr_mutex);
    return res;
}

/*
 * The following things is used to prevent interleaving calls to
 * new_pages and remove_pages.
 */
void page_lock() {
    pcb_t *pcb = get_cur_pcb();
    kmutex_lock( & pcb->page_mutex);
}

void page_unlock() {
    pcb_t *pcb = get_cur_pcb();
    kmutex_unlock( & pcb->page_mutex);
}
