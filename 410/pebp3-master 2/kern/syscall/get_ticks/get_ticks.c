#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "get_ticks.h"
#include <getticks.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


unsigned int
get_ticks_handler()
{
    return (unsigned) getticks();
}

void
get_ticks_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(GET_TICKS_INT);

    funcaddr = (uintptr_t) ( &get_ticks_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
