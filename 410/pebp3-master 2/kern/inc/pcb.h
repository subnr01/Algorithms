/** @file pcb.h
 *  @brief process module header file
 *
 *  The process control block has the following main fields:
 *   - pid
 *   - cr3, address of base of page directory table
 *   - pointer to parent pcb
 *   - thread queue
 *   - child process queue
 *   - resources for wait and exit operations
 *   - page mutex
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bug No known bugs.
 */
#ifndef _PCB_H
#define _PCB_H

#include <queue.h>
#include <stdint.h>
#include <klock.h>
#include <_wait.h>

typedef struct _pcb_t {
    int pid;

    struct _pcb_t *parent;

    uintptr_t cr3; // page table

    kmutex_t thr_mutex; // mutex to protect thread queue
    queue_t thr_queue; // thread queue

    queue_t child_queue; // child process queue
    qnode_t child_qnode; // qnode in process child queue

    wait_t wait_item; // This is used for wait and vanish

    kmutex_t pf_mutex;

    kmutex_t page_mutex; // prevent interleaving calls of new_pages and remove_pages

} pcb_t;

pcb_t* create_process(pcb_t *parent, int cr3);

pcb_t *get_cur_pcb();
int get_thr_num(pcb_t *pcb);

void page_lock();
void page_unlock();

#endif // for #ifndef _PCB_H
