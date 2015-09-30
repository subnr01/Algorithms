#include <stddef.h>
#include <malloc.h>
#include <malloc_internal.h>
#include <klock.h>
#include <_malloc.h>

void malloc_init()
{
    kmutex_init(& malloc_mutex);
}

/* safe versions of malloc functions */
void *malloc(size_t size)
{
    void *res;
    kmutex_lock( & malloc_mutex);{
        res = _malloc(size);
    } kmutex_unlock( & malloc_mutex);
    return res;
}

void *memalign(size_t alignment, size_t size)
{
    void *res;
    kmutex_lock( & malloc_mutex);{
        res = _memalign(alignment, size);
    } kmutex_unlock( & malloc_mutex);
    return res;
}

void *calloc(size_t nelt, size_t eltsize)
{
    void *res;
    kmutex_lock( & malloc_mutex);{
        res = _calloc(nelt, eltsize);
    } kmutex_unlock( & malloc_mutex);
    return res;
}

void *realloc(void *buf, size_t new_size)
{
    void *res;
    kmutex_lock( & malloc_mutex);{
        res = _realloc(buf, new_size);
    } kmutex_unlock( & malloc_mutex);
    return res;
}

void free(void *buf)
{
    kmutex_lock( & malloc_mutex);{
        _free(buf);
    } kmutex_unlock( & malloc_mutex);
}

void *smalloc(size_t size)
{
    void *res;
    kmutex_lock( & malloc_mutex);{
        res = _smalloc(size);
    } kmutex_unlock( & malloc_mutex);
    return res;
}

void *smemalign(size_t alignment, size_t size)
{
    void *res;
    kmutex_lock( & malloc_mutex);{
        res = _smemalign(alignment, size);
    } kmutex_unlock( & malloc_mutex);
    return res;
}

void *scalloc(size_t size)
{
  return NULL;
}

void sfree(void *buf, size_t size)
{
    kmutex_lock( & malloc_mutex);{
        _sfree(buf, size);
    } kmutex_unlock( & malloc_mutex);
}


