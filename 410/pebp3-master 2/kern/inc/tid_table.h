/** @file tid_table.h
 *  @brief tid table module header file
 *
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @bug No known bugs.
 */
#ifndef _TID_TABLE_H
#define _TID_TABLE_H

void tidtable_init();
int tidtable_insert(void *tcb);
void tidtable_remove(int tid);
void* tidtable_search(int tid);

#endif // for #ifndef _TID_TABLE_H
