/** @file vm_release.c
 *  @brief this file contains function modules for freeing
 *  physical frames used by the virtual memory system
 *
 *  There are a variety of different kinds of freeing the virtual memory 
 *  system needs to support. In the case of execve, we need to clear all 
 *  memory except the kernel space pages and the special reserved pages.
 *  In the example of the last thread in a process ending, we need to 
 *  also collect the physical frames for the page directory and the page
 *  table.
 *
 *  This file contains functions responsible for achieving those tasks, and 
 *  aims to do so in a modular way due to the different levels of freeing 
 *  which may be required by the virtual memory system.
 *
 *  There are two main types of free, clear and release. In the clear version
 *  the virtual memory system being freed is the active CR3, this is commonly
 *  used by execve. In the release version we manipulate virtual memory which
 *  is not installed in CR3, this is commonly used by clean-up code. The
 *  release version also frees the frames used for special pages and the page
 *  directory, unlike the clear version which must maintain these structures
 *  to operate.
 *
 *  The clear version has been moved to vmm_loader.c due to special constraints
 *  regarding frame reservation.
 *
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 *  @bugs no known bugs
 *
 */
#define KERNLOG_L1_ON
#include <kernlog.h>
#include "_page_allocator.h"

/** @brief helper function for clearing virtual memory resources
 *
 * To clear the virtual memory we need to release all frames used for user
 * pages and page tables, leaving the kernel memory, page directory, and
 * page table which holds special frames untouched.
 *
 * Thus is a main case and a special case to take care of. The main case is
 * freeing pure user pages and page tables. The special case is the last page
 * table (the one which houses special frames).
 *
 * Until we reach the last page table, the process is simple. Starting at user
 * memory incrementing by PAGE_SIZE, release every present page until page
 * tables will switch. Then free the page table and modify the page directory.
 *
 * For the special case we just have to free the present pages up to the lowest
 * special page (VMM_REMAPPER_PAGE)
 *
 * NOTE, we need VMM_GET_DIR() and VMM_GET_REMAP_TABLE to have been setup
 * in order to use this function.
 *
 * @param *dir mapped logical address to manipulate the page directory
 */
void clear_user_mem(vmm_table *dir){
    //loop will take care of variables, but we need to placate compiler
    auto void change_mapping(vmm_table *dir, unsigned int dir_i);
    auto void free_page(vmm_table *page, unsigned int page_i, uintptr_t addr);
    auto void free_page_table(vmm_table *dir, unsigned int dir_i, 
        uintptr_t addr);

    vmm_table *page = (vmm_table*) VMM_GET_FORK_OLDPAGE(); 
    uintptr_t addr;
    unsigned int page_i = VMM_PTABLE_INDEX(USER_MEM_START);
    unsigned int dir_i = VMM_DIR_INDEX(USER_MEM_START);
    
    for(addr = USER_MEM_START; addr < (uintptr_t) VMM_REMAPPER_PAGE;
        addr += PAGE_SIZE){
        
        //get indices and test if page is present
        page_i = VMM_PTABLE_INDEX(addr);
        dir_i = VMM_DIR_INDEX(addr);
        
        vmm_flag_t flags = VMM_GET_ENTRY_FLAG(&dir->array[dir_i]);
        
        if (!VMM_TEST_PRESENT(flags)){ //skip ahead in loop
            uintptr_t temp_addr = VMM_DIR_NEXTI(dir_i);
            if (temp_addr > addr){
                addr = temp_addr-PAGE_SIZE;//
                continue;
            }
            else{
                break; 
            }
        }

        if (page_i == 0){ 
            //change page mapping to next page table
            change_mapping(dir, dir_i); //page table update
        }
        flags = VMM_GET_ENTRY_FLAG(&page->array[page_i]);
        if (VMM_TEST_PRESENT(flags)){
            free_page(page, page_i, addr);
        }
        if (page_i == VMM_TABLE_SIZE-1){
            //last entry was release, now release table iteslf
            free_page_table(dir, dir_i, addr);
        }

    }
    
    /* Below are small helper functions to keep code from getting too 
     * cluttered */
    
    /** @brief change VMM_GET_FORK_OLDPAGE to point to a new page table
     *  @param *dir, ptr to page directory
     *  @param dir_i, the index we can use to get addr of page table
     */
    inline void change_mapping(vmm_table *dir, unsigned int dir_i){
        uintptr_t phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);
        //now we need to change the mapping, note that this mapper call
        //should always succeed and this assert is put in to ease code
        //changing burdens
        assert(VMM_SUCCESS == mapper(VMM_GET_FORK_OLDPAGE(), phys_addr, 
            VMM_DEFAULT_FLAG));
    }
    /** @brief free the corresponding frame
     *  @param *page, the page table
     *  @param page_i the index into the page table for this frame
     *  @param addr the logical address, needed to invalidate tlb
     *
     *  NOTE: we assume that the page is present 
     */
    inline void free_page(vmm_table *page, unsigned int page_i, 
        uintptr_t addr){

        uintptr_t phys_addr = VMM_GET_ENTRY_NOFLAG(&page->array[page_i]);
        pmm_free_frame(phys_addr);
        page->array[page_i] = 0;
        invl_tlb(addr);
    }

    /** @brief free the corresponding page table 
     *  
     *  @param *dir the page directory
     *  @param dir_i, the index we can use to get addr of page table
     *  @param addr, for clearing the tlb
     */
    inline void free_page_table(vmm_table *dir, unsigned int dir_i, 
        uintptr_t addr){

        uintptr_t phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);
        pmm_free_frame(phys_addr);
        dir->array[dir_i] = 0; 
        invl_tlb(addr);

    }
}


/* @brief responsible for releasing virtual memory system
 *
 * This function will release all physical pages unique to a virtual memory 
 * system as defined by the given page directory. The frames used for the page
 * directory, non-shared page tables, and the page tables used for the special
 * frames are also freed.
 *
 * It is important that the active virtual memory (the page directory in
 * cr3) is not the page directory which is being freed, otherwise the
 * world will end.
 *
 * We just need to do the normal clear_user_mem, release the last page table,
 * and release the page directory
 *
 * @param dir the physical address of the page directory we are freeing
 *
 * @return this function should always succeed
 */
void release_vm(uintptr_t dir_phys){

    kernlog(5, "Entered release_vm\n");
    kernlog(5, "Getting mapping to directory frame");
    
    //set up mapping to directory
    assert(VMM_SUCCESS == mapper(VMM_GET_FORK_DIR(), dir_phys, VMM_DEFAULT_FLAG));
    //above assertion is supposed to always succeed
    
    vmm_table *dir = (vmm_table *) VMM_GET_FORK_DIR();
    clear_user_mem(dir);

    //free the last page table
    unsigned int dir_i = VMM_TABLE_SIZE-1;
    vmm_flag_t flags = VMM_GET_ENTRY_FLAG(&dir->array[dir_i]);
    if (VMM_TEST_PRESENT(flags)){
        uintptr_t phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);
        pmm_free_frame(phys_addr);
    }
    //free the page directory
    pmm_free_frame(dir_phys); 
}
