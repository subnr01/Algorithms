/* @file usermode.h
 *
 * @author Hongchao Deng (hongchad)
 * @author Alan Keith (arkeith)
 */
#ifndef _USERMODE_H
#define _USERMODE_H

/** @brief Switch to user mode and run user program from entry point
 *
 *  @param entry The entry point of user program, passed in from loader
 *  @param stack The starting location of the user programs stack
 *  @return Void.
 */
void run_user(int entry, int stack);

#endif // for #ifndef _USERMODE_H
