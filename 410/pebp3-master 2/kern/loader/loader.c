/** @file loader.c
 *
 *  @brief The loader architecture contains three main things: loading memory,
 *  setting up user stack, and running program as user.
 *
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bugs No known bugs
 */

/* --- Includes --- */
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <exec2obj.h>
#include <elf_410.h>
#include <vmm.h>

#include <loader.h>
#include <usermode.h>

#include "_loader.h"

#define KERNLOG_L1_ON
#include <kernlog.h>

/**@brief Copies data from a file into a buffer.
 *
 * This function looks into the provided exec-object array and finds out
 * the specific file as with the filename.
 *
 * It will try to copy as many bytes as possible, if there isn't enough
 * bytes to copy.
 *
 * @param filename   the name of the file to copy data from
 * @param offset     the location in the file to begin copying from
 * @param size       the number of bytes to be copied
 * @param buf        the buffer to copy the data into
 *
 * @return returns the number of bytes copied on succes; -1 on failure
 */
int getbytes( const char *filename, int offset, int size, char *buf )
{
    int index;
    int num;

    if(size < 0 || offset < 0)
        return -1;

    if(size == 0) return 0;

    // search the file
    for (index = 0; index < exec2obj_userapp_count; index++) {
        if(strcmp(filename, exec2obj_userapp_TOC[index].execname)
          == 0){
            break;
        }
    }

    if(index == exec2obj_userapp_count) // didn't find it
    {
        kernlog(1, "getbytes: didn't find it '%s'", filename);
        return -1;
    }

    num = (exec2obj_userapp_TOC[index].execlen >= offset + size)? size:
            exec2obj_userapp_TOC[index].execlen - offset;

    memcpy(buf,
      (char *) exec2obj_userapp_TOC[index].execbytes + offset,
      num);

    return num;
}


/** @brief main loader function
 *  This function depicts the main flow of what loader does: finding the
 *  executable, load the memory, prepare user stack, and run user
 *  program.
 *
 *  @param filename
 *  @param argv
 *  @return No return on success. Negative integer on failure.
 */
int
load_elf(char *filename, char **argv)
{
    simple_elf_t simelf;
    int index;
    uintptr_t stack_addr;

    for (index = 0; index < exec2obj_userapp_count; index++) {
        if(strcmp(filename, exec2obj_userapp_TOC[index].execname)
          == 0){
            break;
        }
    }
    if(index == exec2obj_userapp_count){ // didn't find it
        kernlog(1, "Missing elf file!");
        return -1;
    }

    if ( elf_load_helper( &simelf, filename) != ELF_SUCCESS ){
        kernlog(1, "Wrong elf!");
        return -1;
    }

    if( load_elf_mem(&simelf, index) < 0 )
        return -1;

    // set the program's user stack for _main
    stack_addr = prep_userstack(argv);
    /* blue pill, back to wonderland */{
        // run
        kernlog(1, "running... program entry point: 0x%08x, stack: 0x%08x",
          (unsigned) simelf.e_entry, stack_addr);
        run_user(simelf.e_entry, stack_addr);
    }

    // error happened.
    // we need to free the entire virtual memory
    kernlog(1, "Loader error!");

    return -1;
}


/*@}*/
