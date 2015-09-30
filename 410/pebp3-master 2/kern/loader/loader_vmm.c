/** @file loader_vmm.c
 *
 *  This is main memory loading function for my loader.
 *
 *  The loading process consists of three main steps:
 *  1. check ELF file, and retrieve address for different regions.
 *  2. clear the prevoius user memory, and reserve the memory we need to
 *  successfully load the new program.
 *  3. load the program to relevant regions and memcpy the data from elf
 *  file to it.
 *
 *  In my memory architecture, I reserve the frame first and then
 *  allocate them. This requires we need to know how many pages we need
 *  to load the program beforehand.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs
 */
#include <vmm.h>
#include <exec2obj.h>
#include <elf_410.h>
#include "_loader.h"
#include <string.h>
#include <page.h>
#include <common_kern.h>
#include <common_macro.h>
#include <vmm_loader.h>
#include <assert.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


/** @brief Calculation on difference between how many pages we have and
 *  we will need to load the new program. Based on the calculation, we
 *  will allocate more pages or release some of them.
 *
 *  There's an assumption made here: the readwrite region is right next
 *  to the readonly region. By 'right next', I mean they are on two
 *  adjacent pages. This assumption is checked in loader and any program
 *  that doesn't obey this cannot be successfully loaded.
 *
 *  @return 0 on success. Negative integer on failure.
 */
static int exec_reserve_mem(
  uintptr_t ro_start, uintptr_t ro_end,
  uintptr_t rw_start, uintptr_t rw_end )
{
    int total_old, total_new, extra_count;
    uintptr_t start, end, addr;
    total_old = count_user_pages();
    kernlog(2,"total_old: %d", total_old);

    total_new = 0;


    /* count pages */ {
        start = PAGE_ALIGN(ro_start);
        end = PAGE_ALIGN(ro_end + PAGE_SIZE - 1);
        total_new += (end - start) / PAGE_SIZE;

        start = PAGE_ALIGN(rw_start);
        end = PAGE_ALIGN(rw_end + PAGE_SIZE - 1);
        total_new += (end - start) / PAGE_SIZE;
    }

    /* count page table */{
        start = PAGE_ALIGN(ro_start);
        end = PAGE_ALIGN( rw_end + PAGE_SIZE - 1);
        if( (start & ~(PAGEDIR_SIZE -1)) != 0){
            total_new ++;
            start = ((start & ~(PAGEDIR_SIZE -1)) + PAGEDIR_SIZE);
        }
        addr = start;
        while(addr < end){
            total_new ++;
            addr += PAGEDIR_SIZE;
        }

        if(end > USER_STACK_ADDR - PAGEDIR_SIZE)
            total_new --; // overlapping stack page table
    }

    /* count stack */ {
        total_new += USER_STACK_PAGE_COUNT;
    }

    kernlog(2,"total_new: %d", total_new);

    if(total_new < total_old){
        extra_count = total_old - total_new;
    }
    else{
        extra_count = 0;
        if(total_new > total_old)
            if(!try_reserve_frame(total_new - total_old)){
                // There isn't enough space to load the new executable, even
                // after all space of current one is released.
                return -1;
            }
    }

    reserveclear_usermem(extra_count);

    return 0;
}

/** @brief the main memory loading function.
 *
 *  This function consists of three main steps:
 *  1. check ELF file, and retrieve address for different regions.
 *  2. clear the prevoius user memory, and reserve the memory we need to
 *  successfully load the new program.
 *  3. load the program to relevant regions and memcpy the data from elf
 *  file to it.
 *
 *  @return 0 on success. Negative integer on failure.
 */
int
load_elf_mem(simple_elf_t *simelfp, int index)
{
    /* load the relevant bytes from elf to virtual memory space.
     *
     * 1. The .text and .rodata section are loaded to a region which is
     * readonly
     * 2. The .data and .bss sections are loaded to a region which is
     * readable and writable.
     *
     * The reason behind assigning a region is because the minimum unit of
     * memory permission is page. And two of them share the same page.
     */

    uintptr_t ro_start, ro_end;
    uintptr_t rw_start, rw_end;
    vmm_flag_t page_flag;

    if(simelfp->e_txtstart < USER_MEM_START)
        return -1;
    if(simelfp->e_rodatstart < simelfp->e_txtstart + simelfp->e_txtlen)
        return -1;
    if(simelfp->e_datstart < simelfp->e_rodatstart + simelfp->e_rodatlen)
        return -1;
    if(simelfp->e_bssstart < simelfp->e_datstart + simelfp->e_datlen)
        return -1;

    ro_start = simelfp->e_txtstart;
    ro_end   = simelfp->e_rodatstart + simelfp->e_rodatlen;

    rw_start = simelfp->e_datstart;
    rw_end   = simelfp->e_bssstart + simelfp->e_bsslen;

    if(rw_end <= simelfp->e_bssstart)
        return -1; //overflow
    // no space for stack
    if( rw_end > USER_STACK_ADDR - USER_STACK_SIZE)
        return -1;
    // the end of readonly region is assumed to be adjacent to the next
    // read write region. This should be obeyed by virtual memory
    // discipline.
    // @ref:  http://www.cs.cmu.edu/~410/lectures/L02_Stack.pdf
    //
    // I'm making this assumption because this will make my calculation
    // a lot more easier and cleaner counting contiguous pages.
    if( PAGE_ALIGN( ro_end + PAGE_SIZE - 1) != PAGE_ALIGN(rw_start) )
        return -1;

    // most important thing
    if( exec_reserve_mem(ro_start, ro_end, rw_start, rw_end) < 0)
        return -1;

    /* ro region for .text and .rodata */ {
        page_flag = VMM_CLEAR_FLAG(page_flag);
        page_flag = VMM_FLAG_PRESENT(page_flag);
        page_flag = VMM_FLAG_USER(page_flag);

        alloc_real(ro_start, ro_end - ro_start, page_flag);

        // copy .text
        kernlog(2, "text: %x %x", (unsigned int) simelfp->e_txtstart,
          (unsigned) simelfp->e_txtstart + (unsigned) simelfp->e_txtlen);
        memcpy((void *) simelfp->e_txtstart,
          (char *) exec2obj_userapp_TOC[index].execbytes + simelfp->e_txtoff,
          simelfp->e_txtlen );

        // copy .rodata
        kernlog(2, "rodata: %x %x", (unsigned int) simelfp->e_rodatstart,
          (unsigned) simelfp->e_rodatstart + (unsigned) simelfp->e_rodatlen);
        memcpy((void *) simelfp->e_rodatstart,
          (char *) exec2obj_userapp_TOC[index].execbytes + simelfp->e_rodatoff,
          simelfp->e_rodatlen );
    }

    /* rw region for .data and .bss */ {
        page_flag = VMM_CLEAR_FLAG(page_flag);
        page_flag = VMM_FLAG_PRESENT(page_flag);
        page_flag = VMM_FLAG_READWRITE(page_flag);
        page_flag = VMM_FLAG_USER(page_flag);

        alloc_real(rw_start, rw_end - rw_start, page_flag);

        // copy .data
        kernlog(2, "data: %x %x", (unsigned int) simelfp->e_datstart,
          (unsigned) simelfp->e_datstart + (unsigned) simelfp->e_datlen);
        memcpy((void *) simelfp->e_datstart,
          (char *) exec2obj_userapp_TOC[index].execbytes + simelfp->e_datoff,
          simelfp->e_datlen );

        // the .bss section was already zero-cleared when allocating pages.
        kernlog(2, "bss: %x %x", (unsigned int) simelfp->e_bssstart,
          (unsigned) simelfp->e_bssstart + (unsigned) simelfp->e_bsslen);

    }


    /* set up stack */ {
        // allocate real frame for the first stack
        page_flag = VMM_CLEAR_FLAG(page_flag);
        page_flag = VMM_FLAG_PRESENT(page_flag);
        page_flag = VMM_FLAG_READWRITE(page_flag);
        page_flag = VMM_FLAG_USER(page_flag);

        alloc_real(USER_STACK_ADDR - PAGE_SIZE,
          PAGE_SIZE, page_flag);

        // This allocates zfod pages.
        page_flag = VMM_CLEAR_FLAG(page_flag);
        page_flag = VMM_FLAG_PRESENT(page_flag);
        page_flag = VMM_FLAG_USER(page_flag);

        alloc_zfod(USER_STACK_ADDR - USER_STACK_SIZE, USER_STACK_SIZE - PAGE_SIZE, page_flag);

    }

    return 0;
}

