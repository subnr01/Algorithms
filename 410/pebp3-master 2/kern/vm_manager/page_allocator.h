/** @file page_allocator.h
 *  @brief contains function prototypes and macros other vm_manager modules may need
 *  access to for manipulating virtual memory 
 *
 *  Originally this was a supposed to be a more publically visible header file,
 *  with private versions in _page_allocator.h. Now this has become an interface
 *  for manipulating virtual memory
 */

#ifndef PAGE_ALLOCATOR_H
#define PAGE_ALLOCATOR_H

#include <stdint.h>

/** @brief get the physical address mapped to by the logical address
 *  @param addr, the logical addr
 *  @return the physical address or 0 on error   
 */
uintptr_t get_physical_addr(uintptr_t addr);

/** @brief this is used heavily by the frame allocators, it enables us
 * to keep track of the physical frame list across all threads. It is
 * stored in the kernel and when initialized will point to the beginning
 * of a logical page
 */
uintptr_t alloc_freeframe;

/** @brief this is a macro which has been used to manipulate the free frame
 * list over time. Currently it reads the value of the next available 
 * physical frame
 */
#define FREEFRAME_VADDR (* ((uintptr_t *) alloc_freeframe))

/** @brief only used in virtual memory clone and release function,
 * this logical address is used to access and modify a page directory
 * which is not active (not in CR3).
 */
#define VMM_GET_FORK_DIR() (0xFFFFF000)

/** @brief only used in virtual memory clone and release function,
 * this logical address is used to access and modify a page tables which are 
 * not active (the corresponding page directory is not in CR3).
 */
#define VMM_GET_FORK_PAGE() (0xFFFFE000)

/** @brief when properly setup, this logical address may be used to access
 * and modify the active (in CR3) page table.
 */
#define VMM_GET_DIR() (0xFFFFD000)

/** @brief this logical address serves as a quick reference to a page table
 * which can be used to access and modify its contents a needed. It is remapped
 * as to the needed page tables. NOTE: this mapping is NOT preserved during 
 * thread context switches. Thus if you use this page you need to ensure
 * that another thread cannot be simultaneously using it.
 *
 * This is enforced by the page locks and not allowing multi_threaded fork
 */
#define VMM_GET_FORK_OLDPAGE() (0xFFFFC000)

/** @brief this logical address is used when cloning memory,
 * it allows us to copy the contents of physical frames
 */
#define VMM_GET_COPY_PAGE() (0xFFFFB000)

/** @brief this logical address can be used to access and modify the
 * virtual page table for the VMM_REMAPPER_PAGE*
 */
#define VMM_GET_REMAP_TABLE (0xFFFFA000)

/** @brief this logical address is frequently used for checking
 * page entries, and setting up new virtual to physical frame mappings.
 * It needs to be preserved on context switches.
 */
#define VMM_REMAPPER_PAGE (0xFFFF9000)

#endif /* PAGE_ALLOCATOR_H */
