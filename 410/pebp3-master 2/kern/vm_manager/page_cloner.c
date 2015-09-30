/** @file page_cloner.c
 *  @brief this file contains function responsible for copying page tables
 *
 *  The cloning problem can be specified as follows: given a process make
 *  a working copy of the virtual memory system that can function without
 *  interference from the original copy.
 *
 *  An easy point to note is that the bottom 16MB of space is direct mapped,
 *  and thus processes can share those page tables.
 *
 *  One tricky issue is the mapping stored at the top of the virtual address
 *  space. Because we may be asking for new frames during the cloning, these
 *  mappings may change.
 *
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 *  @bugs No known bugs
 *
 *  Mostly used when spawning new processes
 *
 *  Note that these functions currently do not support multi-threaded fork
 */
#define KERNLOG_L1_ON
#include <kernlog.h>
#include "_page_allocator.h"

/* @brief helper function for getting new frames before paging is turned on
 *
 * We zero out the frame once we get it
 * @return physical address of the new frame
 */
static uintptr_t new_frame(){
    uintptr_t frame = pmm_alloc_frame();
    if (frame == 0){
        //out of memory, abort
        kernlog(1, "pmm_alloc_frame() failed, out of memory");
        return 0;
    }
    else{
        assert(VMM_SUCCESS == mapper(VMM_REMAPPER_PAGE, frame, VMM_DEFAULT_FLAG));
        memset((void*)VMM_REMAPPER_PAGE, 0, sizeof(vmm_table));
        return frame;
    }
}


/** clone the active virtual memory system
 *
 *  We make a copy of the active virutal memory system and construct
 *  a new page directory with the appropriate page tables
 *
 *  @return the physical frame address of the new page directory
 * NOTE: the assert statements here should always pass, but are kept
 * for documentation purposes
 */
uintptr_t clone_vm(){
    kernlog(5, "Entered clone_vm\n");


    kernlog(5, "Getting initial directory frame");

    /* get frame for new process page directory and zero it out*/
    vmm_table *dir = (vmm_table *) new_frame();
    if (dir == 0)
        return 0; //out of memory

    vmm_flag_t flags = VMM_FLAG_GLOBAL(VMM_DEFAULT_FLAG);

    /* get mapping for new process page directory */
    assert(VMM_SUCCESS == mapper(VMM_GET_FORK_DIR(), (uintptr_t) dir,
        VMM_DEFAULT_FLAG));

    /* copy the kernel mapings over */
    size_t kernel_size = (VMM_DIR_INDEX(
        ((uintptr_t) USER_MEM_START)-((uintptr_t)PAGE_SIZE))
        +1) * sizeof(uintptr_t);

    bcopy((void*)VMM_GET_DIR(), (void*)VMM_GET_FORK_DIR(), kernel_size);

    /* now for every use page which is present, but below special pages, copy
     * data over */
    vmm_table *new_dir = (vmm_table*)VMM_GET_FORK_DIR();
    vmm_table *old_dir = (vmm_table*)VMM_GET_DIR();
    vmm_table *new_page = (vmm_table*) 0;//placate compiler
    vmm_table *old_page = (vmm_table*) 0;
    uintptr_t addr;

    /* for each entry if dir entry present
        acquire new page table
        for each page entry if present
        get new frame, copy contents, insert mapping */

    unsigned int page_i = VMM_PTABLE_INDEX(USER_MEM_START);
    unsigned int dir_i = VMM_DIR_INDEX(USER_MEM_START);
    for(addr = USER_MEM_START; addr < (uintptr_t) VMM_REMAPPER_PAGE;
        addr += PAGE_SIZE){


        page_i = VMM_PTABLE_INDEX(addr);
        //fill out directory entry
        dir_i = VMM_DIR_INDEX(addr);

        flags = VMM_GET_ENTRY_FLAG(&old_dir->array[dir_i]);

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
        if (page_i == 0){ //need a new table

            //get a new page and map to it
            uintptr_t new_page_addr = new_frame();
            if (new_page_addr == 0){
                //out of memory
                release_vm((uintptr_t) dir);
                return 0;
            }

            assert(VMM_SUCCESS ==
                mapper(VMM_GET_FORK_PAGE(), new_page_addr,
                    VMM_DEFAULT_FLAG));

            new_page = (vmm_table *) VMM_GET_FORK_PAGE();


            VMM_SET_ENTRY(&new_dir->array[dir_i], new_page_addr,
                VMM_GET_ENTRY_FLAG(&old_dir->array[dir_i]));

            //get a mapping to the old page table
            assert(VMM_SUCCESS == mapper(VMM_GET_FORK_OLDPAGE(),
                VMM_GET_ENTRY_NOFLAG(&old_dir->array[dir_i]),
                VMM_DEFAULT_FLAG));


            old_page = (vmm_table *) VMM_GET_FORK_OLDPAGE();
        }

        flags = VMM_GET_ENTRY_FLAG(&old_page->array[page_i]);

        if (VMM_TEST_PRESENT(flags) ){
            uintptr_t temp;
            if( VMM_GET_ENTRY_NOFLAG(&old_page->array[page_i]) == zfodframe){
                assert( !(flags & VMM_FLAG_READWRITE(0)) );

                temp = zfod_alloc_frame();

                // try to reserve another frame
                if(temp == 0){
                    release_vm((uintptr_t) dir);
                    return 0;
                }
                assert(temp == zfodframe);
            }
            else{
                temp = new_frame();
                //allocate a new frame and copy the contents
                if (temp == 0){
                    //out of memory
                    release_vm((uintptr_t) dir);
                    return 0;
                }

                assert(VMM_SUCCESS == mapper(VMM_GET_COPY_PAGE(), temp,
                    VMM_DEFAULT_FLAG));

                uintptr_t phys_addr = get_physical_addr(addr);
                assert(phys_addr);

                assert(VMM_SUCCESS == mapper(VMM_REMAPPER_PAGE, phys_addr,
                    VMM_DEFAULT_FLAG));
                bcopy((void*) VMM_REMAPPER_PAGE, (void*) VMM_GET_COPY_PAGE(), PAGE_SIZE);
            }

            // set the entry in page table pointing to the address
            VMM_SET_ENTRY(&new_page->array[page_i], temp, flags);

        }
        else{
            VMM_SET_ENTRY(&new_page->array[page_i], 0, flags);
        }
    }
    kernlog(5, "Kernel space mapped, setting up special pages \n");

    //set up remap page table
    flags = VMM_DEFAULT_FLAG; //supervisor, rw, present flags all set
    page_i = VMM_PTABLE_INDEX(VMM_GET_REMAP_TABLE);
    VMM_SET_ENTRY(&new_page->array[page_i], new_dir->array[dir_i],
        VMM_DEFAULT_FLAG);

    //set up VMM_GET_DIR
    page_i = VMM_PTABLE_INDEX(VMM_GET_DIR());
    VMM_SET_ENTRY(&new_page->array[page_i], (uintptr_t) dir, VMM_DEFAULT_FLAG);

    return (uintptr_t) dir;
}
