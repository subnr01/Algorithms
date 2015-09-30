/** @file deschedule.c
 *  @brief deschedule syscall module
 */
#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "deschedule.h"
#include <sched.h>
#include <vmm_check.h>
#include <pcb.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


/** @brief deschedule calling thread
 *  @return 0 on success. Negative number on failure.
 */
int
deschedule_handler(int *reject)
{

    page_lock();
    /* check address of argument */{
        if(check_fourbyte((uintptr_t)reject, 0) < 0){
            page_unlock();
            return -1;
        }
    }

    if(*reject != 0){
        page_unlock();
        return 0;
    }

    page_unlock();

    desche();

    return 0;
}

void
deschedule_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(DESCHEDULE_INT);

    funcaddr = (uintptr_t) ( &deschedule_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
