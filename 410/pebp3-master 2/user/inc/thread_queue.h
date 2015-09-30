/** @file thread_queue.h
 *  @brief Internal thread queue library declaration.
 *
 *  The queue is implemented using linked list.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */

#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H

#include <_linked_list.h> /* Linked list implementation library */
#include <stddef.h>
#include <thr_constants.h>


/* queue structure which is a specific use for our thread library */
typedef struct _q_node {
    /* linked list */
    struct _q_node * next;
    struct _q_node * prev;

    /* data slot */
    int slot;
} q_node ;

/**************** functions declarations ***************/
int q_init(q_node *head);
q_node *q_pop(q_node *head);
void q_push(q_node *, q_node *);

int q_empty(q_node *head);
q_node *q_find(q_node *head, int tid);
q_node *q_remove(q_node *head, int tid);
int q_count(q_node *head);

int q_norunthread(q_node *head);
void q_set_runthread(q_node *head, int tid);
int  q_get_runthread(q_node *head);
void q_unset_runthread(q_node *head);


#endif /* THREAD_QUEUE_H */

