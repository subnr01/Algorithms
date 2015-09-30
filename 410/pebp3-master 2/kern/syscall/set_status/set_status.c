#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "set_status.h"
#include <pcb.h>
#include <_wait.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

void
set_status_handler(int status)
{
    pcb_t *pcb;

    pcb = get_cur_pcb();

    kernlog(5, "pid: %d, status: %d", pcb->pid, status);

    // race condition could happen: multiple threads set status.
    wait_set_status( & pcb->wait_item, status);
}

void
set_status_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(SET_STATUS_INT);

    funcaddr = (uintptr_t) ( &set_status_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}


