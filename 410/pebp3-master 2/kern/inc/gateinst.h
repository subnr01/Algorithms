#ifndef _GATEINST_H
#define _GATEINST_H

#include <stdint.h>

#define DPL_USER 3
#define DPL_KERN 0

uintptr_t get_gateaddr(unsigned int entry_num);
void trap_gateinst(uintptr_t gate_addr, uintptr_t funcaddr, int dpl);
void interrupt_gateinst(uintptr_t gate_addr, uintptr_t funcaddr, int dpl);

#endif // for #ifndef _GATEINST_H
