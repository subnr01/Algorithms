/** @file has_ecode.c
 *  @brief This file is used for exceptions that have error code
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs
 */
#include "has_ecode.h"
#include "../exception.h"
#include <gateinst.h>
#include <ureg.h>
#include <x86/idt.h>
#include <vanish.h>
#include <tcb.h>
#include <asm.h>
#include <stdio.h>


void TS_handler(ureg_t context)
{
    enable_interrupts();

    exception_handler(&context);
}

/** @brief double fault handler (Abort)
 *  we don't need to return or save registers
 */
void df_handler()
{
    printf("double fault!\n");
    set_status_handler(-2);
    vanish_handler();
}


void
has_ecode_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;


    // double fault
    gateaddr = get_gateaddr(IDT_DF);
    funcaddr = (uintptr_t) ( &df_handler);
    trap_gateinst(gateaddr, funcaddr, DPL_KERN);


    // Invalid TSS
    gateaddr = get_gateaddr(IDT_TS);
    funcaddr = (uintptr_t) ( &TS_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    // Segment Not Present
    gateaddr = get_gateaddr(IDT_NP);
    funcaddr = (uintptr_t) ( &NP_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    // stack segment fault
    gateaddr = get_gateaddr(IDT_SS);
    funcaddr = (uintptr_t) ( &SS_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    // General protection
    gateaddr = get_gateaddr(IDT_GP);
    funcaddr = (uintptr_t) ( &GP_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    // alignment check
    gateaddr = get_gateaddr(IDT_AC);
    funcaddr = (uintptr_t) ( &AC_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);
}
