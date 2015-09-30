/** @file readfile.c
 *
 *  This module mainly checks the validity of parameters passed from
 *  user. The copying bytes stuff is done in getbytes in loader module.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "readfile.h"
#include <loader.h>
#include <common_macro.h>
#include <vmm_check.h>
#include <pcb.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief readfile handler
 *  @return the number of bytes copied on success.
 *          negative integer on failure.
 */
int
readfile_handler(uintptr_t args)
{
    char *filename;
    char *buf;
    int count;
    int offset;

    page_lock();
    /* filename */{
        if( check_addrbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        filename = (char *) GET_ADDR_BYTE(args);
        if( check_string(filename) < 0){
            page_unlock();
            return -1;
        }
    }

    /* buf */{
        args += ADDR_BYTE;
        if( check_addrbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        buf = (char *) GET_ADDR_BYTE(args);
    }

    /* count */ {
        args += FOUR_BYTE;
        if( check_fourbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        count = (int) GET_FOUR_BYTE(args);
        if( check_string_writable(buf, count) < 0){
            page_unlock();
            return -1;
        }
    }

    /* offset */ {
        args += FOUR_BYTE;
        if( check_fourbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        offset = (int) GET_FOUR_BYTE(args);
    }

    int res = getbytes(filename, offset, count, buf);

    page_unlock();


    return res;

}

void
readfile_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(READFILE_INT);

    funcaddr = (uintptr_t) ( &readfile_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
