/** @file readline.c
 *
 *  The readline function interacts tightly with keyboard handler.
 *  Basically when there's no key in the keyboard buffer, the thread
 *  must be io-blocked; When there's another thread who's already been
 *  io-blocked, the thread must be io-blocked as well. The readline has
 *  a first come first serve order.
 *
 *  Notice that when a thread's waken up, there will be a context
 *  switch to get the woken thread to run. In context switch, we ensure
 *  that if a thread was just woken up from IO blocking, we don't enable
 *  the interrupts in order to make sure thread finish his reading.
 *
 *  We use a local buffer here to help prevent the race condition on
 *  malicious or inadvertent remove of previously existing pages.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
#include <stdint.h>
#include <stddef.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "readline.h"
#include <asm.h>
#include <console_io.h>
#include <vmm_check.h>
#include <common_macro.h>
#include <pcb.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


/** @brief readline handler
 *  @return num of chars copied to the buffer on success.
 *          negative integer on failure.
 */
int
readline_handler(uintptr_t args)
{
    int len;
    char buf[KEYBUF_SIZE];
    char *usrbuf;

    int num;
    int key;

    tcb_t *tcb = get_cur_tcb();

    page_lock();
    /* len */{
        if(check_fourbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        len = (int ) GET_FOUR_BYTE(args);

        if(len == 0){
            page_unlock();
            return 0;
        }
        if(len < 0 || len > KEYBUF_SIZE){
            page_unlock();
            return -1;
        }
    }

    /* user buf */{
        args += sizeof(int);

        if(check_addrbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }
        usrbuf = (char *) GET_ADDR_BYTE(args);


    }

    page_unlock();

    num = 0;
    disable_interrupts();{
        // if some other thread is blocked on readline
        if(console_io_has_waiting()){
            console_io_wait(tcb); // will block itself and yield to next one
            // interrupts are disabled when coming back
        }

        do{
            key = readchar();

            if(key == '\n'){
                break;
            }
            else if(key == -1){
                // nothing to be read, wait for keyboard input
                console_io_wait(tcb);
                // context switched back, thread's blocked previously
                // interrupts are disabled when coming back
                unblock_thr(tcb);

            }
            else{
                if(key != '\b'){
                    buf[num++] = key;
                    if(num == len) break;
                }
                else{
                    if(num > 0)
                        num --;
                }

            }

        } while( 1 );

    } enable_interrupts();

    if(num < len){
        buf[num++] = '\n';
    }

    page_lock();

    // should check writable here
    if(check_string_writable(usrbuf, len) < 0){
        page_unlock();
        return -1;
    }

    int i;
    for(i = 0; i <= num; i ++){
        usrbuf[i] = buf[i];
    }

    page_unlock();

    return num;
}

void
readline_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(READLINE_INT);

    funcaddr = (uintptr_t) ( &readline_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
