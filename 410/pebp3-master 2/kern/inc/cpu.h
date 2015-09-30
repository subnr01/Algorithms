/** @file cpu.h
 *  @brief cpu header file
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @bug No known bugs.
 */
#ifndef _CPU_H
#define _CPU_H

#include <tcb.h>

typedef struct _cpu_t{
    tcb_t *run_job; // the thread using this cpu.
} cpu_t;

void cpu_init();
void cpu_relax();

#endif // for #ifndef _CPU_H
