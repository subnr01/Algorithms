/** @file kernstk.h
 *
 *  Each thread has its own kernel stack. It occupies two pages.
 *
 *  """ esp0 and tcb
 *  for each thread, the esp0 points to the starting place of its own
 *  kernel stack, and its own tcb is stored at the bottom of the stack.
 */

#ifndef _KERNSTK_H
#define _KERNSTK_H

#include <page.h>

#define KERNSTK_SIZE (2*PAGE_SIZE)

uintptr_t esp0_to_tcb(uintptr_t esp0);
uintptr_t tcb_to_esp0(uintptr_t tcb);

#endif // for #ifndef _KERNSTK_H
