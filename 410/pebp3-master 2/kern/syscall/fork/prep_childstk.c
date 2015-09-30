#include <conswi.h>
#include <stdint.h>
#include <string.h>
#include <cr.h>
#include "fork.h"
#include <conswi.h>
#include <common_macro.h>

// SS, ESP, EFLAGS, CS, EIP + 4 callee saved regs
// (5+4) items * 4 bytes
#define handler_stack_param_size ((5+4)*4)

#define general_regs_num 8

//  stack graph:
//  1.    iret needed fork trap state and saved regs
//  2.    ret addr to _fork_forkwrapper
//  3.    old %ebp to 1
//  4.    ret addr to _fork_forkhandler
//  5.    old %ebp to 3
//  6.    saved states
void prep_childstk( uintptr_t stk_addr, uintptr_t *save_esp)
{
    uintptr_t p_esp0; // previous esp0

    p_esp0 = (uintptr_t) get_esp0();

    stk_addr = stk_addr - handler_stack_param_size;
    memcpy( (void *) (stk_addr),
      (void *) (p_esp0 - handler_stack_param_size),
      handler_stack_param_size );

    stk_addr -= FOUR_BYTE;
    PUT_FOUR_BYTE(stk_addr, ( & _fork_forkwrapper));
    stk_addr -= FOUR_BYTE;
    PUT_FOUR_BYTE(stk_addr, ( stk_addr + 2 * FOUR_BYTE));
    stk_addr -= FOUR_BYTE;
    PUT_FOUR_BYTE(stk_addr, ( & _fork_switchret));
    stk_addr -= FOUR_BYTE;
    PUT_FOUR_BYTE(stk_addr, ( stk_addr + 2 * FOUR_BYTE));

    push_all_general_regs(stk_addr);

    *save_esp = stk_addr - (general_regs_num * FOUR_BYTE);

}
