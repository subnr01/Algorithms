/** @file _loader.h
 *
 *  Private header file for loader module
 *
 *  @author Hongchao Deng (hongchad)
 */
#ifndef _LOADER_H
#define _LOADER_H

#include <exec2obj.h>
#include <elf_410.h>
#include <page.h>
#include <common_macro.h>


#define USER_STACK_ADDR MAX_VM_ADDR
#define USER_STACK_SIZE ( 8 * PAGE_SIZE )
#define USER_STACK_PAGE_COUNT 9 // one for page directory

#define PAGEDIR_SIZE (1<<22)


int load_elf_mem(simple_elf_t *simelfp, int index);
void free_entire_vmm(simple_elf_t *simelfp);
uintptr_t prep_userstack(char **argv);

#endif /* _LOADER_H */
