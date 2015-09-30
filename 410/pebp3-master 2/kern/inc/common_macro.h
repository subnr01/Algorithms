/** @file common_macro.h
 *  @brief common macros used frequently
 *
 *  @author Hongchao Deng (hongchad)
 */
#ifndef _COMMON_MACRO_H
#define _COMMON_MACRO_H

#include <stdint.h>
#include <page.h>


#define PUT_ADDR_BYTE(addr, val) PUT_FOUR_BYTE(addr, val)
#define GET_ADDR_BYTE(addr) GET_FOUR_BYTE(addr)
#define ADDR_BYTE FOUR_BYTE

#define PUT_FOUR_BYTE(addr, val) (*(uint32_t *)(addr) = (uint32_t)(val))
#define GET_FOUR_BYTE(addr) (*(uint32_t *)(addr))
#define FOUR_BYTE 4

#define PUT_ONE_BYTE(addr, val) (*(uint8_t *)(addr) = (uint8_t)(val))
#define GET_ONE_BYTE(addr) (*(uint8_t *)(addr))
#define ONE_BYTE 1

#define PAGE_ALIGN(addr) \
  ( ( ((uintptr_t)(addr)) >> PAGE_SHIFT) << PAGE_SHIFT)

#define TEST_PAGE_ALIGNED(addr) \
    ( !( ((uintptr_t)(addr)) & (PAGE_SIZE - 1) ) )

// This is used as the top of user virtual memory space.
#define MAX_VM_ADDR 0xc0000000

#endif // for #ifndef _COMMON_MACRO_H
