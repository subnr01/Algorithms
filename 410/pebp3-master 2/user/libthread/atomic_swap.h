/** @file atomic_swap.h
 *  @brief function prototype for atomic_swap.S
 *
 * NOTE: We are assuming uintptr_t is 4 bytes, if this changes
 * we need to update atomic_swap.S
 */

#ifndef ATOMIC_SWAP_H
#define ATOMIC_SWAP_H
#include <stdint.h>

/** @brief atomically exchange value with the number stored in lock address
 */
int atomic_swap(uintptr_t lockaddr, int value);

#endif /* ATOMIC_SWAP_H */
