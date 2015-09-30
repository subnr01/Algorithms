/** @file vmm_check.h
 *  @brief address check module heade file
 *
 *  @author Hongchao Deng (hongchad)
 */
#ifndef _VMM_CHECK_H
#define _VMM_CHECK_H

#include <stdint.h>

int vmm_check(uintptr_t addr, int writable);
int check_string(char *str);
int check_string_writable(char *str, int len);
int check_string_array(char **arr);
int check_addrbyte(uintptr_t addr, int writable);
int check_fourbyte(uintptr_t addr, int writable);

#endif // for #ifndef _VMM_CHECK_H
