/** @file new_pages.c
 *  @brief new_pages syscall internal handler implementation file
 *
 *  """NOTE"""
 *  This syscall looks like a lot of code. Technically most of the code
 *  are repeated in a lot of places (not limited in this module). I
 *  should encapsulate them later.
 *
 *  """DESIGN"""
 *  There are two main things in new_pages handler:
 *  1. check memory region
 *    Before we start allocating pages we need to check whether any page
 *    of the region is present. If so, the syscall should fail.
 *  2. allocate pages
 *    We calculate how many pages we need first (alongside with checking).
 *    Then we will try to reserve that number of frames. After it, that
 *    region will be allocated with all zfod pages. One thing to do at
 *    last is that we will mark the start and the end for that region.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 */
#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "new_pages.h"
#include <common_macro.h>
#include <page.h>
#include <vmm.h>
#include "../../vm_manager/_page_allocator.h"
#include "../../vm_manager/page_allocator.h"
#include <pmm.h>
#include <pcb.h>
#include <vmm_loader.h>
#include <common_kern.h>
#include <page_manager.h>
#include <res_manage.h>
#include <vmm_check.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


/** @brief new pages handler
 *  @return 0 on success.
 *          -1 if arguments are wrong (i.e. not page aligned).
 *          -2 if any pages is present.
 *          -3 if we don't have enough frames.
 */
int
new_pages_handler(uintptr_t args)
{
    page_lock();

    int len;
    uintptr_t addr, base;
    int dir_i;
    vmm_flag_t dir_flag;
    int page_i;
    int flag;
    int new_dir;
    int invalid;
    int ptb_count;
    uintptr_t phys_addr;

    vmm_table *ptb = (vmm_table *) VMM_GET_FORK_OLDPAGE();
    vmm_table *dir = (vmm_table *) VMM_GET_DIR();

    /* base */ {
        if(check_addrbyte(args, 0) < 0)
            return -1;
        base = (uintptr_t) GET_ADDR_BYTE(args);
    }
    /* len */ {
        args += ADDR_BYTE;
        if(check_fourbyte(args, 0) < 0)
            return -1;
        len = (int) GET_FOUR_BYTE(args);
        if(len < 0) return -1;
        if(len == 0) return 0;
    }
    //verify alignment
    if( ! TEST_PAGE_ALIGNED(base) ||
      ! TEST_PAGE_ALIGNED(len) ||
      len & 0x80000000 || // negative number
      base < USER_MEM_START ||
      base + len < base || //overflow check
      base + len >= MAX_VM_ADDR ||
      len == 0 ){
        page_unlock();
        return -1;
    }

    // two jobs in following loop:
    // 1. any address already existed, which is invalid.
    // 2. count how many pages we need (including new page tables).
    new_dir = 1;
    invalid = 0;
    ptb_count = 0;
    for(addr = base; addr < base + len; addr += PAGE_SIZE) {

        if(VMM_PTABLE_INDEX(addr) == 0){
            new_dir = 1;
        }

        if(new_dir){
            new_dir = 0;

            dir_i = VMM_DIR_INDEX(addr);
            dir_flag = VMM_GET_ENTRY_FLAG(&dir->array[dir_i]);
            phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);

            if(!VMM_TEST_PRESENT(dir_flag) ){
                uintptr_t temp_addr = VMM_DIR_NEXTI(dir_i);
                addr = temp_addr - PAGE_SIZE;
                ptb_count ++ ;
                continue;
            }

            // map remmaper page to page table
            assert(VMM_SUCCESS == mapper(VMM_GET_FORK_OLDPAGE(), phys_addr, VMM_DEFAULT_FLAG));
        }

        // check page table entry
        page_i = VMM_PTABLE_INDEX(addr);
        flag = VMM_GET_ENTRY_FLAG(&ptb->array[page_i]);

        if(VMM_TEST_PRESENT(flag)){
            kernlog(3, "page already existed! addr: %08x, flag: %08x", addr, flag);
            invalid = 1;
            break;
        }

    }

    if(invalid){
        // pages already exist
        page_unlock();
        return -2;
    }


    if(!try_reserve_frame(ptb_count + len/PAGE_SIZE)){
        // not enough memory
        page_unlock();
        return -3;
    }

    kernlog(5, "reserved %d pages", ptb_count + len/PAGE_SIZE);


    /* allocate new zfod pages */ {
        flag = VMM_CLEAR_FLAG(flag);
        flag = VMM_FLAG_PRESENT(flag);
        flag = VMM_FLAG_USER(flag);

        alloc_zfod(base, len, flag);
    }

    /* mark the start */{
        mapper_lookup_phase(base);
        page_i = VMM_PTABLE_INDEX(base);

        phys_addr = VMM_GET_ENTRY_NOFLAG(&ptb->array[page_i]);
        flag = VMM_GET_ENTRY_FLAG(&ptb->array[page_i]);
        flag = PAGE_MARK_START(flag);
        VMM_SET_ENTRY(&ptb->array[page_i], phys_addr, flag);
        invl_tlb(base);
    }

    /* mark the end */{
        mapper_lookup_phase(base + len - PAGE_SIZE);
        page_i = VMM_PTABLE_INDEX(base + len - PAGE_SIZE);

        phys_addr = VMM_GET_ENTRY_NOFLAG(&ptb->array[page_i]);
        flag = VMM_GET_ENTRY_FLAG(&ptb->array[page_i]);
        flag = PAGE_MARK_END(flag);
        VMM_SET_ENTRY(&ptb->array[page_i], phys_addr, flag);
        invl_tlb(base + len - PAGE_SIZE);
    }

    kernlog(5, "after new pages: freeframe: %d", res_count_freeframe());
    page_unlock();
    return 0;
}

void
new_pages_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(NEW_PAGES_INT);

    funcaddr = (uintptr_t) ( &new_pages_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
