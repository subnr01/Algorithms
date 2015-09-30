/** @file binheap.h
 *  @brief binheap module header file
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @bug No known bugs.
 */
#ifndef _BINHEAP_H
#define _BINHEAP_H

#include <queue.h>

typedef struct _heapnode_t {
    struct _heapnode_t *parent;
    struct _heapnode_t *child1;
    struct _heapnode_t *child2;

    qnode_t qnode;

    void *item;
} heapnode_t;

typedef struct _binheap_t{
    queue_t queue;
} binheap_t;

typedef int (*cmp_func_t)(void *, void *);


void bh_init(binheap_t *bh);
heapnode_t* make_heapnode(void *item);

void bh_push(binheap_t *bh, heapnode_t *hn, cmp_func_t cmp);
void* bh_pop(binheap_t *bh, cmp_func_t cmp);
void* bh_firstitem(binheap_t *bh);

#endif // for #ifndef _BINHEAP_H
