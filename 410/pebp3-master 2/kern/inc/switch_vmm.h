/** @file switch_vmm.h
 *  @brief because of the our implementation of virtual memory we need
 *  to save and restore the remmapper page of previous and next thread.
 *
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 */
#ifndef _SWITCH_VMM_H
#define _SWITCH_VMM_H

#include <stdint.h>

void save_remap( uintptr_t *remap);
void restore_remap( uintptr_t *remap);

#endif // for #ifndef _SWITCH_VMM_H
