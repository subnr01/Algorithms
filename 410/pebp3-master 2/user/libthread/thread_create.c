/** @file thread_create.c
 *  @brief contains functions relevant to creating new threads
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 *
 *  The core design principle behind our approach to thread creation was
 *  automatically scaling the number of threads with available memory whilst 
 *  minimizing assumptions. We obtain all memory needed  for a thread before 
 *  thread_fork is called, we perform a first fit search using new_pages and
 *  remove pages to find a location for the thread stack (rather than using
 *  static addresses).
 *
 *  Although this approach makes thread creation slow, it can take advantage
 *  of all available memory and we can change the fit algorithm for better
 *  performance in the future.
 *
 *  We also protect thread stacks from eachother by surrounding thread stacks
 *  with unallocated guard pages. For this implementation guards are a single
 *  page, but this can be changed if needed.
 *
 *  @bugs more of a limitation, we require the thread stack size to convert 
 *  to a signed int without its' value changing, otherwise we refuse to create 
 *  threads. This protects against a potential integer overflow
 *
 */

#include <thr_internals.h>
/************** thread create *********************/

/** @brief create a new thread
 *  
 *  We use the page approach because it is robust, it doesn't assume fixed
 *  thread locations and can scale arbitrarily with memory
 *
 *  NOTE: Current limitation that stack size needs to fit in an int
 *
 *  NOTE: goto's are used in this function, they perform a useful task
 *  of reducing duplicate code and nested if statements.
 *
 *  @param *func(void*) the function to execute with the new thread
 *  @return the thread id of the newly created thread, negative on failure
 *
 *
 */
int thr_create( void *(*func)(void *), void *args ){
   
    SET_MULTI_THREAD_ENV(); //turn off automatic stack growth 
    uintptr_t thread_searchbase = THR_PTR_ALIGN(_search_start); //get a page aligned pointer
    
    uintptr_t start = thread_searchbase; //used to detect search wrap around


    if (thread_size <= ((unsigned int) (INT_MAX))){ //check for overflow

        mutex_lock(&cleanup_lock); //only try to create 1 thread at a time

        
        while(1){ //keep searching until i've found the stack

            uintptr_t low_guard = 
                (thread_searchbase - thread_size - 2*GUARD_SIZE);
            
            if (low_guard > start){ //wrap around detected
                mutex_unlock(&cleanup_lock);
                return THR_ENOMEM;
            }

            if(low_guard <= heap_guard){ 
                //we need to move the heap protector down
                
                mutex_lock(&malloc_lock);  //stop thread malloc expanding heap
                remove_pages((void*)heap_guard);

                uintptr_t heap_end = low_guard;

                //Try to allocate a new heap guard
                while (new_pages((void*) (heap_end - GUARD_SIZE), 
                    (int)GUARD_SIZE) != 0){

                    heap_end -= GUARD_SIZE; //find another spot
                    
                    if (heap_end > start){ //wrapped around, no place for guard
                        new_pages((void*)heap_guard, (int) GUARD_SIZE);

                        mutex_unlock(&malloc_lock);
                        mutex_unlock(&cleanup_lock);
                        return THR_ENOMEM; //heap expanded right up next to us
                    }
                }
                mutex_unlock(&malloc_lock);
                heap_guard = heap_end - GUARD_SIZE;
            }

            //space for a low guard page?
            if (new_pages((void*) low_guard, (int) GUARD_SIZE) != 0){
                //no good, retry;
                goto thr_create_retry;
            }

            remove_pages((void*) low_guard); //preserve protection by unalloc

            if(new_pages((void*) (low_guard + GUARD_SIZE), 
                (int) thread_size) != 0){
                //space not contiguous, retry
                goto thr_create_retry;
            }
            // space for a high guard page?
            if (new_pages((void*) (thread_searchbase - GUARD_SIZE),
                GUARD_SIZE) != 0){
                //clean up allocated space and retry
                remove_pages((void*) (low_guard + GUARD_SIZE)); 
                goto thr_create_retry;
            }
            remove_pages((void*) (thread_searchbase - GUARD_SIZE));
            //CONGRATULATIONS! WE'VE GOT THE STACK SPACE
            //change thread_searchbase to the base of the new stack
            thread_searchbase = thread_searchbase - GUARD_SIZE; 
            break;

            thr_create_retry:
                thread_searchbase =  thread_searchbase - GUARD_SIZE;
                if (start <= thread_searchbase){
                    mutex_unlock(&cleanup_lock);
                    return THR_ENOMEM; //wrapped around, out of memory
                }
                else{
                    start = thread_searchbase; //new threshold
                }
                continue;
        }
        //success! i have all the pages i need for a stack
        thd_data_t *dptr = malloc(sizeof(thd_data_t));
        if (dptr == NULL){
            remove_pages((void*) thread_searchbase);
            mutex_unlock(&cleanup_lock);
            return THR_ENOMEM; //not enough memory to allocate thread data
        }
        //success! i have the memory for thread data structures
        
        uintptr_t child_esp = prep_child ( //prepare the child stack
            (void*) thread_searchbase,
            dptr,
            func,
            args,
            &child_launcher);
        
        //child stack prepared
        dptr->base = thread_searchbase; //setup base part of data structure
        dptr->tlist_node_space.slot = gettid(); //pass my tid to the to child

        int rv = thread_fork(child_esp, thread_searchbase);
        if (rv < 0){
            free(dptr);//thread_fork failed
            remove_pages(( void* )thread_searchbase);
            mutex_unlock(&cleanup_lock);
            return THR_EFORK;
        }

        mutex_unlock(&cleanup_lock);
        Deschedule(); //deschedule until the child thread wakes me up
        _search_start = thread_searchbase + thread_size; 
        return rv;
    }
    else{  //overflow, but we can allocate a page at a time
          //TODO for now i'm going to make this a limitation
          //we can implement a page by page allocation later
        return THR_ERROR;
    }
}

/** @brief function for setting up and invoking the child post fork
 * 
 *  To prevent race conditions with the parent we must wake the parent up
 *  once we have added ourselves to the thread list
 *
 *  @param *ptr data structure for child thread
 *  @param *func(void*) function to invoke after setup
 *  @param *args argument to pass to function
 */
void child_launcher(thd_data_t *ptr, void *(*func)(void *), void *args ){
    int parent = thr_data_init(ptr);

    reg_child_fault_handler((void*) ptr->base); //register error handler
    if (parent != 0){
        while (thr_yield(parent) == 0)
            continue; //wait until parent deschedules

        make_runnable(parent); //let parent know we are part of thread list now
    }
            
    thr_exit(func(args));
}
/** @brief registers a page fault handler for the child
 *  
 *  In a multiple threaded environment if we encounter a fault we 
 *  are unlikely going to be able to continue doing useful work, 
 *  thus we have decided to call task_vanish if this occurs.
 *
 *  Future work would be to have a smarter page fault handler, but 
 *  for now this should do
 *
 *  @param *stack location of the handler stack
 *
 *  NOTE: for now we are using the thread stack, this has 
 *  a limitation in that if someone calls remove_pages
 *  on this stack our handler will fault. In the future
 *  we may want to consider an alternative.
 */
void reg_child_fault_handler(void *stack){
    swexn(stack, child_fault_handler, NULL, NULL);
}

/** @brief simple fault handler which calls task_vanish
 *  @param *arg specified when registered
 *  @param *ureg pointer to a ureg area
 */
void child_fault_handler(void *arg, ureg_t *ureg){
    task_vanish(THR_ERROR);
}

/** @brief sets up the initial data structure values for a thread
 *
 *  NOTE: the parent tid is stored in the tlist_node->slot
 *
 *  @param *thread_dataptr points to thread data in heap
 *  @return when applicable, returns the tid of the parent who created child
 *      returns 0 otherwise
 */
int thr_data_init(thd_data_t *thread_dataptr){
    int tid = gettid();
    
    thread_dataptr->tlist_node = &thread_dataptr->tlist_node_space;
    int parent = thread_dataptr->tlist_node->slot; //save value
    thread_dataptr->tlist_node->slot = tid;

    /* add itself to the thread list */

    TLIST_WLOCK();
    q_push(tlist_head, thread_dataptr->tlist_node);
    
    if (q_find(tlist_head, parent) == NULL)
        parent = 0; //no parent or parent does not exist
    TLIST_UNWLOCK();

    thread_dataptr->status = NULL;
    thread_dataptr->join_tid = THR_NULL;
    
    return parent;
}
