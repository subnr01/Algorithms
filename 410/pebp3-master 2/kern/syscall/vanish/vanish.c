/** @file vanish.c
 *  @brief vanish handler and installer implementation file
 *
 *  This is the handler of vanish syscall and also a wrapper function for
 *  internal kernel vanish syscal (defined in 'inc/_wait.h', implemented
 *  in 'wait/wait.c')
 *
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bug No known bugs.
 */
#include <stdint.h>
#include <stddef.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "vanish.h"
#include <pcb.h>
#include <tcb.h>
#include <scheduler.h>
#include <klock.h>
#include <cpu.h>
#include <_wait.h>
#include <asm.h>
#include <res_manage.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


/** @brief vanish handler
 *
 *  We're calling the finish function for the thread, at the mean time
 *  detecting whether it's the last thread. If it's, then we need to do
 *  process vanish. After all that we make the thread die.
 *
 *  @return Void.
 */
void
vanish_handler()
{
    tcb_t *tcb;
    pcb_t *pcb;
    int last_thr;

    tcb = get_cur_tcb();
    pcb = tcb->pcb;

    thr_vanish_lock( & pcb->wait_item);

    last_thr = fini_thread(tcb);

    if( last_thr ) {
        // only the last thread gets here.
        _vanish();
        __sync_fetch_and_sub(&process_num, 1);
    }

    disable_interrupts();{
        // we need to make sure this is atomic because if we are not
        // doing this:
        // 1. the page table is released before thread dies. The thread
        // can't do context switch.
        // 2. Or the thread dies before the lock's released. The
        // process's resources wouldn't be freed.
        thr_vanish_unlock( & pcb->wait_item);// spin swap, definitely released
        die_thr(tcb);
    }
    cpu_relax(); // doesn't matter whether the thread get here or not.

}

void
vanish_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(VANISH_INT);

    funcaddr = (uintptr_t) ( &vanish_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}


