/** @file mapper.c
 * @brief this file contains modules and functions for solving the
 * virtual memory mapping problem
 *
 * When we tried to move the page directory and table outside of the bottom
 * 16MB we encountered a few issues.
 *
 * In order to modify the entries in the page table we need a mapping
 * to the page table, but in order to have a mapping we need a entry
 * already present in the page table. We wanted a way to reduce the number
 * of mappings needed in virtual space.
 *
 * The problem we found was that in order to do such a mapping we needed
 * a mapping to the page directory, but our mapping function relied on
 * traversing the page table logically, which coincidentally relies on
 * mappings already being in place. If we hide things away in physical
 * frames by leaving them un-mapped we need to establish a mapping
 * when editing the page table. Thus, we seemed to run into a quasi-
 * circular dependency problem here.
 *
 * We have abstracted this away as a separate problem. Doing so promotes
 * modularity and encapsulation of concerns.
 *
 * To summarize the problem can be described as follows:
 *  Given a logical address and a physical address:
 *      Map the logical address to the given physical address
 *
 *
 * In order to break the cycle we need at least one consistent mapping.
 * To what you ask? Well to the page table representing the logical page
 * which we use specifically for remapping. The mapping to the page table
 * needs to be preserved.
 *
 * There are a few ways we can do this and each way is a different
 * tradeoff between TLB misses and Virtual Address space usage
 *
 * ### Step 1: Gain access to page directory ###
 *
 * var = get_cr3()              |
 * logic_table[map_index] = var |
 * invlpg[map]  // +1 tlb miss  |
 * var = map[INDEX(addr)]       |  var = VMM_GET_DIR() // -1 virtual page
 *
 * ### Step 2: Gain access to relevant page table and write new frame entry ###
 * logic_table[map_index] = var |
 * invlpg[map] // +1 tlb miss   |
 * map[INDEX(addr)] = frame     |array_based_lookup(addr) //-1024 virtual pages
 *
 *
 * It looks like a good compromise is give up a page of virtual address space
 * to access the page directory, and accept tlb misses to save 1024 virtual pages.
 *
 * However, unless we want to use locking to block access to the special
 * re-mapping page we will need to give each thread its own special page, but
 * this no longer becomes advantageous once the number of threads grows beyond
 * 1024 (virtual page usage is O(n) where n is the number of threads).
 *
 * Alternatively we can simply save and restore the mappings during context
 * switchs. This would introduce more time overhead, but the amount of virtual
 * page overhead (in regards to this mapping problem) reduces to 3 pages. One
 * page for remapping, one page to the remap page table, and one page for the
 * dir (the logical address we use for the dir will not change once the dir is
 * created, thus we don't need a page for the dir page page table).
 *
 * Originally we planned for heavy sanitization of arguments in these functions
 * but overtime it became more efficient for the callee to do this.
 *
 * Automatically a allocating page table for an address during a call to mapper
 * makes sense, as soon after allocation we will be writing in the requested 
 * mapping.
 *
 *
 * @author Alan Keith (arkeith)
 * @author Hongchao Deng (hongchad
 * @bugs No known bugs
 */
#include "_page_allocator.h"
#define KERNLOG_L1_ON
#include <kernlog.h>

uintptr_t new_page_table(uintptr_t *dir_entry, vmm_flag_t dir_flag);

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
 *
 */
int mapper(uintptr_t addr, uintptr_t frame, vmm_flag_t flags){
    kernlog(5, "Mapping logical address %x to physical frame %x\n",
        addr, frame);
    
    int rv = mapper_lookup_phase(addr);
    if (rv != VMM_SUCCESS){
        return rv;
    }

    /* begin map entry write phase */

    /* get access to the remapping page */
    vmm_table *remap = (vmm_table *) VMM_REMAPPER_PAGE;

    assert(frame % PAGE_SIZE == 0);
    /* use the remap page to write the requested mapping of addr to frame */
    remap->array[VMM_PTABLE_INDEX(addr)] = (frame | flags);
    invl_tlb(addr);

    kernlog(5, "Mapped logical address %x to physical frame %x\n",
        addr, frame);
    return VMM_SUCCESS;
}

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
int mapper_lookup_phase(uintptr_t addr){
    kernlog(5, "Changing remapping page to point to addr %x 's page table\n",
        addr);
    /* get access to the directory table */
    vmm_table *dir = (vmm_table *) VMM_GET_DIR();

    /* get page table and save a copy of the entry */
    uintptr_t *entry = &dir->array[VMM_DIR_INDEX(addr)];
    vmm_flag_t flags = (vmm_flag_t) VMM_GET_ENTRY_FLAG(entry);

    uintptr_t table_addr; //save the physical address of the page table

    /* does the page table currently exist for the logical address? */
    if(!VMM_TEST_PRESENT(flags)){
        kernlog(5, "Allocating a new page table to handle addr %x \n",
            addr);

        table_addr = new_page_table(entry, flags);
        if (table_addr == 0){
            kernlog(2, "mapper_lookup_phase failed: "
                "No memory for new page table\n");
            return VMM_ERR_NO_MEM;
        }
    }
    else{
        table_addr = VMM_GET_ENTRY_NOFLAG(entry);
    }

    /* get access to page table for remapping page */
    vmm_table *logic_table = (vmm_table *) VMM_GET_REMAP_TABLE;

    /* change the virtual to physical mapping of the remap page */
    logic_table->array[VMM_PTABLE_INDEX((uintptr_t) VMM_REMAPPER_PAGE)] =
        table_addr | VMM_DEFAULT_FLAG; //present, supervisor, rw

    invl_tlb(VMM_REMAPPER_PAGE); //VMM_REMAP_ADDR entry is invalidated
    kernlog(5, "mapper_lookup_phase successful: remapping page points "
        "to addr %x's page table \n", addr);
    return VMM_SUCCESS;
}



/** @brief set up new page table and write it's dir_entry
 *
 *  For this function we are going to request a new physical frame,
 *  write its physical address into the directory entry, and modify
 *  the current directory entry flags to set the present bit and
 *  the user bit (kernel space is already allocated so new page tables
 *  are for user space)
 *
 *  If we are out of physical frames this function will fail
 *
 *  @param *dir_entry place to write the entry
 *  @param dir_flag current flag settings for the entry
 *
 *  @return physical address of the page table or 0 on error
 */
uintptr_t new_page_table(uintptr_t *dir_entry, vmm_flag_t dir_flag){
    //allocate a new table
    uintptr_t frame = pmm_alloc_frame();
    if (frame == 0)
        return 0;
    assert(VMM_SUCCESS == mapper(VMM_REMAPPER_PAGE, frame, VMM_DEFAULT_FLAG));
    memset((void*)VMM_REMAPPER_PAGE, 0, sizeof(vmm_table));

    //adjust directory entry flag
    vmm_flag_t flags = VMM_FLAG_READWRITE(VMM_FLAG_USER(VMM_FLAG_PRESENT(dir_flag)));

    VMM_SET_ENTRY(dir_entry, frame, flags);
    return frame;
}
