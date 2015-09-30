/** @file idle.c
 *  @brief idle module implementation file
 *
 *  This is the idle module. The idle is used when logically no one is
 *  running on cpu. At this moment we should switch idle into the cpu
 *  and get it run. What idle does basically is that he will loop
 *  forever.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <idle.h>
#include "../syscall/fork/fork.h"
#include <pcb.h>
#include <tcb.h>
#include <kernstk.h>
#include <conswi.h>
#include <scheduler.h>
#include <stddef.h>
#include <assert.h>
#include <cr.h>
#include <vmm.h>
#include <common_macro.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

static tcb_t *__idle_tcb;

#define general_regs_num 8


/** @brief loop function
 *  @return Never returns.
 */
static void _very_idle()
{
    while(1){
        // take if off (blocked) while there's runnable thread
    }
}

/** @brief prepare the idle stack for the first time when idle get
 *          switched into cpu in context switch.
 *
 *  @param stk_addr Stack address to prepare
 *  @param save_esp The place to save the final esp in.
 *  @return Void.
 */
static void prep_idlestk( uintptr_t stk_addr, uintptr_t *save_esp)
{

//  stack graph:
//  1.  ret addr to _very_idle
//  2.  fake old %ebp
//  3.  ret addr to _fork_switchret
//  4.  old %ebp to 2
//  5.  saved states
//
    stk_addr -= FOUR_BYTE;
    PUT_FOUR_BYTE(stk_addr, & _very_idle );
    stk_addr -= FOUR_BYTE;
    PUT_FOUR_BYTE(stk_addr, 0);
    stk_addr -= FOUR_BYTE;
    PUT_FOUR_BYTE(stk_addr, & _fork_switchret);
    stk_addr -= FOUR_BYTE;
    PUT_FOUR_BYTE(stk_addr, stk_addr + 2 * FOUR_BYTE);

    push_all_general_regs(stk_addr);

    *save_esp = stk_addr - ( general_regs_num * FOUR_BYTE );
}

/** @brief idle initialization function.
 *
 *  We are creating the a process without parent for idle process. The
 *  page table is cloned from the first process ('init' process). Then
 *  we are preparing the stack for it.
 *
 *  @return Void.
 */
void idle_init()
{
    uintptr_t cr3;
    pcb_t *pcb;

    cr3 = clone_vm();
    assert(cr3 != 0);

    pcb = create_process(NULL, cr3);
    assert(pcb != NULL);

    __idle_tcb = get_only_thread(pcb);
    __idle_tid = __idle_tcb->tid;

    prep_idlestk( tcb_to_esp0((uintptr_t) __idle_tcb),
                  & __idle_tcb->save_esp  );
}


/** @brief get idle to be the next one to run.
 *
 *  This happens when no run is going to be in run queue and cpu.
 *
 *  @return Void.
 */
void get_idle_next()
{
    scher_push_job(__idle_tcb);
}

/** @brief testifying that whether the thread is idle itself or not.
 *
 *  @return Void.
 */
int I_am_idle(tcb_t *tcb)
{
    return (tcb == __idle_tcb);
}
