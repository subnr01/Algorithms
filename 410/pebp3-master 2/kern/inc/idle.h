/** @file idle.h
 *  @brief idle header file
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @bug No known bugs.
 */
#ifndef _IDLE_H
#define _IDLE_H

#include <tcb.h>

int __idle_tid;

void idle_init();
void get_idle_next();
int I_am_idle(tcb_t *);

#endif // for #ifndef _IDLE_H
