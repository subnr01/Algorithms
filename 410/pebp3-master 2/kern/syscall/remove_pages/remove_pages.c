/** @file remove_pages.c
 *  @brief remove_pages syscall internal handler implementation file
 *
 *  """DESIGN"""
 *  There are two main things in new_pages handler:
 *  1. check memory region
 *    Before we start removing any eage we need to check whether all pages
 *    in the region is present, user permission, and with the starting
 *    base page marked. If not, syscall should fail.
 *  2. removing pages
 *    We free every page when traversing from the start page to end page.
 *    if it's the last page in this page table, we will also free it.
 *
 *  Notice that the removing stage could probably leave a page table
 *  empty (not pages allocated inside). However, it will be reused later
 *  if anyone wanna allocate pages inside or recycled when the process
 *  die.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "remove_pages.h"
#include <stdint.h>
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

#define KERNLOG_L1_ON
#include <kernlog.h>


/** @brief new pages handler
 *  @return 0 on success.
 *          -1 if arguments are wrong (i.e. not page aligned).
 *          -2 if any pages is not present, not user permission. Or the
 *          starting base is not marked as start.
 */
int
remove_pages_handler(uintptr_t base)
{
    page_lock();

    uintptr_t addr, end;
    int dir_i;
    vmm_flag_t dir_flag;
    int page_i;
    int flag;
    int new_dir;
    int invalid;
    uintptr_t phys_addr;

    vmm_table *ptb = (vmm_table *) VMM_GET_FORK_OLDPAGE();
    vmm_table *dir = (vmm_table *) VMM_GET_DIR();


    if( ! TEST_PAGE_ALIGNED(base) ||
      base < USER_MEM_START ||
      base >= MAX_VM_ADDR ){
        page_unlock();
        return -1;
    }

    // checking whether any address is invalid
    new_dir = 1;
    invalid = 0;
    end = base;
    for(addr = base; addr < MAX_VM_ADDR; addr += PAGE_SIZE) {

        if(VMM_PTABLE_INDEX(addr) == 0){
            new_dir = 1;
        }

        if(new_dir){
            new_dir = 0;

            dir_i = VMM_DIR_INDEX(addr);
            dir_flag = VMM_GET_ENTRY_FLAG(&dir->array[dir_i]);
            phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);

            if(!VMM_TEST_PRESENT(dir_flag) ){
                invalid = 1;
                break;
            }

            // map remmaper page to page table
            assert(VMM_SUCCESS == mapper(VMM_GET_FORK_OLDPAGE(), phys_addr, VMM_DEFAULT_FLAG));
        }

        // check page table entry
        page_i = VMM_PTABLE_INDEX(addr);
        flag = VMM_GET_ENTRY_FLAG(&ptb->array[page_i]);

        // Two basic requirement for each page:
        // 1. present, user permission.
        // 2. Being marked for the starting base page
        if(! VMM_TEST_PRESENT(flag) ||
          ! (flag & VMM_FLAG_USER(0)) ||
          (addr == base && !TEST_PAGE_START(flag))
          ){
            invalid = 1;
            break;
        }

        if(TEST_PAGE_END(flag)) {
            end = addr + PAGE_SIZE;
            break;
        }

    }

    assert(addr < MAX_VM_ADDR);
    assert(end != base);

    if(invalid){
        page_unlock();
        return -2;
    }

    // free them!
    new_dir = 1;
    for(addr = base; addr < end; addr += PAGE_SIZE) {

        if(VMM_PTABLE_INDEX(addr) == 0){
            new_dir = 1;
        }

        if(new_dir){
            new_dir = 0;

            dir_i = VMM_DIR_INDEX(addr);
            phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);

            // map remmaper page to page table
            assert(VMM_SUCCESS == mapper(VMM_GET_FORK_OLDPAGE(), phys_addr, VMM_DEFAULT_FLAG));
        }

        kernlog(5, "remove pages: addr: %08x",addr);

        page_i = VMM_PTABLE_INDEX(addr);

        /* free pages */{
            phys_addr = VMM_GET_ENTRY_NOFLAG(&ptb->array[page_i]);
            ptb->array[page_i] = 0;
            invl_tlb(addr);
            pmm_free_frame(phys_addr);
        }

        /* free page table */
        if(page_i == VMM_TABLE_SIZE - 1){
            dir_i = VMM_DIR_INDEX(addr);
            phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);
            dir->array[dir_i] = 0;
            invl_tlb(addr);
            pmm_free_frame(phys_addr);
        }
    }

    kernlog(5, "after remove pages: freeframe: %d", res_count_freeframe());

    page_unlock();
    return 0;
}

void
remove_pages_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(REMOVE_PAGES_INT);

    funcaddr = (uintptr_t) ( &remove_pages_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}


