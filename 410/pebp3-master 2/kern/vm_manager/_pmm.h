/** @file _pmm.h
 *  @brief contains a few macros used by frame allocators
 */
#ifndef __PMM_H
#define __PMM_H

#include <klock.h>
#include <stdint.h>

#define GET_LIST_PREV(addr) ( * (uintptr_t *) (addr) )

int freeframe_count;
uintptr_t free_start;
kmutex_t frame_mutex;

uintptr_t zfodframe;

#endif // for #ifndef __PMM_H
