/** @file thr_init.c
 *  @author Alan Keith (arkeith) Hongchao Deng(hongchad)
 *  @brief houses the thr_init function
 */
/** 
 * @brief initialize the thread library
 *
 *  Main initialization:
 *      heap_guard: a guard hinder the heap from growing up here.
 *      zombie_head: queue for zombie reaping.
 *      mutex
 *
 *  thr_init() is required to be called before calling any mutex related
 *  functions.
 *
 *  NOTE: we assume that thread init is only called once
 *  @param size ammount of stack space to allocate for each thread
 *  @return 0 on success, negative number on error
 *
 *  NOTE: none of the locks require malloc usage, so we don't have to free on
 *  error
 */
#include <thr_internals.h>

int thr_init( unsigned int size ){
    //lprintf("thread_init start \n");
    uintptr_t search_base;
    thd_data_t * main_thread_data;

    mutex_init(&malloc_lock);
    mutex_init(&cleanup_lock);
    rwlock_init(&tlist_lock);

    zombie_head = &zombie_head_space;
    q_init(zombie_head);

    /* replace with rwlock later */
    tlist_head = &tlist_head_space;
    q_init(tlist_head);

    /* size init */
    original_request = size;
    thread_size = THR_SIZE_ALIGN(size); //multiple of page size

    //ensure we can call new_page on PAGE_SIZE
    if ( ((unsigned int) PAGE_SIZE) > ((unsigned int) INT_MAX)){
        /* its impossible to call new_page, can't even allocate
         * a single page */
        return THR_EPAGE_SCREWED;
    }

    //page align the end of stack
    search_base = (uintptr_t) THR_PTR_ALIGN(GET_THRSTACK_SEARCH_BASE());

    // to protect stack from heap, we are going to allocate a page
    // so goal is base| UNALLOCATED GUARD_PAGE | ALLOCATED HEAP GUARD PAGE

    heap_guard = (uintptr_t) SUB_PTR(search_base, 2 * PAGE_SIZE);

    if (new_pages((void *)heap_guard, PAGE_SIZE) != 0){
        return THR_ERROR; //couldn't allocate heap guard page, this is weird
    }

    // main thread initialization for thread list
    main_thread_data = _malloc(sizeof(thd_data_t));

    if(main_thread_data == NULL){
        return THR_ERROR;
    }

    /* we are assuming that the main thread won't call thr_exit() */
    thr_data_init(main_thread_data);
    
    _search_start = GET_THRSTACK_SEARCH_BASE();
    return THR_SUCCESS;
}

