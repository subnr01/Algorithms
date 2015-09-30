#include "no_ecode.h"
#include "../exception.h"
#include <gateinst.h>
#include <ureg.h>
#include <x86/idt.h>
#include <vanish.h>
#include <tcb.h>
#include <asm.h>
#include <stdio.h>


void DE_handler(ureg_t context)
{
    enable_interrupts();

    exception_handler(&context);
}

/** @brief Machine check handler (Abort)
 *  we don't need to return or save registers
 */
void mc_handler()
{
    printf("machine check!\n");
    set_status_handler(-2);
    vanish_handler();
}


void
no_ecode_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;


    // machine check
    gateaddr = get_gateaddr(IDT_MC);
    funcaddr = (uintptr_t) ( &mc_handler);
    trap_gateinst(gateaddr, funcaddr, DPL_KERN);

    gateaddr = get_gateaddr(IDT_NMI);
    funcaddr = (uintptr_t) ( &mc_handler);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    // Divide Error
    gateaddr = get_gateaddr(IDT_DE);
    funcaddr = (uintptr_t) ( &DE_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    gateaddr = get_gateaddr(IDT_DB);
    funcaddr = (uintptr_t) ( &DB_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_USER);

    gateaddr = get_gateaddr(IDT_BP);
    funcaddr = (uintptr_t) ( &BP_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_USER);

    gateaddr = get_gateaddr(IDT_OF);
    funcaddr = (uintptr_t) ( &OF_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_USER);

    gateaddr = get_gateaddr(IDT_BR);
    funcaddr = (uintptr_t) ( &BR_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    gateaddr = get_gateaddr(IDT_UD);
    funcaddr = (uintptr_t) ( &UD_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    gateaddr = get_gateaddr(IDT_NM);
    funcaddr = (uintptr_t) ( &NM_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    gateaddr = get_gateaddr(IDT_NM);
    funcaddr = (uintptr_t) ( &NM_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    gateaddr = get_gateaddr(IDT_MF);
    funcaddr = (uintptr_t) ( &MF_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    gateaddr = get_gateaddr(IDT_MC);
    funcaddr = (uintptr_t) ( &MC_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);

    gateaddr = get_gateaddr(IDT_XF);
    funcaddr = (uintptr_t) ( &XF_wrapper);
    interrupt_gateinst(gateaddr, funcaddr, DPL_KERN);
}
