#include <thr_internals.h>
/************** thread create *********************/

/** @brief create a new thread
 *  @return 0 on success negative number on failure
 *
 *  We use the page approach because it is robust, it doesn't assume fixed
 *  thread locations and can scale arbitrarily with memory
 *
 *  NOTE: current limitation that stack size needs to fit in an int
 *
 *  TODO: heap collision
 */
int thr_create( void *(*func)(void *), void *args ){
    uintptr_t base = THR_PTR_ALIGN(&args); //get a page aligned pointer
    uintptr_t start = base; //used to detect wrap around, aka lacking memory

    //lprintf("mutex_lock start \n");
    mutex_lock(&cleanup_lock); //only try to create 1 thread at a time
    //lprintf("mutex_lock end \n");
    //avoids memory allocation race conditions

    if (thread_size <= ((unsigned int) (INT_MAX))){

        /** @brief internal helper function to reduce duplicate code
         *  We try to find the first available page, this is a guard page
         *
         *  When we return, we will have de-allocated this guard page
         *  and incremented the base by page size
         *
         *  if we succeed outer variable base will be pointing to
         *  the stack we allocated
         *
         *  @return THR_SUCCESS once we have allocated needed stack or
         *  we return negative number error code
         *
         */
        lprintf("while loop \n");
        //inline int thr_allocate_stack(){
        while(1){

            uintptr_t end_check = (base - thread_size - 2*PAGE_SIZE);
            if (end_check > start){ //wrap around detected
                mutex_unlock(&cleanup_lock);
                return THR_ENOMEM;
            }

            if(end_check <= heap_guard){
                //we need to move the heap guard down by 1 more PAGE_SIZE
                mutex_lock(&malloc_lock);  //we can't have malloc expanding heap
                remove_pages((void*)heap_guard);

                uintptr_t heap_end = end_check;
                while (new_pages(((void*) heap_end-PAGE_SIZE), (int)PAGE_SIZE) != 0){
                    heap_end -= PAGE_SIZE;
                    if (end_check > start){
                        new_pages((void*)heap_guard, (int) PAGE_SIZE);
                        mutex_unlock(&malloc_lock);
                        mutex_unlock(&cleanup_lock);
                        return THR_ENOMEM; //heap expanded right up next to us
                    }
                }
                mutex_unlock(&malloc_lock);
                heap_guard = end_check - PAGE_SIZE;
            }
            //space for a low guard page?
            if (new_pages((void*) end_check, (int) PAGE_SIZE) != 0){
                //no good, retry;
                goto thr_create_retry;
            }
            remove_pages((void*) end_check); //preserve protection by unalloc

            if(new_pages((void*) (end_check + PAGE_SIZE), (int) thread_size) != 0){
                //space not contiguous, retry
                goto thr_create_retry;
            }
            // space for a high guard page?
            if (new_pages((void*) (base - PAGE_SIZE), PAGE_SIZE) != 0){
                goto thr_create_retry;
            }
            remove_pages((void*) (base - PAGE_SIZE));
            //CONGRATULATIONS! WE'VE GOT THE STACK SPACE
            base = end_check + PAGE_SIZE; //make it easier for caller
            break;

            thr_create_retry:
                base =  base - PAGE_SIZE;
                if (start <= base){
                    mutex_unlock(&cleanup_lock);
                    return THR_ENOMEM; //wrapped around, out of memory
                }
                else{
                    start = base; //new threshold
                }
                continue;
        }

        lprintf("while loop ends\n");
        //success! i have all the pages i need for a stack
        thd_data_t *dptr = malloc(sizeof(thd_data_t));
        if (dptr == NULL){
            remove_pages((void*) base);
            mutex_unlock(&cleanup_lock);
            return THR_ENOMEM; //not enough memory to allocate thread data
        }
        lprintf("child found %x\n", base);
        uintptr_t child_esp = prep_child(
            (void*) base,
            &thr_data_init,
            func,
            dptr,
            &thr_exit_wrapper,
            args);


        /* add itself to the thread list */
        TLIST_WLOCK();
        q_push(tlist_head, dptr->tlist_node);
        dptr->tlist_node->slot = THR_ERROR; //so we can cleanup thread list if this fails
        TLIST_UNWLOCK();
        
        dptr->base = base; //initialize base part of data structure

        //success! i have the memory for thread data structures
        int rv = thread_fork(child_esp, base);
        if (rv < 0){
            
            TLIST_WLOCK();
            q_remove(tlist_head, THR_ERROR);
            TLIST_UNWLOCK();

            free(dptr);//thread_fork failed
            return THR_EFORK;
        }
        return THR_SUCCESS;
    }
    else{ //overflow, but we can allocate a page at a time
          //TODO for now i'm going to make this a limitation
          //we can implement a page by page allocation later
        mutex_unlock(&cleanup_lock);
        return THR_ERROR;
    }


}
