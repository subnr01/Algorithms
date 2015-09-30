/** @file pagefault.c
 *  @brief this file contains the core of the page fault handler
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs
 */

#include "pagefault.h"
#include <gateinst.h>
#include <ureg.h>
#include <idt.h>
#include <vanish.h>
#include <vmm.h>
#include <pmm.h>
#include <asm.h>
#include <assert.h>
#include <seg.h>
#include <x86/idt.h>
#include <swexn.h>
#include <tcb.h>
#include <pcb.h>
#include <cr.h>
#include <simics.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief the page fault handler
 *  we accept as an arg the register context
 *  if the page fault is not a ZFOD fault,
 *  we pass things off to the swexn handler
 *  @param context the register state at time of fault
 */
void
pagefault_handler(ureg_t context)
{
    assert(context.cs != SEGSEL_KERNEL_CS);

    // we don't need to disable interrupts when handling thread specific
    // issues. Just need to ensure registers are saved.
    enable_interrupts();

    uintptr_t phys_addr;


    kernlog(5, "faulting address: %08x, instruction: %08x",
      (unsigned) context.cr2, (unsigned) context.eip);

    page_lock();
    // check we have access to that entry
    phys_addr = get_physical_addr(context.cr2);


    if(phys_addr == zfodframe){
        assert( ! (vmm_getflags(context.cr2) & VMM_FLAG_READWRITE(0)) );
        zfod_pagefault( & context);
        page_unlock();
    }
    else{
        page_unlock();

        tcb_t *tcb;

        tcb = get_cur_tcb();

        if (tcb->user_handler != 0){
            //deregister handler and invoke
            swexn_handler_t handler = tcb->user_handler;
            tcb->user_handler = 0;

            uintptr_t esp3 = tcb->swexn_esp3;
            tcb->swexn_esp3 = 0;

            void *args = tcb->args;
            tcb->args = 0;

            user_handler_launcher(args, &context, esp3, handler);
        }
        else{
            // kill the thread
            set_status_handler(-2);
            vanish_handler();
        }
    }
}

/** @brief set up page idt */
void
pagefault_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(IDT_PF);

    funcaddr = (uintptr_t) ( &pagefault_wrapper);

    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);
}


