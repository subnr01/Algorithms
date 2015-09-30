/* @file page_allocator.c
 * @brief contains functions for finding the physical frame attached to a 
 * a logical address
 *
 * This module has evolved quite heavily over the course of the kernel, 
 * originally it was responsible for all logical page allocation,
 * including setting the page flags, allocating the pages
 * logically as well as freeing them, and managing pages. As things
 * evolved and the virtual memory implementation changed, files got
 * moved around.
 *
 * One important design decision was whether vmm_set_page_flags and
 * vmm_alloc_pages should handle page alignment for the callers:
 *
 * Choice 1: (functions align and round address range and length for caller)
 *      Pros:
 *          Reduces repeated code for callers (eg. loader)
 *          Eliminates some safety checks from page_allocator internals
 *
 *      Cons:
 *          Risk of hiding caller errors and unintended function calls
 *              (ex. changing page permissions in an unintended way)
 *
 *          if callers have already aligned things, we waste time
 *
 *
 * Choice 2: (functions only allow page aligned/page multiple parameters)
 *
 *      Pros:
 *          Forces callers to be more aware of what pages are being modified
 *          Removes some responsibility from page allocator
 *
 *      Cons:
 *          Requires argument verification
 *          May lead to duplicate code
 *
 *
 * First Decision: Choice 1
 *
 * As our virtual memory implementation changed so did these functions.
 *
 *
 * Another important decision was where the page table should be placed. If
 * we keep everything in the kernel direct mapped memory it will certainly be
 * easier, but will be extremely inefficient in terms of kernel logical space.
 *
 * The big question then becomes how can we move our page directories and
 * page tables into physical frames, without keeping a logical address map
 * for each directory and page. We need at least one page which we can use
 * to logically map to page directories and page tables. For more details
 * see mapper.c
 */
#include "_page_allocator.h"
#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief locates the page table entry for a given address
 *
 *  If the page table for the given logical address is not present,
 *  we won't be able to get a physical address
 *
 *  @param addr, the logical address to lookup
 *  @return a pointer to the table entry or 0 on failure
 *
 */
uintptr_t *get_table_entry(uintptr_t addr){
    kernlog(5, "Entering get_table_entry(%x)\n", addr);

    //get a mapping to the page table for addr
    //use remapping page to access addr
    if (VMM_SUCCESS != mapper_lookup_phase(addr)){
        return 0;
    }

    //get interface to page table
    vmm_table *table = (vmm_table *) VMM_REMAPPER_PAGE;


    //get the table entry
    kernlog(5, "Exiting get_table_entry(%x)\n", addr);
    return &table->array[VMM_PTABLE_INDEX(addr)];
}

/** @brief get the physical address mapped to by the logical address
 *
 *  If the page table for the given logical address is not present,
 *  we won't be able to get a physical address
 *
 *  @param addr, the logical addr
 *  @return the physical address or 0 on error
 */
uintptr_t get_physical_addr(uintptr_t addr){
    uintptr_t *entry = get_table_entry(addr);
    if (entry == (uintptr_t *) 0 )
        return 0;

    if ((*entry) != VMM_FLAG_PRESENT(*entry)){
        return 0;
    }
    return VMM_GET_ENTRY_NOFLAG(entry);
}
