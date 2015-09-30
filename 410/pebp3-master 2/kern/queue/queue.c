/** @file queue.h
 *  @brief queue module implementation file
 *
 *  This is a linked list implemented queue module.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <queue.h>
#include <stddef.h>

#define KERNLOG_L5_ON
#include <kernlog.h>

/** @brief get item from qnode
 *  @param qnode The qnode to get item from
 *  @return The pointer to the item of qnode.
 */
void* qnode_getitem(qnode_t *qnode)
{
    return qnode->item;
}

/** @brief set item in qnode
 *  @param qnode The qnode to set item to
 *  @param item
 *  @return Void.
 */
void qnode_setitem(qnode_t *qnode, void *item)
{
    qnode->item = item;
}

/** @brief queue initialization
 *  @param queue
 *  @return Void.
 */
void
q_init(queue_t *queue)
{
    qnode_t *head = & (queue->head);

    head->next = head;
    head->prev = head;

    queue->count = 0;
}

/** @brief push the node to the last place of the queue
 *  @param queue
 *  @param node
 *  @return Void.
 */
void
q_push(queue_t *queue, qnode_t *node)
{
    qnode_t *head = & (queue->head);
    qnode_t *last = head->prev;

    last->next = node;
    node->prev = last;
    node->next = head;
    head->prev = node;

    queue->count ++;
}

/** @brief insert the node to the front (first place) of the queue.
 *  @param queue
 *  @param node
 *  @return Void.
 */
void q_insert_front(queue_t *queue, qnode_t *node)
{
    qnode_t *head = & (queue->head);
    qnode_t *first = head->next;

    head->next = node;
    node->prev = head;

    first->prev = node;
    node->next = first;

    queue->count ++;
}

/** @brief insert the node to the front (first place) of the queue.
 *  @param queue
 *  @param node
 *  @return Void.
 */
qnode_t *
q_pop(queue_t *queue)
{
    qnode_t *head = & (queue->head);
    qnode_t *res;

    if(queue->count == 0)
        return NULL;
    queue->count--;

    res = head->next;
    head->next = res->next;
    res->next->prev = head;

    return res;
}

/** @brief similar function to queue[index]
 *  @param queue
 *  @param index
 *  @return qnode at index. NULL if index exceeds the range.
 */
qnode_t *
q_index(queue_t *queue, int index)
{
    qnode_t *head = & (queue->head);
    int i;

    if(index < 0 || index >= queue->count){
        return NULL;
    }

    for(i = 0;i < index + 1; i++) {
        head = head->next;
    }
    return head;
}

/** @brief number of nodes in the queue.
 *  @param queue
 *  @return number of nodes.
 */
int
q_count(queue_t *queue)
{
    return queue->count;
}

/** @brief Testing whether the queue is empty
 *  @param queue
 *  @return 1 if empty. 0 if not.
 */
int
q_empty(queue_t *queue)
{
    return (queue->count == 0);
}

/** @brief Testing whether the queue is empty
 *  @param queue
 *  @return 1 if empty. 0 if not.
 */
int
q_rotate(queue_t *queue)
{
    if(queue->count <= 1) return 0;

    q_push(queue, q_pop(queue));
    return 1;
}

/** @brief Remove qnode from queue
 *  @param queue
 *  @param qnode
 *  @return Void.
 */
void q_remove(queue_t * queue, qnode_t *qnode)
{
    qnode_t *prev = qnode->prev;
    qnode_t *next = qnode->next;

    prev->next = next;
    next->prev = prev;

    queue->count --;
}

/** @brief get last qnode in queue
 *  @param queue
 *  @return Last qnode
 */
qnode_t *
q_last(queue_t *queue)
{
    qnode_t *head = & (queue->head);
    return head->prev;
}

/** @brief get first qnode in queue
 *  @param queue
 *  @return first qnode
 */
qnode_t *
q_start(queue_t *queue)
{
    qnode_t *head = & (queue->head);
    return head->next;
}

/** @brief get next qnode by current qnode
 *  @param qnode
 *  @return next qnode
 */
qnode_t *
q_next(qnode_t *qnode)
{
    return qnode->next;
}

/** @brief get end qnode in queue.
 *  @param queue
 *  @return end qnode
 */
qnode_t *
q_end(queue_t *queue)
{
    return ( & (queue->head) );
}
