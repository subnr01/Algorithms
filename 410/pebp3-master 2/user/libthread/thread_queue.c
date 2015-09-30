/** @file thread_queue.c
 *  @brief Internal thread queue library implementation.
 */


#include <thread_queue.h>

int
q_init(q_node *head)
{
    if(head == NULL)
        return -1;
    LL_INIT(head);
    q_unset_runthread(head);
    return 0;
}

q_node *
q_pop(q_node *head)
{
    q_node *front;

    if(LL_EMPTY(head))
        return NULL;

    front = LL_FRONT(head);
    LL_REMOVE_FRONT(head);
    return front;
}

void
q_push(q_node *head, q_node *node)
{
    LL_INSERT_END(head, node);
}

int
q_empty(q_node *head)
{
    return LL_EMPTY(head);
}

q_node *
q_find(q_node *head, int tid)
{
    q_node *iter;
    LL_FOREACH(head, iter) {
        if(iter->slot == tid)
            return iter;
    }
    return NULL;
}

q_node *
q_remove(q_node *head, int tid)
{
    q_node *iter;
    LL_FOREACH(head, iter) {
        if(iter->slot == tid){
            LL_REMOVE_NODE(iter);
            return iter;
        }
    }
    return NULL;
}

int
q_count(q_node *head)
{
    int count = 0;
    q_node *iter;
    LL_FOREACH(head, iter) {
        count ++;
    }
    return count;
}

int q_norunthread(q_node *head)
{
    return (head->slot == THR_NULL);
}

void
q_set_runthread(q_node *head, int tid)
{
    head->slot = tid;
}

int
q_get_runthread(q_node *head)
{
    return head->slot;
}

void
q_unset_runthread(q_node *head)
{
    head->slot = THR_NULL;
}
