#include <stdint.h>
#include <stddef.h>
#include <syscall_int.h>
#include <gateinst.h>
#include <scheduler.h>
#include "fork.h"
#include <pcb.h>
#include <tcb.h>
#include <kernstk.h>
#include <conswi.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


int
thread_fork_handler()
{
    uintptr_t esp0;
    pcb_t *pcb;
    tcb_t *tcb;
    int res;

    pcb = get_cur_pcb();
    tcb = create_thread( pcb );
    // failed to create another thread
    if(tcb == NULL) return -1;

    esp0 = tcb_to_esp0( (uintptr_t) tcb );
    prep_childstk( esp0, &tcb->save_esp);

    res = tcb->tid;
    // added to run queue
    scher_add_newlycreated(tcb);

    return res;
}

void
thread_fork_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(THREAD_FORK_INT);

    funcaddr = (uintptr_t) ( &thread_fork_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);
}

