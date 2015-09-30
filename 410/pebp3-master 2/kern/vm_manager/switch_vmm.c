/** @file switch_vmm.c
 *  @brief We need to preserve a special remapping page on context switch
 *  this function takes care of that
 *
 *  To avoid situations where threads are messing with eachothers mappings
 *  we need this
 *
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 */
#include <switch_vmm.h>
#include "_page_allocator.h"

/** @brief save the location VMM_REMAPPER_PAGE is mapped to 
 *  @param *remap the location to save the mapping
 */
void save_remap( uintptr_t *remap){
    vmm_table *table = (vmm_table *) VMM_GET_REMAP_TABLE;
    unsigned int page_i = VMM_PTABLE_INDEX(VMM_REMAPPER_PAGE);
    *remap = (uintptr_t) VMM_GET_ENTRY_NOFLAG(&table->array[page_i]);
}

/** @brief restore the location VMM_REMAPPER_page was mapped to
 *  @param *remap the location the mapping was saved at
 */
void restore_remap( uintptr_t *remap){
    vmm_table *table = (vmm_table *) VMM_GET_REMAP_TABLE;
    unsigned int page_i = VMM_PTABLE_INDEX(VMM_REMAPPER_PAGE);
    uintptr_t entry = *remap;
    VMM_SET_ENTRY(&table->array[page_i], entry, VMM_DEFAULT_FLAG);
}
