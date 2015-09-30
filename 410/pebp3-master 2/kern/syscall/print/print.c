/** @file print.c
 *  @brief printing to the screen.
 *
 *  There's a global mutex to prevent two threads printing chars to the
 *  screen interleavingly.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "print.h"
#include <stdint.h>
#include <klock.h>
#include <console.h>
#include <common_macro.h>
#include <vmm_check.h>
#include <pcb.h>

#define KERNLOG_L5_ON
#include <kernlog.h>


static kmutex_t print_mutex;

/** @brief print handler
 *  @return 0 on success.
 *          negative integer on failure.
 */
int
print_handler(uintptr_t args)
{
    int len;
    char *buf;

    page_lock();
    /* len */{
        if( check_fourbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }

        len = (int) GET_FOUR_BYTE(args);
        if(len < 0){
            page_unlock();
            return -1;
        }
        if(len == 0){
            page_unlock();
            return 0;
        }
    }
    /* buf */ {
        args += FOUR_BYTE;
        if(check_addrbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }

        buf = (char *) GET_ADDR_BYTE(args);
        if( check_string_writable(buf, len) < 0){
            page_unlock();
            return -1;
        }
    }


    kmutex_lock(&print_mutex);{
        putbytes(buf, len);
    } kmutex_unlock(&print_mutex);

    page_unlock();

    return 0;
}

void
print_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(PRINT_INT);

    funcaddr = (uintptr_t) ( &print_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

    // init
    kmutex_init( & print_mutex);
}
