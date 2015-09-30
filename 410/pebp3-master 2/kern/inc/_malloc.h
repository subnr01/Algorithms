/** @file _malloc.h
 *  @brief This files provides only the init function for the malloc
 *  mutex.
 */
#ifndef __MALLOC_H
#define __MALLOC_H

#include <klock.h>

kmutex_t malloc_mutex;

void malloc_init();

#endif // for #ifndef __MALLOC_H
