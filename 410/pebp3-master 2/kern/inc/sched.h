/** @file sched.h
 *  @brief kernel function to relevant syscall related to scheduling.
 */
#ifndef _SCHED_H
#define _SCHED_H

int yield_to(int tid);
void desche();
int make_run(int tid);

#endif // for #ifndef _SCHED_H
