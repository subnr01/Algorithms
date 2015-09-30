/** @file conswi.h
 *  @author Hongchao Deng (hongchad)
 */
#ifndef _CONSWI_H
#define _CONSWI_H

#include <stdint.h>

/** @brief swtich cpu state from previous thread to the next thread.
 *
 *  This function will push all general registers on current thread's
 *  kernel stack and save the stack address (%esp) to the first
 *  parameter.
 *
 *  Then the %esp will point to the next thread's previous stack address
 *  in kernel, which is the second parameter, and restore the previous
 *  states (technically general registers).
 *
 *  @return Void.
 */
void switch_cpustate(uintptr_t *prev_esp, uintptr_t next_esp);

/** @brief the switch cpu state return place for a newly forked child.
 *
 *  Since we need to prepare the stack for forked child to make it act
 *  like it's been previously context switched out, we need a flow
 *  branch for this special functionality requirement.
 *
 *  Technically, all the forked child need to do when getting out of
 *  context switch is to enable interrupts and goes back to another
 *  forked place which returns 0.
 *
 *  @return Void.
 */
void _fork_switchret();


#endif // for #ifndef _CONSWI_H
