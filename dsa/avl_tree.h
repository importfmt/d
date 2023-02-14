#ifndef _AVL_H
#define _AVL_H

struct avl_node;
typedef struct avl_node *avl_position;
typedef struct avl_node *avl_tree;

avl_tree avl_make_empty(avl_tree);              // TODO
avl_position avl_find(int x, avl_tree t);      // TODO
avl_position avl_find_min(avl_tree t);         // TODO
avl_position avl_find_max(avl_tree t);         // TODO
avl_tree avl_insert(int x, avl_tree t);
avl_tree avl_delete(int x, avl_tree t);    // TODO
int avl_retrieve(avl_position p);       // TODO
static int avl_height(avl_position p);
static avl_position avl_single_rotate_with_right(avl_tree);     // TODO
static avl_position avl_single_rotate_with_left(avl_tree);
static avl_position avl_double_rotate_with_right(avl_tree);     // TODO
static avl_position avl_double_rotate_with_left(avl_tree);
int avl_max(int a, int b);  // TODO

struct avl_node
{
        int element;
        avl_tree left;
        avl_tree right;
        int height;
};

static int avl_height(avl_position p)
{
        if (p == NULL)
                return -1;
        else
                return p->height;
}

avl_tree avl_insert(int x, avl_tree t)
{
        if (t == NULL)
        {
                t = (avl_tree)malloc(sizeof(struct avl_node));
                if (t == NULL)
                {
                        perror("out of space.");
                        return NULL;
                }
                else
                {
                        t->element = x;
                        t->height = 0;
                        t->left = t->right = NULL;
                }
        }
        else if (x < t->element)
        {
                t->left = avl_insert(x, t->left);
                if (avl_height(t->left) - avl_height(t->right) == 2)
                {
                        if (x > t->right->element)
                                t = avl_single_rotate_with_left(t);
                        else
                                t = avl_double_rotate_with_left(t);
                }
        }
        else if (x > t->element)
        {
                t->right = avl_insert(x, t->right);
                if (avl_height(t->right) - avl_height(t->left) == 2)
                {
                        if (x > t->right->element)
                                t = avl_single_rotate_with_right(t);
                        else 
                                t = avl_double_rotate_with_right(t);
                }
        }

        t->height = avl_max(avl_height(t->left), avl_height(t->right)) + 1;
        return t;
}

static avl_position single_rotate_with_left(avl_position k2)
{
        avl_position k1;

        k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        
        k2->height = avl_max(avl_height(k2->left), avl_height(k2->right)) + 1;
        k1->height = avl_max(avl_height(k1->left), avl_height(k1->right)) + 1;
        return k1;
}

static avl_position double_rotate_with_left(avl_position k3)
{
        k3->left = avl_single_rotate_with_right(k3->left);
        return avl_single_rotate_with_left(k3);
}
#endif
