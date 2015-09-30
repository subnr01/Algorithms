#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "get_cursor_pos.h"
#include <vmm_check.h>
#include <common_macro.h>
#include <console.h>
#include <pcb.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


int
get_cursor_pos_handler(uintptr_t args)
{
    int *row, *col;
    int krow, kcol;

    get_cursor(&krow, &kcol);

    page_lock();
    /* row pointer */{
        if(check_addrbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        row = (int *) GET_ADDR_BYTE(args);
        // check user writable
        if(check_fourbyte((uintptr_t)row, 1) < 0){
            page_unlock();
            return -1;
        }
    }
    args += ADDR_BYTE;
    /* col pointer */{
        if(check_addrbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        col = (int *) GET_ADDR_BYTE(args);
        // check user writable
        if(check_fourbyte((uintptr_t)col, 1) < 0){
            page_unlock();
            return -1;
        }
    }
    *row = krow;
    *col = kcol;

    page_unlock();

    return 0;
}

void
get_cursor_pos_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(GET_CURSOR_POS_INT);

    funcaddr = (uintptr_t) ( &get_cursor_pos_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
