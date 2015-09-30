#ifndef _WRAPPER_MACRO_H
#define _WRAPPER_MACRO_H

// we are pushing:
// 1. general registers (esp set to 0)
// 2. data segments
// 3. cr2 (also 0. we don't need it)
#define PREP_UREG \
        pusha;\
        movl $0, 12(%esp);\
        push %gs;\
        push %fs;\
        push %es;\
        push %ds;\
        pushl 0

#endif // for #ifndef _WRAPPER_MACRO_H
