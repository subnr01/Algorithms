/** @file _multi_thread.h
 *  @brief Multi threading internal library
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */
#ifndef _MULTI_THREAD_H
#define _MULTI_THREAD_H

#include <stdint.h>

/* main stack low address interface */
#define GET_STACK_LOW_PTR() (main_stack_low)
#define SET_STACK_LOW_PTR(addr) (main_stack_low = (uintptr_t) (addr) )

/* thread stack search base */
#define GET_THRSTACK_SEARCH_BASE() (GET_STACK_LOW_PTR() - 1 * PAGE_SIZE)

/* single/multi thread environment interface */
#define SET_SINGLE_THREAD_ENV() multi_thread_flag = 0;
#define SET_MULTI_THREAD_ENV() multi_thread_flag = 1;
#define MULTI_THREAD_ENV() (multi_thread_flag)
#define SINGLE_THREAD_ENV() (!multi_thread_flag)

// mark the multi_thread environment ( 0:no, 1:yes)
int multi_thread_flag;

// used to record down the low address of main stack
// Also useful for automatic stack growth check
uintptr_t main_stack_low;

#endif /* _MULTI_THREAD_H */
