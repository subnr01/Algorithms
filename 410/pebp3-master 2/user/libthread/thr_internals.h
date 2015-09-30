/** @file thr_internals.h
 *
 *  @brief This file may be used to define things
 *         internal to the thread library.
 *  
 *  @author Alan Keith (arkeith) Hongchao Deng (hongchad)
 *
 * 
 *  Macros and function prototypes used by our thread library are deifned here
 *
 */

#ifndef THR_INTERNALS_H
#define THR_INTERNALS_H

#include <malloc.h>
#include <mutex_type.h>
#include <thread_queue.h>
#include <mutex.h>
#include <syscall.h>
#include <stdint.h>
#include <thread.h>
#include <limits.h>
#include <rwlock.h>
#include <_multi_thread.h>
#include <thr_constants.h>

#include <simics.h> // debugging

/** @brief size of guard pages, protects thread stacks from eachother */
#define GUARD_SIZE (PAGE_SIZE)

/** @brief Rounds up to the nearest multiple page size */
#define THR_SIZE_ALIGN(size) \
    ( ( (unsigned int)(size) + (PAGE_SIZE-1) ) & ~(PAGE_SIZE-1))

/** @brief Aligns the pointer, rounding down */
#define THR_PTR_ALIGN(ptr) (((uintptr_t) (ptr)) & ~(PAGE_SIZE-1) )

/** @brief malloc macros for thread safe malloc */
#define MALLOC_LOCK()   (mutex_lock(&malloc_lock)) //!< lock
#define MALLOC_UNLOCK() (mutex_unlock(&malloc_lock)) //!< unlock

/** @brief reader/writer lock macros for protecting thread list */
#define TLIST_RLOCK()   (rwlock_lock(&tlist_lock, RWLOCK_READ))
#define TLIST_UNRLOCK() (rwlock_unlock(&tlist_lock)) 
#define TLIST_WLOCK()   (rwlock_lock(&tlist_lock, RWLOCK_WRITE)) 
#define TLIST_UNWLOCK() (rwlock_unlock(&tlist_lock)) 


/** @brief macros for basic pointer arithmetic */
#define ADD_PTR(PTR, SIZE) ( (uintptr_t)(PTR) + (uintptr_t)(SIZE))
#define SUB_PTR(PTR, SIZE) ( (uintptr_t)(PTR) - (uintptr_t)(SIZE))


/** @brief macro for getting the data structure for the invoking thread */
#define GET_SELF_THD_DATAPTR() (get_thd_dataptr(thr_getid()))

/***  global variables for thread library ***/

/* global mutex */
mutex_t malloc_lock; //!<lock to make malloc thread safe
mutex_t cleanup_lock; //!<lock to ensure only 1 person
rwlock_t tlist_lock; //!< lock to ensure the thread list operation atomical

/* zombie queue */
extern q_node zombie_head_space; //!<space for the head of the zombie queue
extern q_node *zombie_head; //!<head of the zombie queue
q_node tlist_head_space; //!<space for head of thread list
q_node *tlist_head;  //!< head of the thread list

/* thread stack */
unsigned int thread_size; //!< allocated size of each thread stack
unsigned int original_request; //!< original request size by thr_init
uintptr_t heap_guard; //!< protect stacks from heap expansion
uintptr_t _search_start; //!< keep track of highest free space

/** @brief thread data structure
 *  TODO add software exception handler cause we need to reinstall it
 */
typedef struct _thd_data_t {
    q_node tlist_node_space; //!< for thread list queue; thread list internal node
    q_node *tlist_node; //!< for thread list queue; thread list internal node

    void *status;    //!< where we store exit status on thr_exit
    uintptr_t base;  //!< location of allocated stack space
    int join_tid;    //!< the thd_id who called thr_join on us
} thd_data_t;


/************* function declarations *******************/

/** @brief obtain the thread data structure for give tid*/
thd_data_t *get_thd_dataptr(int tid);

int set_join_tid(int tid);
/** @brief deallocates space reserved by thread
 */
void dealloc_thread(int tid);

/** @brief wrapper function for definite deschedule().
 */
void Deschedule();

/** @brief prepare the child stack
 *
 *  This is an assembly wrapper, these arguments are in a specific order
 *
 *  We prepare the child's stack so when we fork we can begin execution
 *
 *  @param *base location of child stack
 *  @param *data_ptr pointer to child threads data structure
 *  @param *func(void*) location of the thread function
 *  @param *func_args arguments for thread function
 *  @param *child_cannon child initialization function
 *
 *  @return the location of the stack pointer which should be used by child
 */
uintptr_t prep_child(
    void *base,
    thd_data_t *data_ptr,
    void *(*func)(void*),
    void *func_args,
    void (*child_cannon)(thd_data_t *ptr, void *(*func)(void *), void *args )
);

void child_launcher(thd_data_t *ptr, void *(*func)(void *), void *args );

/** @brief sets up the initial data structure values for a thread
 *  DOES NOT INITIALIZE base
 *
 *  @param *data location of thread data structure
 *  @return when called by a child thread, will return parent's thread id
 */
int thr_data_init(thd_data_t *data);

/** @brief assembly c prototype for thread_fork
 *
 *  We manipulate it so the child automatically begins execution
 *  on the child stack
 *  @param child_esp the value we should use as esp if child
 *  @return returns 0 if the parent, thread id if the child
 */
int thread_fork(uintptr_t child_esp, uintptr_t child_ebp);

int thr_allocate_stack(void);//helper function prototype

void reg_child_fault_handler(void *stack);
void child_fault_handler(void *arg, ureg_t *ureg);

#define THR_EXCEPTION() (child_fault_handler(NULL, NULL))
#endif /* THR_INTERNALS_H */
