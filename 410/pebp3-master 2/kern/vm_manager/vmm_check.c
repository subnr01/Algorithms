/** @file vmm_check.c
 *  @brief address check module implementation file
 *
 *  The entire checking is based on a central function called vmm_check.
 *  The vmm_check will check the validity of the address. This will
 *  check the page directory, and then the page table to ensure the
 *  validity of the page where the address resides in. Naturally, the
 *  checking will ensure only validity of one byte. So I am implementing
 *  some extensions to provide easier checking modules.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs
 */
#include <common_macro.h>
#include <stdint.h>
#include "page_allocator.h"
#include "_page_allocator.h"
#include <vmm.h>
#include <pmm.h>
#include <common_macro.h>
#include <stddef.h>
#include <asm.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief check whether that address has permission of user, present,
 *  and conditionally writable.
 *
 *  @param addr the address to check
 *  @param writable whether or not to check writeable permission
 *
 *  @return 0 on success. Negative integer on failure.
 */
int vmm_check(uintptr_t addr, int writable)
{
    int dir_i;
    int page_i;
    vmm_flag_t flag;
    uintptr_t phys_addr;

    vmm_table *dir = (vmm_table *) VMM_GET_DIR();
    vmm_table *ptb = (vmm_table *) VMM_REMAPPER_PAGE;

    dir_i = VMM_DIR_INDEX(addr);
    flag = VMM_GET_ENTRY_FLAG(&dir->array[dir_i]);

    if(! VMM_TEST_PRESENT(flag) ||
      ! (flag & VMM_FLAG_USER(0))){
        return -1;
    }

    phys_addr = VMM_GET_ENTRY_NOFLAG(&dir->array[dir_i]);
    // map remmaper page to page table
    assert(VMM_SUCCESS ==
      mapper(VMM_REMAPPER_PAGE, phys_addr, VMM_DEFAULT_FLAG));

    page_i = VMM_PTABLE_INDEX(addr);
    flag = VMM_GET_ENTRY_FLAG(&ptb->array[page_i]);

    if(! VMM_TEST_PRESENT(flag) ||
      ! (flag & VMM_FLAG_USER(0))){
        return -1;
    }

    if(writable &&
      ! (flag & VMM_FLAG_READWRITE(0)) ){
        return -2;
    }

    return 0;
}


/** @brief The previous vmm_check function could only ensure validity of
 *  one byte on specific address. For most data types, such as int, void
 *  *, they are four bytes in x86-32 architecture.
 *
 *  The entire four bytes could either be within the same page size or
 *  cross boundary of two different pages. In the second case, we need
 *  to check both pages has the right permission.
 *
 *  Nonetheless, checking in both cases could be done by checking the
 *  first byte and the last byte (fourth) for specific address.
 *
 *  @param addr the address to check
 *  @param whether to check writeable permissions
 *
 *  @return 0 on success. Negative integer on failure.
 */
int check_fourbyte(uintptr_t addr, int writable)
{
    if(vmm_check(addr, writable) < 0)
        return -1;

    if(vmm_check( addr + FOUR_BYTE - 1, writable ) < 0)
        return -1;

    return 0;
}

int check_addrbyte(uintptr_t addr, int writable){
    return check_fourbyte(addr, writable);
}

/** @brief check whether every single byte in that string is in valid
 *  address until a NULL terminating byte (included)
 *
 *  @param *str 
 *
 *  @return 0 on success. Negative integer on failure.
 */
int check_string(char *str)
{
    while(1){
        if(vmm_check((uintptr_t)str, 0) < 0)
            return -1;
        if( * str == '\0')
            return 0;
        str ++ ;
    }
}

/** @brief The above string checking only checks the readable
 *  permission. Sometimes we need to check whether it's writable as
 *  well because we need to write to user buffers.
 *
 *  @str String buffer
 *  @len Buffer length
 *  @return 0 on success. Negative integer on failure.
 */
int check_string_writable(char *str, int len)
{
    assert(len >= 0);

    int i;
    for(i = 0; i < len ;i ++){
        if(vmm_check((uintptr_t)str, 1) < 0)
            return -1;
        str ++ ;
    }
    return 0;
}



/** @brief check whether string array.
 *  1. check address of each value is in valid address.
 *  2. check each string.
 *  until NULL terminating value.
 *
 *  @return 0 on success. Negative integer on failure.
 */
int check_string_array(char **arr)
{
    char *str;
    while(1){

        if(check_addrbyte((uintptr_t)arr, 0) < 0)
            return -1;

        if(*arr == NULL)
            return 0;

        str = *arr;

        if(check_string(str) < 0)
            return -1;

        arr ++;
    }
}


