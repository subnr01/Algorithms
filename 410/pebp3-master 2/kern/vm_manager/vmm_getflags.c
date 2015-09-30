/* @file vmm_getflags.c
 * @brief quick and easy interface for getting flags for virtual address
 *
 * This function/file is mainly just to encapsulate looking acquiring
 * flags for a virtual address, it is mainly used by syscall modules
 *
 * @author Alan Keith (arkeith)
 * @author Hongchao Deng (hongchad)
 * @bugs No known bugs
 *
 * Limitations: while we are checking we assume that things
 * have been locked done such that virtual memory system 
 * does not change during the midst of this evaluation.
 *
 * AKA we don't want the table being changed in the middle
 * of our lookup, thus we require those using this function 
 * to ensure this safety.
 */
#include "page_allocator.h"
#include "_page_allocator.h"
#include <assert.h>

/** @brief get the flags associated with a virtual address
 *  @param addr the logical address
 *  @return the flags or 0 on error
 *
 *  NOTE: this function can fail if we run out of memory and are unable
 *  to allocate a page table for the given address in mapper_lookup_phase
 */
vmm_flag_t vmm_getflags(addr)
{
    //we weren't able to
    if(mapper_lookup_phase(addr) != VMM_SUCCESS)
        return 0;

    vmm_table *ptable = (vmm_table*) VMM_REMAPPER_PAGE;
    unsigned int index = VMM_PTABLE_INDEX(addr);
    vmm_flag_t flags = VMM_GET_ENTRY_FLAG(&ptable->array[index]);

    return flags;
}
