#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include <cr.h>
#include <kernstk.h>
#include <tcb.h>
#include "gettid.h"

#define KERNLOG_L5_ON
#include <kernlog.h>


int
gettid_handler()
{
    uintptr_t esp0;
    tcb_t *tcb;

    esp0 = get_esp0();
    tcb = (tcb_t *) esp0_to_tcb(esp0);

    return tcb->tid;
}

void
gettid_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(GETTID_INT);

    funcaddr = (uintptr_t) ( &gettid_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
