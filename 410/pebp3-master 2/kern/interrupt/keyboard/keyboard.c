/** @file keyboard.c
 *  @brief This module handles keyboard inputs.
 *
 *  Everytime a keyboard interrupt comes in, we process the key code and
 *  get useful chars. After this step normally do we push the new chars
 *  into the keyboard buffer. However, we need to handle two special
 *  cases:
 *  1. newline '\n'. We need to wake up anyone who's blocking on io.
 *  2. backspace '\b'. We need to remove one item from the buffer.
 *  However, there's a special case that the thread calling readline
 *  previously has retrieved all the buffer chars and there's no item
 *  currently in keyboard buffer. We know in this case the thread's
 *  already been blocked and he must have a local buffer. We push those
 *  backspace to keyboard buffer to notify running thread.
 *
 *  Lastly, because we have a buffer to store chars we could not
 *  guarantee infinite inputs without being retrieved. If the buffer is
 *  full, we use FIFO rule to squeeze out previous items.
 *
 *  @author Hongchao Deng (hongchad)
 */
#include <stdint.h>
#include <asm.h>
#include <gateinst.h>
#include <interrupt_defines.h>
#include <x86/keyhelp.h>
#include <idt.h>
#include <console.h>
#include <console_io.h>

#include "keyboard.h"

#define KERNLOG_L1_ON
#include <kernlog.h>


#define MOD_INC(n) (((n)+1) % KEYBUF_SIZE)
#define MOD_DEC(n) (((n)+KEYBUF_SIZE-1) % KEYBUF_SIZE)

static char keybuf[KEYBUF_SIZE];
static int front, rear;

static void
keyboard_init()
{
    front = rear = 0;
}

static int keybuf_empty() { return front == rear; }

static int process_key(int key);

/** @brief Main keyboard interrupt handler function
 *  @return Void.
 */
void
keyboard_handler()
{
    char key;

    if(!intr_ok){ // not started yet
        inb(KEYBOARD_PORT);
        outb(INT_CTL_PORT, INT_ACK_CURRENT);
    }

    key = (char) inb(KEYBOARD_PORT);
    outb(INT_CTL_PORT, INT_ACK_CURRENT);

    key = process_key(key);
    if(key == -1)
        return;

    putbyte(key); // echoed back

    if( key != '\b') {
        keybuf[rear] = key;

        rear = MOD_INC(rear);
        if(rear == front) // full
            front = MOD_INC(front); // squeeze front
    }
    else{
        /* backspace */
        if( ! keybuf_empty() &&
          keybuf[MOD_DEC(rear)] != '\b')
            rear = MOD_DEC(rear);
        else{
            keybuf[rear] = key;
            rear = MOD_INC(rear);
        }
    }

    if( key == '\n' && console_io_has_waiting() ){
        // wake up those who waited
        console_io_wakeup_next();
    }
}

void
keyboard_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    keyboard_init();

    gateaddr = get_gateaddr(KEY_IDT_ENTRY);
    funcaddr = (uintptr_t) ( &keyboard_wrapper);

    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);
}


static int
process_key(int key)
{
    key = process_scancode(key);

    if( KH_HASDATA(key) && KH_ISMAKE(key) ) {
        return KH_GETCHAR(key);
    }
    else {
        return -1;
    }
}

int
readchar()
{
    int key;

    if(keybuf_empty())
        return -1;

    key = keybuf[front];
    front = MOD_INC(front);
    return key;
}
