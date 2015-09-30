/** @file sleep.c
 *  @brief sleep module implementation file
 *
 *  The sleep module mainly consists of a sleep queue. The queue is a
 *  priority queue, which always keeps the minimum item in the top. This
 *  property will make checking on whether someone should be woken up
 *  easier. And maintaining the queue consumes O(lg N) time.
 *
 *  In order to make sleep queue scalable with the thread number, I
 *  implement it using a linked list. Basically it's still a priority
 *  queue (binary heap).
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <sleep_lib.h>
#include <binheap.h>
#include <tcb.h>
#include <getticks.h>
#include <stddef.h>
#include <malloc.h>
#include <malloc_internal.h>
#include <asm.h>
#include <limits.h>
#include <cpu.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

static sleep_t sleep;
static cmp_func_t cmp;


/** @brief compare function for sleep item
 *  @param hn1 first item
 *  @param hn2 second item
 *  @return -1 if first item is smaller than second.
 *          0 if equal.
 *          1 if larger
 */
static int
cmp_func(void *si1, void *si2)
{
    long long res =
          ( (sleepitem_t *)(si1) )->time
        - ( (sleepitem_t *)(si2) )->time;
    if(res < 0) return -1;
    if(res == 0) return 0;
    return 1;
}

/** @brief sleep module init function
 *  @return Void.
 */
void sleep_init()
{
    bh_init( & sleep.bh);
    cmp = & cmp_func;
}

/** @brief add new sleep item
 *
 *  @param tcb The thread doing sleep
 *  @param ticks The tick count the thread will sleep for
 *  @return 0 on success. negative integer on failure.
 */
int sleep_add(tcb_t *tcb, int ticks)
{
    heapnode_t *hn;
    sleepitem_t *slitem;

    kernlog(5, "sleep add!");
    if( (slitem = malloc(sizeof(sleepitem_t))) == NULL){
        return -1;
    }
    slitem->tcb = tcb;
    slitem->time = getticks() + ticks;

    if( ( hn = make_heapnode(slitem)) == NULL){
        free(slitem);
        return -1;
    }

    disable_interrupts(); {
        // timer interrupt isn't expected since the sleep queue would be
        // checked and get items from in it while we're pushing new items in.
        // I could use a spin yield lock but that will leak more tick
        // counts.
        bh_push( & sleep.bh, hn, cmp);

        block_thr(tcb);
    } cpu_relax();

    kernlog(5, "finished sleep add!");

    return 0;
}

/** @brief pop sleep item
 *
 *  @return tcb of minimum sleep time thread on success. NULL on failure.
 */
tcb_t* sleep_pop()
{
    // interrupts are disabled
    tcb_t *tcb;
    sleepitem_t *slitem;

    kernlog(5, "sleep pop!");
    slitem = bh_pop(&sleep.bh, cmp);
    if(slitem == NULL)
        return NULL;

    tcb = slitem->tcb;

    _free(slitem);
    kernlog(5, "finished sleep pop!");

    return tcb;
}

/** @brief get minimum time in sleep queue
 *
 *  @return the minimum time in sleep queue.
 */
long long sleep_mintime()
{
    // interrupts are disabled
    sleepitem_t *item = bh_firstitem(&sleep.bh);
    if(item == NULL)
        return LLONG_MAX;
    return item->time;
}


