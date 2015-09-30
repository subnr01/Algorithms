#ifndef _FORK_H
#define _FORK_H

#include <stdint.h>

void fork_wrapper();
int fork_handler();

void _fork_forkwrapper();

void prep_childstk( uintptr_t stk_addr, uintptr_t *save_esp);
void push_all_general_regs(uintptr_t esp);

int thread_fork_handler();
int thread_fork_wrapper();

#endif // for #ifndef _FORK_H
