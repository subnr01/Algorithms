/** @file exec.c
 *  @brief The exec syscall kernel handler
 *
 *  This is exec syscall kernel handler implementation. In the exec,
 *  I'm saving all the arguments in the kernel stack because the loader
 *  is going to remove entire virtual memory and construct a new one.
 *  During loading process, the kernel stack is a safe place to save
 *  arguments and then we can be able to restore them back to user space
 *  on user stack. Since the kernel stack is of limited size, the total
 *  size of arguments is also limited to 2K.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug now known bugs.
 */
#include <stdint.h>
#include <stddef.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "exec.h"
#include <loader.h>
#include <vmm.h>
#include <string.h>
#include <common_macro.h>
#include <vmm_check.h>
#include <assert.h>
#include <pcb.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


#define AG_SIZE 2048 // limit the size of argvev to 2 KB.

// reserved space in argv:
// one for the addres of the filename. one for null terminated end.
#define AG_RESERVED 8

/** @brief copy the string from user space *src to kernel stack place *dst.
 *
 *  @param src
 *  @param dst
 *  @return The address of the place next to the end of last string
 *  copied to dst.
 */
static uintptr_t
cp_string(char *src, char *dst)
{
    while( *src != '\0'){
        *dst = *src;
        src ++; dst ++;
    }
    *dst = '\0'; dst ++;
    return (uintptr_t) dst ;
}

/** @brief copy the string from user space *src to kernel stack place *dst.
 *  And also set the entry to the starting place of dst as a value in
 *  string array.
 *
 *  @param src
 *  @param dst
 *  @return The address of the place next to the end of last string
 *  copied to dst.
 */
static uintptr_t
prep_entry(char **entry, char *src, char *dst)
{
    *entry = dst;
    return cp_string(src, dst);
}

/** @brief exec handler
 *
 *  The handler is putting all arguments into the kernel stack and then
 *  pass them to the loader. The loader will then renew the entire
 *  virtual memory other than the kernel space and then allocate the
 *  arguments back to user space on user stack.
 *
 *  The arguments are copied to the kernel stack as followed:
 *  1. the bottom are used to store the string pointers with a NULL
 *  terminated end.
 *  2. Above the pointer array stores the strings from the first to the
 *  last one by one growing up.
 *
 *  @param args Argument starting address
 *  @return 0 on success.
 *          -1 if the arguments are wrong.
 *          -2 if there's not enough space to save arguments in kernel
 *          stack.
 *          -3 if the loading process goes wrong.
 */
int
exec_handler(uintptr_t args) // (char *execname, char **argv)
{
    char *execname;
    char **argv;
    char kern_argv[AG_SIZE]; // reserved 2 KB space in kernel stack

    page_lock();

    /* execname */{
        if(check_addrbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }

        execname = (char *) GET_ADDR_BYTE(args);

        if(check_string(execname) < 0){
            page_unlock();
            return -1;
        }

        assert(execname != NULL );
    }

    /* argument vector */ {
        args += ADDR_BYTE;

        if(check_addrbyte(args, 0) < 0){
            page_unlock();
            return -1;
        }

        argv = (char **) GET_ADDR_BYTE(args);

        if(argv != NULL && check_string_array(argv)){
            page_unlock();
            return -1;
        }
    }

    kernlog(5, "execname: %s", execname);

    // check argvec:
    //   every single byte of argv in two dimensions.

    if( argv == NULL ) {
        if( strlen(execname) + 1 + AG_RESERVED >= AG_SIZE){
            page_unlock();
            return -2;
        }

        // put the execname on the first place of argv vector. and set
        // its value to string place.
        prep_entry((char **)kern_argv, execname, kern_argv + AG_RESERVED);

        // NULL terminated end.
        PUT_ADDR_BYTE(kern_argv + ADDR_BYTE, NULL);
    }
    else {
        int i;
        int argc = 0;
        char **parg = argv;
        uintptr_t growup;

        while( *parg != NULL ){
            argc++;
            parg++;
        }
        if(argc > 0) argc -= 1;

        kernlog(5, "argc: %d", argc);
        if( (argc * ADDR_BYTE + AG_RESERVED) >= AG_SIZE){
            page_unlock();
            return -2;
        }

        growup = (uintptr_t) ( kern_argv + (argc * ADDR_BYTE + AG_RESERVED) );

        if( strlen(execname) + 1 + (growup - (uintptr_t)kern_argv) >= AG_SIZE){
            page_unlock();
            return -2;
        }

        // put the execname as the first argument.
        growup = prep_entry((char **)kern_argv, execname, (char *) growup );

        for(i = 1; i <= argc; i++){
            if( strlen(argv[i]) + 1 + (growup - (uintptr_t)kern_argv) >= AG_SIZE){
                page_unlock();
                return -2;
            }
            growup = prep_entry( (char **) (kern_argv + i * ADDR_BYTE), argv[i],
                                (char *) growup);
        }

        PUT_ADDR_BYTE(kern_argv + ( argc + 1 ) * ADDR_BYTE, NULL);
    }


    page_unlock();

    load_elf( *(char **) kern_argv , (char **) kern_argv);

    return -3;
}


/** @brief syscall installer
 */
void
exec_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(EXEC_INT);

    funcaddr = (uintptr_t) ( &exec_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
