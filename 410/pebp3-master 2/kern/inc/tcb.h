/** @file tcb.h
 *  @brief thread control block module header file
 *
 *  The thread control block has the following main fields:
 *   - tid
 *   - thread state
 *   - context switch states saved place (kernel stack)
 *   - one qnode to link to process thread queue
 *   - one qnode to link to scheduler run queue
 *   - memory remapping saved variable
 *   - a lock for make_runnable
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#ifndef _TCB_H
#define _TCB_H

#include <queue.h>
#include <pcb.h>
#include <stdint.h>
#include <klock.h>
#include <swexn.h>

typedef struct _tcb_t {
    int tid;

    uintptr_t save_esp; // for context switch
    int state; // flag recording thread state

    // registered as a member of pcb
    qnode_t thr_qnode;
    pcb_t *pcb;

    // usability:
    //   1. active, in run queue
    //   2. blocked, in wait queue
    qnode_t thr_sched;

    // memory mapping
    uintptr_t remap;

    kmutex_t makerun_mutex;

    // for swexn
    uintptr_t swexn_esp3;
    swexn_handler_t user_handler;
    void *args;

} tcb_t;


tcb_t* get_only_thread(pcb_t *pcb);
tcb_t* create_thread(pcb_t *pcb);
void init_thread(tcb_t *tcb, pcb_t *pcb);
tcb_t* get_tcb_from_qnode(qnode_t *thr_qnode);

tcb_t* get_cur_tcb();
qnode_t* get_cur_thr_sched();

int is_thr_blocked(tcb_t *tcb);
void block_thr(tcb_t *tcb);
void activate_thr(tcb_t *tcb);
void unblock_thr(tcb_t *tcb);
int is_thr_dead(tcb_t *tcb);
void die_thr(tcb_t *tcb);
int is_thr_active(tcb_t *tcb);
int is_thr_ioblocked(tcb_t *tcb);
void ioblock_thr(tcb_t *tcb);
int is_thr_desche(tcb_t *tcb);
void desche_thr(tcb_t *tcb);

void pcb_add_tcb(pcb_t*, tcb_t*);
int pcb_del_tcb(pcb_t*, tcb_t*);

int get_tid_fromtcb(void *tcb);
int fini_thread(tcb_t *tcb);

#endif // for #ifndef _TCB_H
