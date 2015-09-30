/** @file fork.c
 *  @brief fork handler and installer implementation file
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <stdint.h>
#include <stddef.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "fork.h"
#include <pcb.h>
#include <tcb.h>
#include <kernstk.h>
#include <conswi.h>
#include <vmm.h>
#include <assert.h>
#include <scheduler.h>
#include <res_manage.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief fork handler
 *
 *  We're checking the thread number first to reject case that a process
 *  has more than one thread. Once satisfied we are going to create a
 *  new process and allocate resources for it. Once everything's done,
 *  we add the only thread of it to the run queue.
 *
 *  @return pid on success. negative number on failure.
 */
int
fork_handler()
{
    uintptr_t esp0, cr3;
    pcb_t *pcb;
    tcb_t *tcb;
    pcb_t *parent_pcb;
    tcb_t *parent_tcb = get_cur_tcb();
    int res;

    parent_pcb = get_cur_pcb();

    // process doing fork with multiple threads would fail
    if( get_thr_num(parent_pcb) > 1){
        return -1;
    }

    kernlog(5, "before clone");
    if( (cr3 = clone_vm()) == 0){
        kernlog(5, "after clone failed");
        return -1;
    }
    kernlog(5, "after clone");

    pcb = create_process( parent_pcb, cr3);{
        // failed to create child process
        if(pcb == NULL){
            release_vm(cr3);
            return -1;
        }
    }

    // added child to parent's child queue
    q_push( & parent_pcb->child_queue, & pcb->child_qnode);

    tcb = get_only_thread(pcb);
    esp0 = tcb_to_esp0( (uintptr_t) tcb );

    // prepare the kernel stack for newly created one so that when he
    // get switched to run for the first time he will run as thought
    // he's been switched out previously.
    prep_childstk( esp0, & tcb->save_esp);

    /* copying swexn handler */{
        tcb->user_handler = parent_tcb->user_handler;
        tcb->swexn_esp3 = parent_tcb->swexn_esp3;
        tcb->args = parent_tcb->args;
    }

    // for resources manager
    __sync_fetch_and_add(&process_num, 1);

    res = pcb->pid;
    // add newborn to run queue.
    // NOTE: the new one may start here.
    scher_add_newlycreated(tcb);

    return res;
}

void
fork_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(FORK_INT);

    funcaddr = (uintptr_t) ( &fork_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);
}

