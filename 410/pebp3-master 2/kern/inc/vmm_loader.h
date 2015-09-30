/** @file vmm_loader.h
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 */
#ifndef _VMM_LOADER_H
#define _VMM_LOADER_H

#include <stdint.h>
#include <types.h>
#include <vmm.h>

int count_user_pages();
void alloc_real(uintptr_t start, size_t len, vmm_flag_t flag);
void alloc_zfod(uintptr_t start, size_t len, vmm_flag_t flag);
void reserveclear_usermem(int extra);
int try_reserve_frame(int cnt);

#endif // for #ifndef _VMM_LOADER_H
