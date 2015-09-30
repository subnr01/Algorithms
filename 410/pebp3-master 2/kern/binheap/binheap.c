/** @file binheap.c
 *  @brief binheap module implementation file
 *
 *  This is a minimum binary heap implemented in linked list.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <binheap.h>
#include <stddef.h>
#include <malloc.h>
#include <malloc_internal.h>
#include <assert.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief swap the item field of two heapnodes
 *  @return Void.
 */
static void swap_item(heapnode_t *a, heapnode_t *b)
{
    void *temp = a->item;
    a->item = b->item;
    b->item = temp;
}

/** @brief binary heap initialization
 *
 *  @param bh
 *  @return Void.
 */
void
bh_init(binheap_t *bh)
{
    q_init( & bh->queue);
}

/** @brief make a new heap node
 *
 *  We're allocating space for the new heap node, pointing the item
 *  field to the parameter, and returing the pointer to the new node.
 *
 *  @param item
 *  @return Void.
 */
heapnode_t* make_heapnode(void *item)
{
    heapnode_t *hn;

    if( (hn = malloc(sizeof(heapnode_t))) == NULL){
        return NULL;
    }

    hn->parent = hn->child1= hn->child2 = NULL;
    qnode_setitem(& hn->qnode, hn);
    hn->item = item;

    return hn;
}

/** @brief binary heap shift the node up function
 *
 *  @param bh binary heap
 *  @param hn heapnode
 *  @param cmp compare function
 *  @return Void.
 */
static void
bh_shiftup(binheap_t *bh, heapnode_t *hn, cmp_func_t cmp)
{
    kernlog(5, "  binheap shiftup");

    heapnode_t *root;
    root = qnode_getitem(q_index(& bh->queue, 0));

    while(hn != root){
        // if parent is larger than the new heapnode, then shift the new
        // heapnode up.
        if( cmp(hn->item, hn->parent->item) < 0 ){
            swap_item(hn, hn->parent);
        }
        else{
            break;
        }
        hn = hn->parent;
    }

    kernlog(5, "  finished binheap shiftup");
}

/** @brief binary heap pushing a new heapnode function
 *
 *  @param bh binary heap
 *  @param hn heapnode
 *  @param cmp compare function
 *  @return Void.
 */
void bh_push(binheap_t *bh, heapnode_t *hn, cmp_func_t cmp)
{
    heapnode_t *last;

    kernlog(5, "binheap push");

    if(q_count(&bh->queue) == 0){
        // pushing it is enough when there's no other item
        q_push(&bh->queue, & hn->qnode);
    }
    else{
        last = qnode_getitem(q_last(&bh->queue));

        if(last->parent == NULL){//root
            last->child1 = hn;
            hn->parent = last;
        }
        else{
            last = last->parent;

            assert(last->child1 != NULL);

            if(last->child2 == NULL){
                last->child2 = hn;
                hn->parent = last;
            }
            else{
                last = qnode_getitem(last->qnode.next);

                assert( last->child1 == NULL);

                last->child1 = hn;
                hn->parent = last;
            }
        }

        q_push(&bh->queue, & hn->qnode);
        bh_shiftup(bh, hn, cmp);
    }

    kernlog(5, "finished binheap push");
}

/** @brief binary heap shift the node down function
 *
 *  @param bh binary heap
 *  @param hn heapnode
 *  @param cmp compare function
 *  @return Void.
 */
static void
bh_shiftdown(binheap_t *bh, heapnode_t *hn, cmp_func_t cmp)
{
    heapnode_t *child1, *child2;

    while(hn->child1 != NULL){
        // choose the smaller child to compare and maybe swap.
        child1 = hn->child1;
        child2 = hn->child2;
        if(child2 != NULL &&
          cmp(child2->item, child1->item) < 0)
            child1 = child2;

        // if the heapnode is larger than its child, then shift the
        // heapnode down
        if(cmp(hn->item, child1->item) > 0){
            swap_item(hn, child1);
        }
        else
            break;

        hn = child1;
    }
}

/** @brief binary heap poping minimum itme function
 *
 *  @param bh binary heap
 *  @param hn heapnode
 *  @param cmp compare function
 *  @return minimum item
 */
void*
bh_pop(binheap_t *bh, cmp_func_t cmp)
{
    // interrupts are disabled
    void *res;
    heapnode_t *root;
    heapnode_t *last;
    heapnode_t *last_parent;

    if(q_empty( & bh->queue)){
        return NULL;
    }
    else if(q_count( &bh->queue) == 1){
        root = qnode_getitem(q_pop(&bh->queue));
        res = root->item;
        _free(root); // bad impl...
        return res;
    }

    root = qnode_getitem(q_index(&bh->queue, 0));
    res = root->item;
    last = qnode_getitem(q_last(&bh->queue));
    last_parent = last->parent;

    assert(last_parent != NULL);

    swap_item(root, last);

    // remove child records from its parent
    if(last == last_parent->child1){
        last_parent->child1 = NULL;
    }
    else{
        last_parent->child2 = NULL;
    }

    q_remove(&bh->queue, & last->qnode);

    // we are using the unblocked free function because the interrupts
    // are disabled entering this function in the kernel.
    // This decision makes the code sort of specific. However, the basic
    // idea for the entire linked list implemented binary heap should be
    // generic. In other cases, using a free from malloc library should
    // be enough.
    _free(last);

    bh_shiftdown(bh, root, cmp);

    return res;
}

/** @brief get the minimum item.
 *
 *  @param bh binary heap
 *  @return first item in the first heapnode
 */
void*
bh_firstitem(binheap_t *bh)
{
    heapnode_t *hn;
    if(q_empty( & bh->queue))
        return NULL;
    else{
        hn = (heapnode_t *) qnode_getitem(q_index(&bh->queue, 0));
        return hn->item;
    }
}
