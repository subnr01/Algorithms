#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "halt.h"
#include <conswi.h>
#include <idle.h>
#include <asm.h>
#include <scheduler.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


void
halt_handler()
{
    disable_interrupts(); {
        while(1);
    }
}

void
halt_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(HALT_INT);

    funcaddr = (uintptr_t) ( &halt_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
