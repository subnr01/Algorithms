#ifndef _PAGEFAULT_H
#define _PAGEFAULT_H

#include <ureg.h>

void AC_wrapper();
void GP_wrapper();
void SS_wrapper();
void NP_wrapper();
void TS_wrapper();

void TS_handler(ureg_t context);

#endif // for #ifndef _PAGEFAULT_H
