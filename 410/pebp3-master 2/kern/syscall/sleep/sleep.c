/** @file sleep.c
 *  @brief sleep handler and installer implementation file
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bug No known bugs.
 */
#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "sleep.h"
#include <sched.h>
#include <asm.h>
#include <tcb.h>
#include <sleep_lib.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


int
sleep_handler(int ticks)
{
    tcb_t *tcb;

    if(ticks == 0)
        return 0;
    if(ticks < 0)
        return -1;

    tcb = get_cur_tcb();

    if(sleep_add(tcb, ticks) == -1 ){
        return -1;
    }

    return 0;
}

void
sleep_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(SLEEP_INT);

    funcaddr = (uintptr_t) ( &sleep_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
