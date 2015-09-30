/** @file skiplist.c
 *  @brief skiplist module implementation file
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @ref: http://en.literateprograms.org/Skip_list_(Java)
 *  @bug No known bugs.
 */
#include <skiplist.h>
#include <mt19937int.h>
#include <string.h>
#include <getticks.h>
#include <malloc.h>

/** @brief get random level for specific skipset.
 *  @return random level.
 */
int random_level(Skipset_t *ss)
{
    static int first = 1;

    int lvl = 0;

    if(first){
        sgenrand(getticks());
        first = 0;
    }

    while( genrand() < 0x80000000 && lvl < ss->max_level)
        lvl ++;

    return lvl;
}



/** @brief make a new skip node
 *  @return new skip node pointer on success. NULL on failure.
 */
Skipnode_t* make_skipnode(int level, void *item)
{
    Skipnode_t *sn = malloc(sizeof(Skipnode_t));
    if(sn == NULL)
        return NULL;
    sn->forward = calloc(level + 1, sizeof(Skipnode_t *));
    if(sn->forward == NULL){
        free(sn);
        return NULL;
    }
    sn->item = item;

    return sn;
}


/** @brief make a new skip set.
 *  @return new skip set pointer on success. NULL on failure.
 */
Skipset_t *make_skipset(int max_level)
{
    Skipset_t *ss = malloc(sizeof(Skipset_t));
    if(ss == NULL)
        return NULL;
    ss->header = make_skipnode(max_level, NULL);
    if(ss->header == NULL)
        return NULL;
    ss->level = 0;
    ss->max_level = max_level;
    return ss;
}


/** @brief find a skipt node contain indexed on val.
 *  @return skip node pointer on success. NULL on failure.
 */
void* sl_find(Skipset_t *ss, int val, getvalue_fun_t getvalue)
{
    int i;
    Skipnode_t *x = ss->header;

    for(i = ss->level; i>= 0; i--) {
        while( x->forward[i] != NULL && getvalue(x->forward[i]->item) < val ){
            x = x->forward[i];
        }
    }

    x = x->forward[0];

    if(x != NULL && getvalue(x->item) == val)
        return x;

    return NULL;
}

/** @brief Testing if skip set contains the item indexed at val
 *  @return 1 on success. 0 on failure.
 */
int sl_contains(Skipset_t *ss, int val, getvalue_fun_t getvalue)
{
    return (sl_find(ss, val, getvalue) != NULL);
}

/** @brief Testing if skip set contains the item indexed at val
 *  @return 1 on success. 0 on failure.
 */
int sl_insert(Skipset_t *ss, void *item, getvalue_fun_t getvalue)
{
    int i;
    Skipnode_t *x = ss->header;
    Skipnode_t *update[ss->max_level + 1];

    memset(update, 0 , sizeof(Skipnode_t *) * (ss->max_level + 1) );

    for(i = ss->level; i >= 0; i--){
        while( x->forward[i] != NULL &&
          getvalue(x->forward[i]->item) < getvalue(item) ){
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    if( x == NULL || getvalue(x->item) != getvalue(item) ){
        int lvl = random_level(ss);
        if(lvl > ss->level){
            for(i=ss->level + 1; i <= lvl; i++){
                update[i] = ss->header;
            }
            ss->level =lvl;
        }
        x = make_skipnode(lvl, item);
        if(x == NULL)
            return -1;

        for(i = 0; i <= lvl; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
        return 0;
    }
    return -1;
}

/** @brief Remove the skip node indexed at val
 *  @return Void.
 */
void sl_remove(Skipset_t *ss, int val, getvalue_fun_t getvalue){
    int i;
    Skipnode_t *x = ss->header;
    Skipnode_t *update[ss->max_level + 1];
    memset(update, 0 , sizeof(Skipnode_t *) * (ss->max_level + 1) );

    for(i = ss->level; i >= 0; i--){
        while( x->forward[i] != NULL &&
          getvalue(x->forward[i]->item) < val ){
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    if( x != NULL && getvalue(x->item) == val) {
        for(i = 0; i <= ss->level; i ++){
            if( update[i]->forward[i] != x)
                break;
            update[i]->forward[i] = x->forward[i];
        }

        free(x->forward);
        free(x);

        while( ss->level > 0 && ss->header->forward[ss->level] == NULL){
            ss->level --;
        }

    }
}
