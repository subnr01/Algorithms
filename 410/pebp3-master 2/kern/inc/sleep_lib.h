/** @file sleep_lib.h
 *  @brief sleep module header file
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @bug No known bugs.
 */
#ifndef _SLEEP_LIB_H
#define _SLEEP_LIB_H

#include <tcb.h>
#include <binheap.h>

typedef struct _sleepitem_t{
    long long time;
    tcb_t *tcb;
} sleepitem_t;

typedef struct _sleep_t{
    binheap_t bh;
} sleep_t;

void sleep_init();
int sleep_add(tcb_t *tcb, int ticks);
tcb_t* sleep_pop();
long long sleep_mintime();

#endif // for #ifndef _SLEEP_LIB_H
