/** @file vm_installer.c
 *  @brief anything regarding setting up virtual memory found here
 * 
 *  This file contains functions for turning on VM for the first time
 *
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 *  @bug No known bugs
 */
#include "_page_allocator.h"
//#define KERNLOG_L1_ON
#include <kernlog.h>

/* @brief helper function for getting new frames before paging is turned on
 * 
 * We zero out the frame once we get it
 * @return physical address of the new frame
 */
static uintptr_t new_frame(){
    uintptr_t frame = pmm_getframe_nopaging(); //shouldn't fail on startup
    assert(frame);
    memset((void*)frame, 0, sizeof(vmm_table));
    return frame;
}
/** @brief installs virtual memory
 *
 *  The function has to accomplish the following:
 *
 *  1. Allocate a page directory
 *  2. Direct map the bottom 16MB, allocating page tables as needed
 *  3. Set up special pages (upper address range)
 *
 * NOTE: This version only initializes the bottom 16mb
 * of address space
 */
void activate_vm(){
    kernlog(1, "Entered activate_vm\n");
    

    kernlog(5, "Getting initial directory frame");

    vmm_table *dir = (vmm_table *) new_frame();

    vmm_table *page = (vmm_table*) 0;//placate compiler


    //kernel 16mb is global 
    vmm_flag_t flags = VMM_FLAG_GLOBAL(VMM_DEFAULT_FLAG); 
    
    kernlog(5, "Mapping kernel space\n");
    uintptr_t addr;

    //direct map bottom 16 MB
    for(addr = 0; addr < (uintptr_t) USER_MEM_START; addr += PAGE_SIZE){
        
        unsigned int page_i = VMM_PTABLE_INDEX(addr);
        if (page_i == 0){ //need a new table

            page = (vmm_table *) new_frame();
            //fill out directory entry
            unsigned int dir_i = VMM_DIR_INDEX(addr);
            VMM_SET_ENTRY(&dir->array[dir_i], &page->array, flags);
        }
        VMM_SET_ENTRY(&page->array[page_i], addr, flags);
    }
    kernlog(5, "Kernel space mapped, setting up special pages \n");
    
    flags = VMM_DEFAULT_FLAG; //supervisor, rw, present flags all set
    page = (vmm_table *) new_frame();
    
    //directory entry flag needs user entry because not every page is 
    //supervisor only at the top of the address space
    VMM_SET_ENTRY(&dir->array[VMM_TABLE_SIZE-1], &page->array, 
        VMM_FLAG_USER(flags));    


    /* VMM_REMAPPER_PAGE is the lowest special page, any pages above its
     * location are reserved by the kernel and need to be protected accordingly
     * the last page is used by the kernel for the physical frame allocator, 
     * so we need to be to treat its mapping differently
     */
    
    VMM_SET_ENTRY(&page->array[VMM_PTABLE_INDEX(VMM_GET_REMAP_TABLE)],
        &page->array, flags);//logical address for accessing page table


    VMM_SET_ENTRY(&page->array[VMM_PTABLE_INDEX(VMM_GET_DIR())], 
        &dir->array, flags); //logical address for manipulating page directory
    
    alloc_freeframe = (uintptr_t) smemalign(PAGE_SIZE, PAGE_SIZE);
    FREEFRAME_VADDR = (((uintptr_t) page) + PAGE_SIZE);
    //FREEFRAME_VADDR will initially point to the lowest available frame
    
    assert((uintptr_t) &dir->array == (uintptr_t) dir);
    assert((uintptr_t) &dir->array == (uintptr_t) &dir->array[0]);
    set_cr3((uintptr_t)&dir->array);


    /* turn on paging */{
        set_cr0( get_cr0() | CR0_PG );
        set_cr4(get_cr4() | CR4_PGE );
    }
    kernlog(1, "Virtual Memory activated, leaving activate_vm\n");
}

