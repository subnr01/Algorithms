/* @file frame_allocator.c
 * @brief Physical frames allocator implementation
 *
 * We are using a simple linked list stack to keep track of free
 * physical frames, the trick is accessing and manipulating this list
 * when virtual memory has been turned on.
 *
 * This is acheived through alloc_freeframe, which is a pointer
 * to a region of memory reserved in the kernel space. This region
 * of memory is page aligned and is exactly the size of one page size.
 *
 * The next free frame can be obtaining by dereferencing alloc_freeframe 
 * and reading a uintptr_t. To pop a frame off of the list, we manipulate 
 * the virtual memory system. The logical address alloc_freeframe points to
 * is constant, but we change the physical frame that logical address
 * resolves to be the next available freeframe. 
 *
 * We use a locking mechanism to avoid race conditions manipulating this
 * free list.
 *
 * We reserve the last physical frame as our zero fill on demand frame
 *
 * @author Alan Keith (arkeith)
 * @author Hongchao Deng (hongchad)
 * @bugs No known bugs at this time
 */
#include <pmm.h>
#include <common_kern.h>
#include <page.h>
#include <vmm.h>
#include "page_allocator.h"
#include "_page_allocator.h"
#include <klock.h>
#include <assert.h>
#include "_pmm.h"
#include <string.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief This is used in vm initialization function in order to
 *  provide free frames to get vm run.
 *
 *  NOTE: this function assumes that paging has not been turned on,
 *  once it is turned on we need to use the other allocator
 *
 *
 *  @return physical frame address
 */
uintptr_t
pmm_getframe_nopaging()
{
    // before paging is turned on we shouldn't be able to exhaust the available
    // frames, we leave this check in for ease of future expansion
    assert( freeframe_count > 1); // reserve one page for zfod frame.

    free_start += PAGE_SIZE;  //need for transition to paged alocation
    freeframe_count --;

    return (free_start - PAGE_SIZE) ;
}

/** @brief physical memory init function
 *
 *  This will build a linked list structure using four bytes of each
 *  frame. The head of the list will be accessible via the logical address
 *  pointed to by alloc_freeframe. The operation will take O(1)
 *  time for both allocation and free.
 *
 *  @return Void.
 */
void
pmm_init()
{
    //bottom of the kernel is (mostly) direct mapped
    uintptr_t start = USER_MEM_START; 

    //determine how many physical frames can we support
    uintptr_t frame_hi_addr = (uintptr_t)
      (machine_phys_frames() << PAGE_SHIFT); 

    free_start = start;
    freeframe_count = ( (frame_hi_addr - start) >> PAGE_SHIFT );

    kernlog(2, "pmm init. start addr: 0x%08x, high addr: 0x%08x",
      (unsigned)start, (unsigned) frame_hi_addr);
    
    // build the linked list
    // linking every frame above USER_MEM_START to one on top of him
    // The final layout would be something like this:
    //      |         | addr:3
    //      |link to:3| addr:2
    //      |link to:2| addr:1
    //      |link to:1| addr:0
    for(start = USER_MEM_START; start < frame_hi_addr - PAGE_SIZE;
      start += PAGE_SIZE)
    {
        //write the previous frame phsyical address into current frame
        GET_LIST_PREV(start) = start + PAGE_SIZE;
    }

    kmutex_init(&frame_mutex);

    // set the highest frame to be zfod frame
    zfodframe = frame_hi_addr - PAGE_SIZE;
    memset((void *) zfodframe, 0, PAGE_SIZE);
}


/** @brief allocate one free frame from the free frame list
 *  @return the physical address of the given free frame
 */
uintptr_t
pmm_alloc_frame()
{
    kmutex_lock(&frame_mutex);

    uintptr_t freeframe_paddr;

    if( ! freeframe_count ){ //out of frames
        kmutex_unlock(&frame_mutex);
        return PMM_NULL;
    }
    
    //get_physical_addr will not fail here, alloc_freeframe in kernel,
    //so page table is always present
    freeframe_paddr = get_physical_addr(alloc_freeframe);

    assert(freeframe_paddr != 0); 
    assert(FREEFRAME_VADDR % PAGE_SIZE == 0);

    // remap logical address pointed to be alloc_freeframe
    // to use the next free frame in the list
    //mapper will not fail either, as it only fails if 
    //it needs to get a new frame to use as a page table.
    //because the page table for alloc_freeframe is always
    //present we will succeed
    assert( VMM_SUCCESS == mapper(alloc_freeframe,
          GET_LIST_PREV(alloc_freeframe), VMM_DEFAULT_FLAG) );

    freeframe_count--;

    kmutex_unlock(&frame_mutex);
    return freeframe_paddr;
}

/** @brief recycle a free frame
 *
 *  @param paddr The physical address of free frame
 *  @return Void.
 *
 *  Some of our frames may actually be zfod frames, we need
 *  to invoke a special handler in those cases
 *
 *  NOTE: we require that paddr be page aligned and nonzero
 */
void
pmm_free_frame(uintptr_t paddr)
{
    uintptr_t prev_addr;

    assert(paddr % PAGE_SIZE == 0);
    assert(paddr != 0);


    if(paddr == zfodframe){
        zfod_free_frame();
    }
    else{ // real allocated frame
        kmutex_lock(&frame_mutex);

        //get_physical_addr will not fail here, alloc_freeframe in kernel,
        //so page table is always present
        prev_addr = get_physical_addr(alloc_freeframe);
        assert(prev_addr != 0);

        // map the freeframe head to the new one.
        // should always succeed
        assert( VMM_SUCCESS ==
          mapper(alloc_freeframe, paddr, VMM_DEFAULT_FLAG) );

        // set the list prev field to previous head.
        // | | 2
        // |2| 1
        //
        // |1| new freed frame
        GET_LIST_PREV(alloc_freeframe) = prev_addr;

        freeframe_count++;


        kmutex_unlock(&frame_mutex);
    }

}

/** @brief For resource manager to determine the number of freeframe
 *
 * @return the number of free frames
 */
int res_count_freeframe()
{
    return freeframe_count;
}
