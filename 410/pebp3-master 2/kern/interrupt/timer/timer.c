/** @file timer.c
 *  @brief This is the timer handler module for timer interrupt
 *
 *  When timer goes off, we have mainly two things to do:
 *  1. check the sleep queue and see if anyone who's sleeping should be
 *  waken up.
 *
 *  2. switch the currently running thread back to last of run queue and
 *  switch the next item in run queue in to run in a cpu.
 *
 *  @author Hongchao Deng (hongchad)
 */
#include <stdint.h>
#include <asm.h>
#include <timer_defines.h>
#include <interrupt_defines.h>
#include <gateinst.h>
#include "timer.h"
#include <scheduler.h>
#include <idt.h>
#include <sleep_lib.h>
#include <getticks.h>


#define KERNLOG_L1_ON
#include <kernlog.h>

static long long num = 0;

long long
getticks()
{
    return num;
}


void
timer_handler()
{
    long long sleep_time;
    tcb_t *tcb;

    if( !intr_ok ){
        // this is used to handle IRQ7 problem.
        // even though we enable interrupts, it doesn't mean we are
        // ready to handle them.
        outb(INT_CTL_PORT, INT_ACK_CURRENT);
        return;
    }

    /* wake up sleeping thread if needed */{
        sleep_time = sleep_mintime();
        // There's an assumpt made here:
        // the maximum sleep time is the max number of long long.
        // The sleep time is calculated as current time plus the time
        // thread wants to sleep for.
        //
        // If the sleep time calculated is larger than LLMAX, there
        // could be an overflow problem.
        // I'm making this assumption because approaching to that large
        // would take ten years if timer interrupt interval is about
        // 10ms in this project.
        if(sleep_time <= num ){
            kernlog(5, "min time: %lld", sleep_time);
            tcb = sleep_pop();
            unblock_thr(tcb);
            scher_push_job( tcb );
        }
    }

    num++;

    outb(INT_CTL_PORT, INT_ACK_CURRENT);

    // scheduler reschedules
    scher_resche();
}

void
timer_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(TIMER_IDT_ENTRY);

    funcaddr = (uintptr_t) ( &timer_wrapper);

    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    /* initialize the timer */
    outb(TIMER_MODE_IO_PORT, TIMER_SQUARE_WAVE);

    /*
     *  timer cycles: two bytes
     *      first:  LSB
     *      second: MSB
     */
    outb(TIMER_PERIOD_IO_PORT, TIMER_CYCLE & 0xFF);
    outb(TIMER_PERIOD_IO_PORT, (TIMER_CYCLE >> 8) & 0xFF);
}
