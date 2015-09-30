/** @file swexn.h
 *  @brief header file containing function declarations and structs for swexn
 *  
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 *  @bugs No known bugs
 *
 *  Limitations: We expect calls to the swexn syscall to only be done
 *  from user mode. Otherwise our iret_t structure will have inaccurate
 *  fields and behavior is undefined
 */

#ifndef _SWEXN_H
#define _SWEXN_H
#include <ureg.h>
#include <stdint.h>
#include <kernstk.h>
typedef void (*swexn_handler_t)(void *arg, ureg_t *ureg);

/** @brief structure used by swexn to access state pushed onto kern stack
 *  to validate the eflags parameter in uret_t structure given to swexn,
 *  we need a baseline for comparison. If the state of eflags was safe before
 *  this syscall, we can use some of its bits as a baseline
 */
typedef struct _iret_t {
    unsigned int eip; 
	unsigned int cs;
	unsigned int eflags;
	unsigned int esp;
	unsigned int ss;
} iret_t;


int swexn(void *esp3, swexn_handler_t eip, void *arg, ureg_t *newureg);
void swexn_wrapper();

/** @brief arguments are extracted from uintptr_t which is esi */
int swexn_handler(uintptr_t, iret_t);

/** @brief this is a prototype for a wrapper function */
void swexn_restore_reg(ureg_t);

void user_handler_launcher(void*, ureg_t*, uintptr_t, swexn_handler_t);
#endif // for #ifndef _SWEXN_H
