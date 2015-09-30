/** @file vmm_loader.c
 *  @brief functions useful for exec and loader and interacting with zfod
 *
 *  At first, this module was used by the loader to solve a problem where we
 *  release frames of a program, then try to load a new program, but fail
 *  cause we are out of memory. Because we have already release the frames
 *  there was no way to communicate the problem back to the original
 *  caller of exec.
 *
 *  The method we came up with relied on counting up how many unique frames
 *  were in use by the current program. We also would calculate how many
 *  frames the new program would need. If the current program had enough
 *  frames we would reserve the neccesary frames and release the extras.
 *  
 *  If even more frames were required we would attempt to reserve the extras.
 *
 *  We then realized this functionality was also useful in new_pages. If you
 *  look at the file 'frame_alloc.c' in the same directory, you will
 *  see there's a reservation first architecture in the frame
 *  allocation code. And this file provides the main functions doing the
 *  reservation, allocation (both real or zfod frames) and also two
 *  functions for counting and freeing the entire user memory.
 *
 * @author Hongchao Deng (hongchad)
 * @author Alan Keith (arkeith)
 * @bugs No known bugs
 *
 * LIMITATIONS 
 *
 * These functions rely on a reserve and alloc scheme. Thus 
 * the caller is responsible for ensuring they have reserved
 * the necessary frames such that our calls will not fail
 */
#include <vmm_loader.h>
#include <common_kern.h>
#include "page_allocator.h"
#include "_page_allocator.h"
#include <page.h>
#include <vmm.h>
#include <pmm.h>
#include <stdint.h>
#include <types.h>
#include <assert.h>
#include "_pmm.h"
#include <common_macro.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief allocate real frames for memory regions starting at @start
 *  and lengthening for @len size. The new pages will be set permission
 *  as per @flag. Normally the flag contains permission of user,
 *  present, and conditionally writable.
 *
 *  Note that this is NOT a ZFOD alloc, the pages allocated will have
 *  their contents set to 0, but each will be a unique physical frame
 *
 *  This is useful if you know you will be immediately writting
 *  to the pages after you have allocated them
 *
 *  Note that we explicitly allocate new page tables from reserved
 *  frame pool so they are not implicitly allocated when the 
 *  mapper function is called
 *
 *  @param start
 *  @param len
 *  @param flag
 *  @return Void.
 *
 *  Limitations: 
 *      This is a void function, thuse it CANNOT be permitted
 *      to fail. As such we require the caller to have reserved
 *      the necessary frames which will allow this alloc_real
 *      call to work
 */
void alloc_real(uintptr_t start, size_t len, vmm_flag_t flag)
{
    //you should always be asking for the present flag
    assert(flag & VMM_FLAG_PRESENT(0));

    uintptr_t addr, end;
    end = PAGE_ALIGN(start+len + PAGE_SIZE - 1);
    start = PAGE_ALIGN(start);
    vmm_table *dir = (vmm_table *) VMM_GET_DIR();
    vmm_table *ptb = (vmm_table *) VMM_GET_FORK_OLDPAGE();

    int new_dir = 1;

    for(addr = start; addr < end; addr += PAGE_SIZE){

        if(VMM_PTABLE_INDEX(addr) == 0){
            new_dir = 1;
        }

        if(new_dir) {
            /* create a new page table if not existed */
            int dir_i = VMM_DIR_INDEX(addr);
            uintptr_t *entry = & dir->array[dir_i];
            uintptr_t dir_phys_addr;
            vmm_flag_t dir_flag = VMM_GET_ENTRY_FLAG(&dir->array[dir_i]);

            if(!VMM_TEST_PRESENT(dir_flag)){
                dir_phys_addr = exec_alloc_reserved_frame();

                kernlog(5, "new page for dir: %08x, %08x", dir_i << 22, dir_phys_addr);
                VMM_SET_ENTRY(entry, dir_phys_addr, VMM_FLAG_READWRITE(flag));

                assert(VMM_SUCCESS == mapper(VMM_GET_FORK_OLDPAGE(),
                    dir_phys_addr,
                    VMM_DEFAULT_FLAG));
                memset(ptb, 0, PAGE_SIZE);

            }
            new_dir = 0;
        }

        uintptr_t phys_addr = exec_alloc_reserved_frame();
        assert(phys_addr % PAGE_SIZE == 0); //including assert(phys_addr != 0);

        kernlog(5, "new page for addr: %08x %08x", addr, phys_addr);
        assert(VMM_SUCCESS == mapper(addr, phys_addr, flag));
        memset((void *)addr, 0, PAGE_SIZE);
    }
}

/** @brief allocate zfod frames for memory regions starting at @start
 *  and lengthening for @len size. The new pages will be set permission
 *  as per @flag. Normally the flag contains permission of user,
 *  present. No matter what the writable permission will be set off in
 *  this function because of the nature of zfod pages.
 *
 *  Note that we explicitly allocate new page tables from reserved
 *  frame pool so they are not implicitly allocated when the 
 *  mapper function is called
 *
 *
 *  @param start
 *  @param len
 *  @param flag
 *  @return Void
 *  
 *  Limitations: 
 *      This is a void function, thuse it CANNOT be permitted
 *      to fail. As such we require the caller to have reserved
 *      the necessary frames which will allow this alloc_real
 *      call to work
 */
void alloc_zfod(uintptr_t start, size_t len, vmm_flag_t flag)
{
    assert(flag & VMM_FLAG_PRESENT(0));
    flag &= (~ VMM_FLAG_READWRITE(0) ) ;

    uintptr_t addr, end;
    end = PAGE_ALIGN(start+len + PAGE_SIZE - 1);
    start = PAGE_ALIGN(start);
    vmm_table *dir = (vmm_table *) VMM_GET_DIR();
    vmm_table *ptb = (vmm_table *) VMM_GET_FORK_OLDPAGE();

    int new_dir = 1;

    for(addr = start; addr < end; addr += PAGE_SIZE){

        // page dir
        if( VMM_PTABLE_INDEX(addr) == 0){
            new_dir = 1;
        }

        if(new_dir) {
            /* create a new page table if not existed */
            int dir_i = VMM_DIR_INDEX(addr);
            uintptr_t *entry = & dir->array[dir_i];
            uintptr_t dir_phys_addr;
            vmm_flag_t dir_flag = VMM_GET_ENTRY_FLAG(&dir->array[dir_i]);

            if(!VMM_TEST_PRESENT(dir_flag)){
                kernlog(3, "new page for dir: %08x", dir_i << 22);
                dir_phys_addr = exec_alloc_reserved_frame();
                VMM_SET_ENTRY(entry, dir_phys_addr, VMM_FLAG_READWRITE(flag));

                assert(VMM_SUCCESS == mapper(VMM_GET_FORK_OLDPAGE(),
                    dir_phys_addr,
                    VMM_DEFAULT_FLAG));
                memset(ptb, 0, PAGE_SIZE);
            }
            new_dir = 0;
        }

        kernlog(3, "new zfod page for addr: %08x, flag: %08x", addr, flag);
        assert(VMM_SUCCESS == mapper(addr, zfodframe, flag));
    }
}


/** @brief clears the entire user memory. However freed pages aren't
 *  counted back to the total free frames, estentially making them RESERVED.
 *
 *  If the current program image has more frames than we need to reserve
 *  we will free those extra frames in the normal way
 *
 * 
 *  @param extra number of frames to free normally from this image 
 *  @return Void.
 */
void reserveclear_usermem(int extra){

    vmm_table *dir = (vmm_table *) VMM_GET_DIR();

    //loop will take care of variables, but we need to placate compiler
    auto void change_mapping(vmm_table *dir, unsigned int dir_i);
    auto void free_page(vmm_table *page, unsigned int page_i, uintptr_t addr, int *extra);
    auto void free_page_table(vmm_table *dir, unsigned int dir_i,
        uintptr_t addr, int *extra);

    vmm_table *page = (vmm_table*) VMM_GET_FORK_OLDPAGE();
    uintptr_t addr;
    unsigned int page_i;
    unsigned int dir_i;

    // The clearing process will scans the entire user memory and make
    // decisions based on:
    // 1. presence of page table. If not present, skip the entire
    // page table size.
    // 2. presence of pages. We need to free pages.
    // 3. we might need to free page tables as well when scanning
    // touches the last page of current page table.
    assert(USER_MEM_START % PAGE_SIZE == 0);
    for(addr = USER_MEM_START; addr < (uintptr_t) MAX_VM_ADDR;
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
            free_page(page, page_i, addr, &extra);
        }

        if (page_i == VMM_TABLE_SIZE-1){
            //last entry was release, now release table iteslf
            free_page_table(dir, dir_i, addr, &extra);
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
     *  @param *extra pointer to the count of normal released frames
     *
     *  NOTE: we assume that the page is present
     */
    inline void free_page(vmm_table *page, unsigned int page_i,
        uintptr_t addr, int *extra){

        uintptr_t phys_addr = VMM_GET_ENTRY_NOFLAG(&page->array[page_i]);
        if( *extra == 0) //reserve frame
            exec_freeandreserve(phys_addr);
        else{
            // we don't need to reserve it.
            pmm_free_frame(phys_addr);
            *extra = *extra -1;
        }
        page->array[page_i] = 0;
        invl_tlb(addr);
    }

    /** @brief free the corresponding page table
     *
     *  @param *dir the page directory
     *  @param dir_i, the index we can use to get addr of page table
     *  @param addr for flushing tlb
     *  @param *extra pointer to the count of normal released frames
     */
    inline void free_page_table(vmm_table *dir, unsigned int dir_i,
        uintptr_t addr, int *extra){

        uintptr_t phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);
        if( *extra == 0)
            exec_freeandreserve(phys_addr);
        else{
            // we don't need to reserve it.
            pmm_free_frame(phys_addr);
            *extra = *extra -1;
        }
        dir->array[dir_i] = 0;
        invl_tlb(addr);

    }
}


/** @brief Count the pages used in user memory by this process.
 *
 *  Essentially we just loop through memory counting pages as we
 *  come across them
 *
 *  Limitations: we have assumed that the user process does not have more
 *  pages that can fit in an int, if memory is expanded in a future version of the
 *  kernel our asserts will detect if this is a valid area of concern 
 *
 *  @return the number of pages available for use.
 */
int count_user_pages()
{
    uintptr_t addr;
    int page_i;
    int dir_i;
    int new_dir;
    vmm_table *dir;
    vmm_table *page = (vmm_table *) VMM_GET_FORK_OLDPAGE();
    int res = 0;

    dir = (vmm_table *) VMM_GET_DIR();

    new_dir = 1;

    for(addr = USER_MEM_START; addr < (uintptr_t) MAX_VM_ADDR;
      addr += PAGE_SIZE){
        page_i = VMM_PTABLE_INDEX(addr);
        dir_i = VMM_DIR_INDEX(addr);

        vmm_flag_t flags = VMM_GET_ENTRY_FLAG( & dir->array[dir_i]);

        if( !VMM_TEST_PRESENT(flags)){
            uintptr_t temp_addr = VMM_DIR_NEXTI(dir_i);
            if( temp_addr > addr ){ // overflow
                addr = temp_addr - PAGE_SIZE;
                continue;
            }
            else{
                break;
            }
        }

        // detected new page directory address
        if( (addr % (1<<22)) == 0){
            new_dir = 1;
        }

        if(new_dir){
            uintptr_t phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);
            assert( VMM_SUCCESS == mapper( VMM_GET_FORK_OLDPAGE(),
                  phys_addr, VMM_DEFAULT_FLAG));
            assert(res + 1 > res);
            res ++; // count page tables
            //kernlog(5, "counted dir: %08x", dir_i << 22);

            new_dir = 0;
        }

        flags = VMM_GET_ENTRY_FLAG(&page->array[page_i]);

        if(VMM_TEST_PRESENT(flags)){
            assert(res + 1 > res);
            res ++; // count pages
            //kernlog(5, "counted: %08x", addr);
        }


    }

    return res;
}


/** @brief try to reserve the given number of frames
 *
 *  @param cnt the number of frames we want to reserve
 *  @return 1 on success 0 on failure.
 */
int try_reserve_frame(int cnt)
{
    int res = 0;
    kmutex_lock(&frame_mutex);{
        if(freeframe_count >= cnt){
            freeframe_count -= cnt;
            res = 1;
        }
    } kmutex_unlock(&frame_mutex);
    return res;
}
