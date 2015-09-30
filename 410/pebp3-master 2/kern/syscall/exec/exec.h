/** @file exec.h
 *  @brief The exec syscall kernel handler
 *
 *  This is exec syscall kernel handler header file.
 *
 *  @author Hongchao Deng (hongchad)
 *  @bug now known bugs.
 */
#ifndef _EXEC_H
#define _EXEC_H

#include <stdint.h>

void exec_wrapper();
int exec_handler(uintptr_t args);

#endif // for #ifndef _EXEC_H
