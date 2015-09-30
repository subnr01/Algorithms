/** @file frame_alloc.c
 *  @brief This is an extended frame allocator module for ZFOD and
 *  reserved allocation.
 *
 *  """ NOTE
 *  In the new architecture, we do reservation first and allocation
 *  second. This makes the entire memory code cleaner. When doing
 *  allocation, one has already reserved as many frames as he needs.
 *  So during allocation we don't need to decrement the frame count.
 *  We only do it in try_reserve function.
 *
 *  The crux of the idea is that reserving a frame is the same as
 *  decrementing the free frame count but not actually changing 
 *  the free frame list. Thus, reservation allows us remove a frame
 *  from the list at a later time.
 *  """
 *
 *  """ Frame allocation operation details
 *  The free frames are managed by a linked list structure. And There's
 *  a special address mapped to the head of the list.
 *
 *  The module provides two main functions: allocation and recycle
 *  frames.
 *
 *  In allocation, we first get the physical address of that special
 *  page, and save it as return value. Then, we map the special page to
 *  the physical address of next free frame in the list.
 *
 *  Similarly, the recycle process mainly consists of three steps:
 *  1. get the physical address of special page.
 *  2. map the special page to the recycled free frames.
 *  3. set a field in current page, the new recycled free frame to point
 *  back to the previous physical address.
 *
 *  """ Concurrency and solution
 *  The frame allocator is shared by all processes and all threads. We
 *  use a kernel mutex to protect it. Only one thread (thus one process)
 *  could get access to the frame allocator at one time.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs
 */
#include <pmm.h>
#include "_pmm.h"
#include <klock.h>
#include "page_allocator.h"
#include "_page_allocator.h"
#include <page.h>
#include <vmm.h>
#include <stdint.h>
#include <assert.h>

#define KERNLOG_L5_ON
#include <kernlog.h>

/** @brief reserve one frame and return zfod frame
 *
 *  This function isn't useful at all. I changed my architecture to use
 *  the model of reservation first and allocation second. And this file
 *  is still kept to remain compatible with old page allocator modules.
 *
 *  @return frame physical address on success.
 *          0 on failure.
 */
uintptr_t
zfod_alloc_frame()
{
    kmutex_lock(&frame_mutex);{

        if( ! freeframe_count ){
            kmutex_unlock(&frame_mutex);
            return PMM_NULL;
        }
        // reserve a frame
        freeframe_count --;

    }
    kmutex_unlock(&frame_mutex);

    // returning the zfod frame
    return zfodframe;
}

/** @brief allocate frame for zfod page fault handler
 *  @return Physical address of free frame
 */
uintptr_t
zfodfault_allocframe()
{
    uintptr_t freeframe_paddr;

    kmutex_lock(&frame_mutex);{

        //get_physical_addr will not fail here, alloc_freeframe in kernel,
        //so page table is always present
        freeframe_paddr = get_physical_addr(alloc_freeframe);

        assert(freeframe_paddr != 0);
        assert( GET_LIST_PREV(alloc_freeframe) % PAGE_SIZE == 0);

        // map the freeframe head to the next one in list.
        assert( VMM_SUCCESS ==
          mapper(alloc_freeframe,
              GET_LIST_PREV(alloc_freeframe), VMM_DEFAULT_FLAG) );
    } kmutex_unlock(&frame_mutex);
    return freeframe_paddr;
}

/** @brief recycle a free frame "logically".
 *
 *  @return Void.
 */
void
zfod_free_frame()
{
    kmutex_lock(& frame_mutex); {
        freeframe_count ++;
    } kmutex_unlock(& frame_mutex);
}

/** @brief recycle a free frame
 *
 *  @param paddr The physical address of free frame
 *  @return Void.
 */
void
exec_freeandreserve(uintptr_t paddr)
{
    // just don't increment the freeframe_count
    uintptr_t prev_addr;

    assert(paddr % PAGE_SIZE == 0);
    assert(paddr != 0);

    if(paddr == zfodframe)
        return;

    kmutex_lock(&frame_mutex);{
        //get_physical_addr will not fail here, alloc_freeframe in kernel,
        //so page table is always present
        prev_addr = get_physical_addr(alloc_freeframe);

        assert(prev_addr != 0);

        assert( VMM_SUCCESS ==
          mapper(alloc_freeframe, paddr, VMM_DEFAULT_FLAG) );

        // set the list prev field to previous head.
        GET_LIST_PREV(alloc_freeframe) = prev_addr;
    }
    kmutex_unlock(&frame_mutex);
}

/** @brief recycle a free frame
 *
 *  @param paddr The physical address of free frame
 *  @return physical frame address
 */
uintptr_t
exec_alloc_reserved_frame()
{
    // just don't decrement the freeframe_count
    uintptr_t freeframe_paddr;

    kmutex_lock(&frame_mutex);{
        //get_physical_addr will not fail here, alloc_freeframe in kernel,
        //so page table is always present
        freeframe_paddr = get_physical_addr(alloc_freeframe);

        assert(freeframe_paddr != 0);
        assert( GET_LIST_PREV(alloc_freeframe) % PAGE_SIZE == 0);

        // map the freeframe head to the next one in list.
        assert( VMM_SUCCESS ==
          mapper(alloc_freeframe,
              GET_LIST_PREV(alloc_freeframe), VMM_DEFAULT_FLAG) );

    } kmutex_unlock(&frame_mutex);

    return freeframe_paddr;
}
