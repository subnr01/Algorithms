/** @file autostack_wrapper.h
 *  @brief autostack_wrapper declaration
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */
#ifndef AUTOSTACK_WRAPPER_H
#define AUTOSTACK_WRAPPER_H
#include <ureg.h>

/** @brief the assembly wrapper for automatic stack growth handler */
void handler_wrapper(void *arg, ureg_t *ureg);

#endif /* AUTOSTACK_WRAPPER_H */
