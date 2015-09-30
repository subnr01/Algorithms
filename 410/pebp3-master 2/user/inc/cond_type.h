/** @file cond_type.h
 *  @brief This file defines the type for condition variables.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */

#ifndef COND_TYPE_H
#define COND_TYPE_H

/** @brief condition variable data structure
 */
typedef struct cond {
    mutex_t internal_lock; //!< internal mutex for synch protection
    q_node queue;  //!< queue for storing waiting thread ids
    q_node *wait_queue; //!< pointer to queue
} cond_t;


#endif /* _COND_TYPE_H */
