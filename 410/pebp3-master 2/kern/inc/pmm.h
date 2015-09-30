/** @file pmm.h
 *  @brief physical memory manager header file
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
#ifndef PMM_H
#define PMM_H

#include <stdint.h>

// the bottom 16MB is used for kernel. So the frames in those area won't
// be available from beginning. So it's safe to use 0 address as NULL.
// NOTE: later I figure out this is not so useful. I could use 0. it's a
// good number.
#define PMM_NULL 0


extern uintptr_t zfodframe;

uintptr_t pmm_getframe_nopaging();

/** @brief pmm init before vm is activated
 */
void pmm_init();


/* @brief allocating one free physical page at a time from free list
 *
 * @return PMM_ERROR on failure; valid physical address on success.
 */
uintptr_t pmm_alloc_frame();

/* @brief add the free physical page back to the free list
 *
 * @param paddr the physical address of bottom of the page which is to
 * be freed.
 *
 * @return Void.
 */
void pmm_free_frame(uintptr_t paddr);



void zfod_free_frame();
uintptr_t zfod_alloc_frame();
uintptr_t zfodfault_allocframe();
void exec_freeandreserve(uintptr_t paddr);
uintptr_t exec_alloc_reserved_frame();

#endif /* PMM_H */
