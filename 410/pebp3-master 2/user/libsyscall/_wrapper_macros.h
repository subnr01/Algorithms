/** @file _wrapper_macros.h
 * @brief contains assembly macros for modularity
 *
 * Because much of the assembly is going to be duplicated for various system
 * calls, we decided to make this assembly macro.
 */
#ifndef _WRAPPER_MACROS_H
#define _WRAPPER_MACROS_H
#include <syscall_int.h>

#define SYSCALL_1_BYTE_ARG \
    push %esi ;\
    movb 8(%esp), %esi /* move 1 byte arg into esi  */

#define SYSCALL_2_BYTE_ARG \
    push %esi ;\
    movw 8(%esp), %esi /* move 2 byte arg into esi */

#define SYSCALL_4_BYTE_ARG \
    push %esi ;\
    movl 8(%esp), %esi /* move 4 byte arge into esi */

#define SYSCALL_MULTI_ARG \
    push %esi ;\
    leal 8(%esp), %esi /* load address of argument array into esi */

#define SYSCALL_END \
    pop %esi


#endif /* _WRAPPER_MACROS_H */
