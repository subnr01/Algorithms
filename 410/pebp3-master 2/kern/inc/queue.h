/** @file queue.h
 *  @brief queue module header file
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct _qnode_t{
    struct _qnode_t *next, *prev;
    void *item;
} qnode_t;

typedef struct _queue_t{
    qnode_t head;
    int count;
} queue_t;


void* qnode_getitem(qnode_t *qnode);
void qnode_setitem(qnode_t *qnode, void *item);

void q_init(queue_t *queue);
void q_push(queue_t *queue, qnode_t *node);
void q_insert_front(queue_t *queue, qnode_t *node);
qnode_t *q_pop(queue_t *queue);
qnode_t* q_index(queue_t *queue, int index);
int q_count(queue_t *queue);
int q_empty(queue_t *queue);

int q_rotate(queue_t *queue);

void q_remove(queue_t * queue, qnode_t *qnode);
qnode_t* q_last(queue_t *queue);

qnode_t *q_start(queue_t *queue);
qnode_t *q_end(queue_t *queue);
qnode_t *q_next(qnode_t *qnode);

#endif // for #ifndef _QUEUE_H
