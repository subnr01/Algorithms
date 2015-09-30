/** @file zfod.c
 *  @brief This is the zfod page fault handler which will allocate a
 *  real frame for any page causing fault.
 *  @author Hongchao Deng (hongchad)
 */
#include <vmm.h>
#include <pmm.h>
#include <assert.h>
#include <string.h>
#include <ureg.h>
#include <klock.h>
#include <pcb.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/*  @brief This is the zfod page fault handler which will allocate a
 *  real frame for any page causing fault.
 *
 *  When designing the zfod handler, I consider a race like this:
 *  Two threads could cause the same page to fault and get a real frame
 *  to that page. While locking one from another on doing the zfod
 *  allocation, we need to check whether the page has been allocated in
 *  a place after acquiring the mutex and before allocating real frame.
 *
 *  @return Void.
 */
void zfod_pagefault(ureg_t * context)
{
    pcb_t *pcb = get_cur_pcb();
    uintptr_t phys_addr;

    // two threads could have zfod fault on the same page. we need to
    // protect vm from such race condition.
    //
    // We don't need this mutex anymore since we have locked entire
    // virtual memory outside in page fault handler
    //kmutex_lock( & pcb->pf_mutex);{

        vmm_flag_t flags = vmm_getflags(context->cr2);
        kernlog(5, "zfod fault: addr: %08x, flag: %08x", context->cr2, flags);

        // check whether someone else has mapped it already.
        if( flags & VMM_FLAG_READWRITE(0)){
            kmutex_unlock( & pcb->pf_mutex);
            return;
        }

        assert( (flags & VMM_FLAG_PRESENT(0)) );
        assert( (flags & VMM_FLAG_USER(0)) );

        phys_addr = zfodfault_allocframe();
        assert(phys_addr != 0);

        assert(VMM_SUCCESS ==
          mapper(context->cr2, phys_addr, VMM_FLAG_READWRITE(flags)) );

        memset((void *)(context->cr2 & (~(PAGE_SIZE-1))), 0, PAGE_SIZE);

    //} kmutex_unlock( & pcb->pf_mutex);
}


