/** @file skiplist.h
 *  @brief skiplist module header file
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @ref: http://en.literateprograms.org/Skip_list_(Java)
 *  @bug No known bugs.
 */
#ifndef _SKIPLIST_H
#define _SKIPLIST_H

typedef struct _Skipnode_t{
    void *item;
    struct _Skipnode_t **forward; // array of pointers
} Skipnode_t;

typedef struct _Skipset_t {
    Skipnode_t *header;
    int level;
    int max_level; // NOTE: [0..max_level] includes 0
} Skipset_t;

typedef int (*getvalue_fun_t)(void *);


Skipnode_t* make_skipnode(int level, void *item);
Skipset_t *make_skipset(int max_level);
void* sl_find(Skipset_t *ss, int val, getvalue_fun_t getvalue);
int sl_contains(Skipset_t *ss, int val, getvalue_fun_t getvalue);
int sl_insert(Skipset_t *ss, void *item, getvalue_fun_t getvalue);
void sl_remove(Skipset_t *ss, int val, getvalue_fun_t getvalue);

#endif // for #ifndef _SKIPLIST_H
