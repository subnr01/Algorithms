#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "make_runnable.h"
#include <sched.h>
#include <idle.h>

#define KERNLOG_L5_ON
#include <kernlog.h>

int
make_runnable_handler(int tid)
{
    if( tid < 0 || tid == __idle_tid)
        return -1;
    return make_run(tid);
}

void
make_runnable_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(MAKE_RUNNABLE_INT);

    funcaddr = (uintptr_t) ( &make_runnable_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
