#ifndef _BQ_H
#define _BQ_H

#define BQ_MAX_TREES_SIZE 100

typedef struct bq_node *bq_bin_tree;
typedef struct bq_collection *binary_queue;

bq_bin_tree bq_combine_trees(bq_bin_tree t1, bq_bin_tree t2);
binary_queue bq_merge(binary_queue h1, binary_queue h2);
int bq_delete_min(binary_queue h);
int bq_is_empty(binary_queue h); // TODO
binary_queue bq_initialize(); // TODO

struct bq_node
{

        int element;
        bq_bin_tree left_child;
        bq_bin_tree next_sibling;
};

struct bq_collection
{
        int current_size;
        bq_bin_tree the_trees[bq_MAX_TREES_SIZE];
};

bq_bin_tree bq_combine_trees(bq_bin_tree t1, bq_bin_tree t2)
{
        if (t1->element > t2->element) return bq_combine_trees(t2, t1);
        t2->next_sibling = t1->left_child;
        t1->left_child = t2;
        return t1;
}

binary_queue bq_merge(binary_queue h1, binary_queue h2)
{
        bq_bin_tree t1, t2, carry = NULL;
        int i, j;

        if (h1->current_size + h2->current_size > bq_MAX_TREES_SIZE)
        {
                perror("Merge would exceed capacity.");
                return NULL;
        }

        h1->current_size += h2->current_size;
        for (i = 0, j = 1; j <= h1->current_size; i++, j *= 2)
        {
                t1 = h1->the_trees[i];

                switch (!t1 + 2 * !!t2 + 4 * !!carry)
                {
                        case 0:
                        case 1:
                                break;
                        case 2:
                                h1->the_trees[i] = t2;
                                h2->the_trees[i] = NULL;
                                break;
                        case 3:
                                carry = bq_combine_trees(t1, t2);
                                h1->the_trees[i] = h2->the_trees[i] = NULL;
                                break;
                        case 4:
                                h1->the_trees[i] = carry;
                                carry = NULL;
                                break;
                        case 5:
                                carry = bq_combine_trees(t1, carry);
                                h1->the_trees[i] = NULL;
                                break;
                        case 6:
                                carry = bq_combine_trees(t2, carry);
                                h2->the_trees[i] = NULL;
                                break;
                        case 7:
                                h1->the_trees[i] = carry;
                                carry = bq_combine_trees(t1, t2);
                                h2->the_trees[i] = NULL;
                                break;
                }
        }
        return h1;
}

int bq_delete_min(binary_queue h)
{
        int i, j, min_tree, min_item;
        binary_queue deleted_queue;
        bq_bin_tree deleted_tree, old_root;

        if (bq_is_empty(h))
        {
                perror("Empty binomial queue.");
                return -1;
        }

        for (i = 0; i < bq_MAX_TREES_SIZE; i++)
        {
                if (h->the_trees[i] && h->the_trees[i]->element < min_item)
                {
                        min_item = h->the_trees[i]->element;
                        min_tree = i;
                }
        }

        deleted_tree = h->the_trees[min_tree];
        old_root = deleted_tree;
        deleted_tree = deleted_tree->left_child;
        free(old_root);

        deleted_queue = bq_initialize();
        deleted_queue->current_size = (1 << min_tree) - 1;
        for (j = min_tree - 1; j >= 0; j--)
        {
                deleted_queue->the_trees[j] = deleted_tree;
                deleted_tree = deleted_tree->next_sibling;
                deleted_queue->the_trees[j]->next_sibling = NULL;
        }
        
        h->the_trees[min_tree] = NULL;
        h->current_size -= deleted_queue->current_size + 1;
        bq_merge(h, deleted_queue);
        return min_item;
}

#endif
