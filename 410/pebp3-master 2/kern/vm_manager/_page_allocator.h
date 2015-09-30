/** @file _page_allocator.h
 *  @brief contains prototypes and data structures related to virtual memory
 *
 *  Mostly used by functions in vm_manager directory
 *
 *  @author Alan Keith (arkeith)
 *  @auther Hongchao Deng (hongchad)
 *  @bugs No known bugs
 */
#ifndef _PAGE_ALLOCATOR_H
#define _PAGE_ALLOCATOR_H

#include <vmm.h>
#include <pmm.h>
#include "page_allocator.h"
#include <types.h>
#include <string.h>
#include <cr.h>
#include <common_kern.h>
#include <page.h>
#include <assert.h>
#include "invl_tlb.h"
#include <malloc.h>

/** @brief macros for declaring page table
 *  Remember we have 10 bits for page directory, 10 bits for page table,
 *  and 12 physical bits.
 */
#define VMM_TABLE_SIZE (1024) //!< number of initial slots in table

/** @brief page directory/table struct
 *  used for ease of page directory/table manipulation
 */
typedef struct  _table{
    uintptr_t array[VMM_TABLE_SIZE]; //!< array for table entries
} vmm_table;


/** @brief mask out the low flags bits */
#define VMM_FLAG_BITS (4095) //!< (1<<12)-1 , quicker to just make it 4095

/** @used to isolate page and table index bits from a logical address */
#define VMM_MASK (1023)

/** @brief mask out the directory entry bits */
#define VMM_DIR_MASK (VMM_MASK << 22) 

/** @brief get the page_dir index for a logical address */
#define VMM_DIR_INDEX(addr) ((((addr) & VMM_DIR_MASK) >> 22) & VMM_MASK)

/** @brief given directory index, get the logical address which will use the
 * next index */
#define VMM_DIR_NEXTI(dir_i) (((dir_i) + 1) << 22)

/** @brief mask out the table entry bits */
#define VMM_PTABLE_MASK (VMM_MASK << 12)

/** @brief get the page_tqable index for a logical address */
#define VMM_PTABLE_INDEX(addr) (((addr) & VMM_PTABLE_MASK) >> 12)

uintptr_t *get_table_entry(uintptr_t addr);

/** @brief given a ptr to a page/dir table entry, return entry's flags */
#define VMM_GET_ENTRY_FLAG(entry) ((*(entry)) & (VMM_FLAG_BITS))

/** @brief given a ptr to a page/dir table entry, return de-flagged entry */
#define VMM_GET_ENTRY_NOFLAG(entry) ((*(entry)) & (~VMM_FLAG_BITS))

/** @brief macro for setting an entry 
 *  @param ptr location of the entry
 *  @param addr the physical address to write in the upper 20bits of the entry
 *  @param flags the flags to set the entry
 *
 *  NOTE: right now I am heavily sanitizing the parameters
 */
#define VMM_SET_ENTRY(ptr, addr, flags) (\
    (*(ptr)) = ((( (uintptr_t) (addr)) & (~VMM_FLAG_BITS)) \
    | (((uintptr_t) (flags)) & (VMM_FLAG_BITS))))

/** @brief given the flags for a page entry, check the present flag */
#define VMM_TEST_PRESENT(flags) ((flags) == VMM_FLAG_PRESENT((flags)))

/** @brief maps a logical frame to a physical address with the given flags 
 * 
 * This is function solves the aforementioned mapping problem in 2 parts
 * 
 * First, change the remapping page to point to the page table for given addr
 * Second, modify the entry, establishing the required entry
 *
 * Over time, it became more effective to sanitize arugments outside of mapper,
 * thus in this current version we require the caller to ensure the validity
 * of the passed arguments arguments (eg. alignment)
 *
 * This function can fail if the page table for logical address has not
 * been allocated AND we are unable to acquire a new frame to use as a 
 * page table.
 *
 * @param addr logical address of the mapping
 * @param frame the physical frame address logical address will access
 * @param flags the permission flags to give the new mapping
 * 
 * @return 0 on success or negative error code on failure
 */
int mapper(uintptr_t addr, uintptr_t frame, vmm_flag_t flags);


/** @brief have remapping page map to page table for given logical address
 * 
 *  This functions main goal is to change the physical memory the logical
 *  address of the special remapping page accesses. To do this we have to
 *  do the following
 *
 *  1. lookup physical address of page table for addr from the page directory
 *  2. make it the entry for the logical address of the remapping page
 *  
 *  This is one module used by the mapper function.
 *  
 *  NOTE: If the logical address's page table is not currently initialized,
 *  we will do so in this function. However this means this function can
 *  fail if we are out of physical frames.
 *
 *
 *  @param addr logical address whose page table we want access to
 *
 *  @return 0 on success or a negative error code on failure
 *
 *  NOTE: the physical frame allocator will call the mapper code, however
 *  we avoid a recursion problem providing that the page table for remapping
 *  address is already present
 *
 */
int mapper_lookup_phase(uintptr_t addr);
#endif /* _PAGE_ALLOCATOR_H */

