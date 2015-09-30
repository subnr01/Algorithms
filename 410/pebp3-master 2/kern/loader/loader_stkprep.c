/** @file loader_stkprep.c
 *
 *  This files provides the functionality of preparing the user stack
 *  before the kernel runs user program.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs
 */
#include "_loader.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <common_macro.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


/** @brief Prepares the arguments for the main entry of user program to
 *  run as if the user program is called by another function following
 *  the stack disciplin.
 *
 *  The arguments are copied from the kernel stack to the user stack as
 *  follows:
 *  1. we first copy the strings to the stack.
 *  2. Then we make array of string pointers referring back to the
 *  string we copied in previous step.
 *  More details are documented below in the code.
 *  @param **args arguments array to copy
 *
 *  @return The stack address for the user program to start at.
 */
uintptr_t
prep_userstack(char **argv)
{
    int i, j;
    int argc;
    uintptr_t stack = USER_STACK_ADDR;
    uintptr_t argv_addr;
    uintptr_t crawl_argv;


    for(i = 0; argv[i] != NULL; i ++){
        j = strlen(argv[i]);
        for(; j >=0 ; j --){
            stack -= ONE_BYTE;
            PUT_ONE_BYTE(stack, argv[i][j]);
        }
    }
    // by now the argv have been saved on stack like this:
    //       filename
    //       arg1
    //       arg2
    //       ...
    // by crawling up the stack (using strlen), the char pointer could
    // be stored in right order from the last to the first following the
    // stack discipline.
    crawl_argv = stack;
    argc = i - 1;

    assert(argc >= 0); // This is kernel function, we protect it by outside (i.e. exec)

    // When a variable is crawling up the strings we copied previously,
    // we are pushing pointers to the strings in reverse order (from the
    // last to the first) on the stack which follows discipline.
    // Since argc is passed in, we can ignore NULL end pointer
    for( ; i > 0 ; i--){
        stack -= FOUR_BYTE;
        PUT_FOUR_BYTE(stack, (uint32_t) crawl_argv);
        crawl_argv += strlen((char *)crawl_argv) + 1; // crawl up the argv
    }
    argv_addr = stack;

    /* arguments */{
        //   4. stack_low
        stack -= FOUR_BYTE;
        PUT_FOUR_BYTE(stack, (uint32_t) USER_STACK_ADDR - USER_STACK_SIZE);

        //   3. stack_high
        stack -= FOUR_BYTE;
        PUT_FOUR_BYTE(stack, (uint32_t) USER_STACK_ADDR);


        //   2. argv
        stack -= FOUR_BYTE;
        PUT_FOUR_BYTE(stack, (uint32_t) argv_addr);

        //   1. argc
        stack -= FOUR_BYTE;
        argc += 1; // finally I realized this is not POSIX exec...
        PUT_FOUR_BYTE(stack, (uint32_t) argc);
    }

    assert(stack >= USER_STACK_ADDR - USER_STACK_SIZE + 4); // the argument size is also protected

    // we need to take the return address into account for user stack
    return stack - 4;
}

