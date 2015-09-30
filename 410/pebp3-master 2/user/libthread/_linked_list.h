/** @file Linked_list
 *  @brief Linked_list interface implementation
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */
/* first in first out queue; Linked_list impl. */
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H


/* link the head to itself */
#define LL_INIT(LL_HEAD) \
    (LL_HEAD)->next = (LL_HEAD); \
    (LL_HEAD)->prev = (LL_HEAD);

/* insert the node to the end of list, which is the same as the prev of
 * the head.
 */
#define LL_INSERT_END(LL_HEAD, LL_NODE) \
    ((LL_HEAD)->prev)->next = (LL_NODE); \
    (LL_NODE)->prev = ((LL_HEAD)->prev); \
    (LL_NODE)->next = (LL_HEAD);         \
    (LL_HEAD)->prev = (LL_NODE);

/* remove the node from the front of list */
#define LL_REMOVE_FRONT(LL_HEAD) \
    (LL_HEAD)->next = ((LL_HEAD)->next)->next; \
    ((LL_HEAD)->next)->prev = (LL_HEAD);

/* remove any node from list. Just link it's prev and next to each other
 */
#define LL_REMOVE_NODE(LL_NODE) \
    ((LL_NODE)->next)->prev = (LL_NODE)->prev; \
    ((LL_NODE)->prev)->next = (LL_NODE)->next;


/* return the front of the list. */
#define LL_FRONT(LL_HEAD)  ( (LL_HEAD)->next )

/* check if the list is empty */
#define LL_EMPTY(LL_HEAD)  ( (LL_HEAD)->next == (LL_HEAD) )

/* loop macro of the list */
#define LL_FOREACH(LL_HEAD, ITER) \
    for((ITER) = (LL_HEAD)->next;  \
      (ITER) != (LL_HEAD); (ITER) = (ITER)->next )


#endif /* _LINKED_LIST_H */
