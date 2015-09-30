/** @file malloc.c
 *  @brief malloc wrappers to make malloc thread safe
 *
 *  We use a mutex lock to enforce thread safety
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs
 */

#include <stdlib.h>
#include <types.h>
#include <stddef.h>
#include <thr_internals.h>
#include <malloc.h>

/*
 * All those functions here are protected by a malloc lock which is put
 * in the thread lib.
 * It's initialized in the thread init function.
 * The macros are provided by the thread lib.
 */

void *malloc(size_t __size)
{
    MALLOC_LOCK();
    void *ret = _malloc(__size);
    MALLOC_UNLOCK();
    return ret;
}

void *calloc(size_t __nelt, size_t __eltsize)
{
    MALLOC_LOCK();
    void *ret = _calloc(__nelt, __eltsize);
    MALLOC_UNLOCK();
    return ret;
}

void *realloc(void *__buf, size_t __new_size)
{
    MALLOC_LOCK();
    void *ret = _realloc(__buf, __new_size);
    MALLOC_UNLOCK();
    return ret;
}

void free(void *__buf)
{
    MALLOC_LOCK();
    _free(__buf);
    MALLOC_UNLOCK();
}
