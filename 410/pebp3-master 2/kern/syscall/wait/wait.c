/** @file wait.c
 *
 *  This is the handler of wait syscall and also a wrapper function for
 *  internal kernel wait syscal (defined in 'inc/_wait.h', implemented
 *  in 'wait/wait.c')
 *
 */
#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "wait.h"
#include <_wait.h>
#include <vmm_check.h>
#include <pcb.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


/** @brief wait handler
 *  @return pid on success. negative number on failure.
 */
int
wait_handler(int *status_ptr)
{

    int kern_staptr;
    int res;

    res = _wait(&kern_staptr);

    page_lock();
    /* check address of argument */{
        if( check_fourbyte( (uintptr_t)status_ptr, 1) < 0){
            page_unlock();
            return -1;
        }
        *status_ptr = kern_staptr;
    }
    page_unlock();

    return res;

}

void
wait_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(WAIT_INT);

    funcaddr = (uintptr_t) ( &wait_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
