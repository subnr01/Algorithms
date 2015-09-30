/** @file timer.h
 */
#ifndef _TIMER_H
#define _TIMER_H

#include <timer_defines.h>

// timer cycles between interrupts
#define TIMER_CYCLE (TIMER_RATE / 100)

void timer_wrapper();
void timer_handler();

#endif // for #ifndef _TIMER_H
