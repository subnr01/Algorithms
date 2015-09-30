/** @file kernlog.h
 *
 *  The kernel logging module
 *  This logging is useful for development and testing purose.
 *
 *  Overally, there is a macro to turn all the log on or off. Notice
 *  this is conditional compilation.
 *
 *  The logging has 5 levels. Based on how verbose information is
 *  expected, the logging level could be tuned to print as wants.
 *
 *  @author Hongchao Deng (hongchad)
 */
#ifndef KERNLOG_H
#define KERNLOG_H

#include <simics.h>

/* to turn off the logging, comment out this macro */
//#define KERNLOG_ON


#ifdef KERNLOG_ON
    /*
     * There are five levels:
     * Level 1 is the most critical and least verbose mode
     * Level 5 is the least critical and most verbose mode
     *
     * In each module, just add two lines to have logging work:
     *   #define KERNLOG_L#_ON
     *   #include <kernlog.h>
     * assign the level to the number after 'L'.
     * Notice that the #define should be written before the #include
     *
     * Any level in kernlog() that's smaller than it is going to be
     * logged onto the lprintf output.
     */

    #ifdef KERNLOG_L1_ON
        #ifdef KERNLOG_LEVEL
            #undef KERNLOG_LEVEL
        #endif
        #define KERNLOG_LEVEL 1
    #endif

    #ifdef KERNLOG_L2_ON
        #ifdef KERNLOG_LEVEL
            #undef KERNLOG_LEVEL
        #endif
        #define KERNLOG_LEVEL 2
    #endif

    #ifdef KERNLOG_L3_ON
        #ifdef KERNLOG_LEVEL
            #undef KERNLOG_LEVEL
        #endif
        #define KERNLOG_LEVEL 3
    #endif

    #ifdef KERNLOG_L4_ON
        #ifdef KERNLOG_LEVEL
            #undef KERNLOG_LEVEL
        #endif
        #define KERNLOG_LEVEL 4
    #endif

    #ifdef KERNLOG_L5_ON
        #ifdef KERNLOG_LEVEL
            #undef KERNLOG_LEVEL
        #endif
        #define KERNLOG_LEVEL 5
    #endif

    #ifdef KERNLOG_LEVEL
        /* logging interface*/
        #define kernlog(level, fmt, ...) \
        { \
            if(level <= KERNLOG_LEVEL) \
                lprintf(fmt, ##__VA_ARGS__); \
        }
    #else
        #define kernlog(level, fmt, ...)
    #endif

#else
    #define kernlog(level, fmt, ...)
#endif


#endif /* KERNLOG_H */


