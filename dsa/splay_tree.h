#ifndef _ST_H
#define _ST_H

struct st_node;
typedef struct st_node *splay_tree;
typedef struct st_node *st_position;

splay_tree st_make_empty(splay_tree t); // TODO
splay_tree st_find(splay_tree t);       // TODO
splay_tree st_find_min(splay_tree t);   // TODO
splay_tree st_find_max(splay_tree t);   // TODO
splay_tree st_initialize(void);
splay_tree st_insert(int x, splay_tree t);
splay_tree st_remove(int x, splay_tree t);
int st_retrieve(splay_tree t); // TODO
splay_tree st_splay(int item, st_position x);
st_position st_single_rotate_with_left(st_position p);  // TODO
st_position st_single_rotate_with_right(st_position p); // TODO
st_position st_double_rotate_with_left(st_position p);  // TODO
st_position st_double_rotate_with_right(st_position p); // TODO

struct st_node
{
        int element;
        splay_tree left;
        splay_tree right;
};

static st_position NULL_NODE = NULL;

splay_tree st_initialize(void)
{
        if (NULL_NODE == NULL)
        {
                NULL_NODE = (splay_tree)malloc(sizeof(struct st_node));
                if (NULL_NODE == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
        }
        return NULL_NODE;
}

splay_tree st_splay(int item, st_position x)
{
        static struct st_node header;
        st_position left_tree_max, right_tree_min;

        header.left = header.right = NULL_NODE;
        left_tree_max = right_tree_min = &header;

        while (item != x->element)
        {
                if (item < x->element)
                {
                        if (item < x->left->element)
                                x = st_single_rotate_with_left(x);
                        if (x->right == NULL_NODE)
                                break;
                        left_tree_max->right = x;
                        left_tree_max = x;
                        x = x->right;
                }
        }
        left_tree_max->right = x->left;
        right_tree_min->left = x->right;
        x->left = header.right;
        x->right = header.left;

        return x;
}

splay_tree st_insert(int item, splay_tree t)
{
        static st_position new_node = NULL;
        if (new_node == NULL)
        {
                new_node = (st_position)malloc(sizeof(struct st_node));
                if (new_node == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
        }
        new_node->element = item;

        if (t == NULL_NODE)
        {
                new_node->left = new_node->right = NULL_NODE;
                t = new_node;
        }
        else
        {
                t = st_splay(item, t);
                if (item < t->element)
                {
                        new_node->left = t->left;
                        new_node->right = t;
                        t->left = NULL_NODE;
                        t = new_node;
                }
                else if (t->element < item)
                {
                        new_node->right = t->right;
                        new_node->left = t;
                        t->right = NULL_NODE;
                        t = new_node;
                }
                else
                        return t;
        }

        new_node = NULL;
        return t;
}

splay_tree st_remove(int item, splay_tree t)
{
        st_position new_tree;

        if (t != NULL_NODE)
        {
                t = st_splay(item, t);
                if (item == t->element)
                {
                        if (t->left == NULL_NODE)
                                new_tree = t->right;
                        else
                        {
                                new_tree = t->left;
                                new_tree = st_splay(item, new_tree);
                                new_tree->right = t->right;
                        }
                        free(t);
                        t = new_tree;
                }
        }
        return t;
}

#endif
