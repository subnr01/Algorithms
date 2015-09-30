/** @file tid_table.c
 *  @brief tid table module implementation file
 *
 *  This is the tid table module. The table is storing pointers to
 *  thread control block. When doing inserting, searching, and removing
 *  operations, we're using tid as indexing item.
 *
 *  The tid table uses skip list as data structure storing and search
 *  items. This consumes on average O(lg N) time.
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @bug No known bugs.
 */
#include <tid_table.h>
#include <skiplist.h>
#include <klock.h>
#include <tcb.h>
#include <stddef.h>
#include <assert.h>
#include <skiplist.h>

#define MAX_LEVEL 11

#define KERNLOG_L5_ON
#include <kernlog.h>

static Skipset_t *tidtable_ss;
static kmutex_t table_kmu; // would be better if we have rwlock

static getvalue_fun_t getvalue;

/** @brief tid table init
 *  @return Void.
 */
void tidtable_init()
{
    assert( (tidtable_ss = make_skipset(MAX_LEVEL) ) != NULL );
    kmutex_init(& table_kmu);
    getvalue = &get_tid_fromtcb ;
}

/** @brief insert new thread into the tid table
 *  @return 0 on success. negative number on failure.
 */
int tidtable_insert(void *tcb)
{
    int res;
    kmutex_lock( & table_kmu);{
        res = sl_insert(tidtable_ss, tcb, getvalue);
    } kmutex_unlock( & table_kmu);
    return  res;
}

/** @brief remove thread item from tid table
 *  @return Void.
 */
void tidtable_remove(int tid)
{
    kmutex_lock( & table_kmu);{
        sl_remove(tidtable_ss, tid, getvalue);
    } kmutex_unlock( & table_kmu);
}

/** @brief search and return the thread item based on tid indexing.
 *  @return item pointer on success. NULL on failure.
 */
void* tidtable_search(int tid)
{
    Skipnode_t *sn;
    void *tcb;
    kmutex_lock( & table_kmu);{
        sn = sl_find(tidtable_ss, tid, getvalue);
    } kmutex_unlock( & table_kmu);

    if(sn == NULL)
        return NULL;
    tcb = sn->item;

    return tcb;
}
