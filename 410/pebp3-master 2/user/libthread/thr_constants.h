/** @file thr_constants.h 
 *  @brief macros for return values and other constants 
 */
#ifndef THR_CONSTANT_H
#define THR_CONSTANT_H

/** @brief return code for thread library success */
#define THR_SUCCESS (0) //
/** @brief negative error codes for communicating problems
 */
#define THR_ENOMEM (-10) //!< not enough memory to complete function
#define THR_EPAGE_SCREWED (-11) //!< can't call new_pages, PAGE_SIZE > INT_MAX
#define THR_DUP_JOIN (-12) //!< multiple thr_joins on same tid
#define THR_NULL (0) //!< signals no thread
#define THR_ERROR (-1) //!< negative number used for error handling
#define THR_EFORK (-13) //!< problem calling thread_fork

/* comment style macro */
#define CRITICAL_SECTION


#endif /* THR_CONSTANT_H */
