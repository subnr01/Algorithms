#ifndef _PAGEFAULT_H
#define _PAGEFAULT_H

#include <ureg.h>

void pagefault_wrapper();
void pagefault_handler(ureg_t );
void zfod_pagefault(ureg_t *);

#endif // for #ifndef _PAGEFAULT_H
