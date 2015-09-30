/** @file vmm.h
 *  @brief This file contains publically accessible macros and functions 
 *  related to virtual memory management
 *  
 *  This header mainly provides interfaces for setting up permission flags for
 *  pages, allocating pages, and changing apge permissions.
 *
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 *  @bugs No known bugs
 *
 */ 
#ifndef VMM_H
#define VMM_H

#include <types.h>
#include <stdint.h>
#include <page.h>
/*--- virtual memory ---*/
/** @brief macros for manipulating permission flags
 *  NOTE: each macro takes an int as an argument and operates on its bits 
 *  to set/unset flags, returning the modified flag bit map
 */

typedef int vmm_flag_t;

#define VMM_FLAG_PRESENT(flags) ((flags) | (0x1)) //!< page has physical frame
#define VMM_FLAG_NOT_PRESENT(flags) ((flags) & ~(0x1)) //!< no physical frame

#define VMM_FLAG_READWRITE(flags) ((flags) | (0x2)) //!< page can be written to
#define VMM_FLAG_READONLY(flags) ((flags) & ~(0x2)) //!< page is read-only

#define VMM_FLAG_USER(flags) ((flags) | (0x4)) //!< user allowed
#define VMM_FLAG_SUPERVISOR(flags) ((flags) & ~(0x4)) //!< supervisor only

#define VMM_WRITE_THROUGH(flags) ((flags) | (0x8)) //!< write-through caching
#define VMM_WRITE_BACK(flags) ((flags) & ~(0x8)) //!< write-back caching

#define VMM_DISABLE_CACHE(flags) ((flags) | (0x10)) //!< do not cache page
#define VMM_ENABLE_CACHE(flags) ((flags) & ~(0x10)) //!< allow caching of page

#define VMM_FLAG_GLOBAL(flags) ((flags) | (0x100)) //!< save page on tlb flush
#define VMM_FLAG_LOCAL(flags) ((flags) & ~(0x100)) //!< page can be flushed

/** @brief custom flags
 * The present flag is used to specify when a mapping to a physical frame
 * has been installed for a page. We desired a flag to register a logical
 * page's availability, this is desirable for synchronization solutions
 *
 */
#define VMM_FLAG_ALLOC(flags) ((flags) | (0x200)) //!< page has a mapping 
#define VMM_FLAG_FREE(flags) ((flags) & ~(0x200)) //!< used to mark a page free

#define VMM_DEFAULT_FLAG ( \
    VMM_FLAG_PRESENT( \
    VMM_FLAG_READWRITE( 0))) //!< page permissions as returned by vmm_alloc_pages

#define VMM_ZFOD_FLAG (\
  VMM_FLAG_PRESENT(0) )


#define VMM_CLEAR_FLAG(flag) (0) //!< unset's all flags

/** @brief error codes for vmm functions*/
#define VMM_SUCCESS (0) //!< function complete successfully
#define VMM_ERR_BADSTART (-1) //!< not allowed to allocate start address
#define VMM_ERR_OVERFLOW_INT (-2) //!< length leads to an integer overflow
#define VMM_ERR_OVERFLOW_ADDR (-3) //!< address range overflow
#define VMM_ERR_DUPALLOC (-4) //!< parts of range already allocated
#define VMM_ERR_DUPFREE (-5) //!< parts of range already free
#define VMM_ERR_NO_MEM (-6) //!< function could not complete, no more frames 

/** @brief activates virtual memory system
 */
void activate_vm(void);

uintptr_t clone_vm(void);
void release_vm(uintptr_t);
vmm_flag_t vmm_getflags();
uintptr_t get_physical_addr(uintptr_t addr);
int mapper(uintptr_t addr, uintptr_t frame, vmm_flag_t flags);

#endif /* VMM_H */
