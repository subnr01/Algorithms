#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "set_cursor_pos.h"
#include <console.h>
#include <vmm_check.h>
#include <common_macro.h>
#include <pcb.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


int
set_cursor_pos_handler(uintptr_t args)
{
    int row, col;

    page_lock();

    /* row */ {
        if( check_fourbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        row = GET_FOUR_BYTE(args);
    }
    /* col */ {
        args += FOUR_BYTE;
        if( check_fourbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        col = GET_FOUR_BYTE(args);
    }

    page_unlock();

    return set_cursor(row, col);

}

void
set_cursor_pos_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(SET_CURSOR_POS_INT);

    funcaddr = (uintptr_t) ( &set_cursor_pos_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
