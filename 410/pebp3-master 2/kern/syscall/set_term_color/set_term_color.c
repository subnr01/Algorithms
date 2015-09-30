#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "set_term_color.h"
#include <console.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


int
set_term_color_handler(int color)
{
    return set_term_color(color);
}

void
set_term_color_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(SET_TERM_COLOR_INT);

    funcaddr = (uintptr_t) ( &set_term_color_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
