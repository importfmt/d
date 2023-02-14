#ifndef _RBT_H
#define _RBT_H

typedef enum color_type
{
        red,
        black
} color_type;

struct rbt_node;
typedef struct rbt_node *red_black_tree;
typedef struct rbt_node *rbt_position;
rbt_position NULL_NODE = NULL;

red_black_tree rbt_initialization(void);
static rbt_position rbt_rotate(int item, rbt_position parent);
rbt_position rbt_single_rotate_with_left(rbt_position p);  // TODO
rbt_position rbt_single_rotate_with_right(rbt_position p); // TODO
/* x: current node
** p: parent node
** gp: grandparent node
** ggp: grandgrandparent node ?
*/
static rbt_position x, p, gp, ggp;
static void rbt_handler_reorient(int item, red_black_tree t);
red_black_tree rbt_insert(int item, red_black_tree t);

struct rbt_node
{
        int element;
        red_black_tree left;
        red_black_tree right;
        color_type color;
};

red_black_tree rbt_initialization(void)
{
        red_black_tree t;
        if (NULL_NODE == NULL)
        {
                NULL_NODE = (struct rbt_node *)malloc(sizeof(struct rbt_node));
                if (NULL_NODE == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
                NULL_NODE->left = NULL_NODE->right = NULL_NODE;
                NULL_NODE->color = black;
                NULL_NODE->element = 0; // Infinity;
        }

        t = (struct rbt_node *)malloc(sizeof(struct rbt_node));
        if (t == NULL)
        {
                perror("Out of space.");
                return NULL;
                t->element = 0; // NegInfinity;
                t->left = t->right = NULL_NODE;
                t->color = black;
        }
        return t;
}

static rbt_position rbt_rotate(int item, rbt_position parent)
{
        if (item < parent->element)
                return parent->left = item < parent->left->element ? rbt_single_rotate_with_left(parent->left) : rbt_single_rotate_with_right(parent->left);
        else
                return parent->right = item < parent->right->element ? rbt_single_rotate_with_left(parent->right) : rbt_single_rotate_with_right(parent->right);
}

static void rbt_handler_reorient(int item, red_black_tree t)
{
        x->color = red;
        x->left->color = black;
        x->right->color = black;

        if (p->color == red)
        {
                gp->color = red;
                if (item < gp->element != (item < p->element))
                        p = rbt_rotate(item, gp);
                x = rbt_rotate(item, ggp);
                x->color = black;
        }
        t->right->color = black;
}

red_black_tree rbt_insert(int item, red_black_tree t)
{
        x = p = gp = t;
        NULL_NODE->element = item;
        while (x->element != item)
        {
                ggp = gp;
                gp = p;
                p = x;
                if (item < x->element)
                        x = x->left;
                else
                        x = x->right;
                if (x->left->color == red && x->right->color == red)
                        ;
                rbt_handler_reorient(item, t);
        }

        if (x != NULL_NODE)
                return NULL_NODE;
        x = (struct rbt_node *)malloc(sizeof(struct rbt_node));
        if (x == NULL)
        {
                perror("Out of space.");
                return NULL_NODE;
        }
        x->element = item;
        x->left = x->right = NULL_NODE;

        if (item < p->element)
                p->left = x;
        else
                p->right = x;

        rbt_handler_reorient(item, t);

        return t;
}

#endif
