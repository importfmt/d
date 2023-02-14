#ifndef _lh_H
#define _lh_H

struct lh_tree_node;
typedef struct lh_tree_node *lh_priority_queue;

lh_priority_queue lh_initialize(void);
int lh_find_min(lh_priority_queue h);
int lh_is_empty(lh_priority_queue h);
lh_priority_queue lh_merge(lh_priority_queue h1, lh_priority_queue h2);
lh_priority_queue lh_insert1(int x, lh_priority_queue h);
lh_priority_queue lh_delete_min(lh_priority_queue h);
static lh_priority_queue lh_merge1(lh_priority_queue h1, lh_priority_queue h2);
void lh_swap_children(lh_priority_queue h);

#define lh_insert(x, h) (h = lh_insert1((x), h))

struct lh_tree_node
{
        int element;
        lh_priority_queue left;
        lh_priority_queue right;
        int npl;        /* Null path length */
};

static lh_priority_queue lh_merge1(lh_priority_queue h1, lh_priority_queue h2)
{
        if (h1->left == NULL)
                h1->left = h2;
        else
        {
                h1->right = lh_merge(h1->right, h2);
                if (h1->left->npl < h1->right->npl)
                        lh_swap_children(h1);
                h1->npl = h1->right->npl + 1;
        }
        return h1;
}

lh_priority_queue lh_merge(lh_priority_queue h1, lh_priority_queue h2)
{
        if (h1 == NULL) return h2;
        if (h2 == NULL) return h1;
        if (h1->element < h2->element) return lh_merge1(h1, h2);
        else return lh_merge1(h2, h1);
}

lh_priority_queue lh_insert1(int x, lh_priority_queue h)
{
        lh_priority_queue single_node;
        
        single_node = (lh_priority_queue)malloc(sizeof(struct lh_tree_node));
        if (single_node == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        else
        {
                single_node->element = x;
                single_node->npl = 0;
                single_node->left = single_node->right = NULL;
                h = lh_merge(single_node, h);
        }
        return h;
}

lh_priority_queue lh_delete_min(lh_priority_queue h)
{
        lh_priority_queue left_heap, right_heap;

        if (lh_is_empty(h))
        {
                perror("Priority queue is empty.");
                return h;
        }
        
        left_heap = h->left;
        right_heap = h->right;
        free(h);
        return lh_merge(left_heap, right_heap);
}

#endif
