#ifndef _SL_H
#define _SL_H

struct sl_node;
typedef struct sl_node *skip_list;
typedef struct sl_node *sl_position;

struct sl_node
{
        int element;
        skip_list right;
        skip_list down;
};

static sl_position BOTTOM = NULL;
static sl_position TAIL = NULL;

skip_list sl_initialize(void);
sl_position sl_find(int item, skip_list l);
skip_list sl_insert(int item, skip_list l);

skip_list sl_initialize(void)
{
        skip_list l;

        if (BOTTOM == NULL)
        {
                BOTTOM = (struct sl_node *)malloc(sizeof(struct sl_node));
                if (BOTTOM == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
                BOTTOM->right = BOTTOM->down = BOTTOM;

                TAIL = (struct sl_node *)malloc(sizeof(struct sl_node));
                if (TAIL == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
                TAIL->element = 0; // Infinity
                TAIL->right = TAIL;
        }

        l = (struct sl_node *)malloc(sizeof(struct sl_node));
        if (l == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        l->element = 0; // Infinity
        l->right = TAIL;
        l->down = BOTTOM;
        return l;
}

sl_position sl_find(int item, skip_list l)
{
        sl_position current = l;
        BOTTOM->element = item;

        while (item != current->element)
        {
                if (item < current->element)
                        current = current->down;
                else
                        current = current->right;
        }
        return current;
}

skip_list sl_insert(int item, skip_list l)
{
        sl_position current = l;
        sl_position new_node;

        BOTTOM->element = item;
        while (current != BOTTOM)
        {
                while (item > current->element)
                        current = current->right;

                if (current->element > current->down->right->right->element)
                {
                        new_node = (struct sl_node *)malloc(sizeof(struct sl_node));
                        if (new_node == NULL)
                        {
                                perror("Out of space.");
                                return NULL;
                        }
                        new_node->right = current->right;
                        new_node->down = current->down->right->right;
                        current->right = new_node;
                        new_node->element = current->element;
                        current->element = current->down->right->element;
                }
                else
                        current = current->down;
        }

        if (l->right != TAIL)
        {
                new_node = (struct sl_node *)malloc(sizeof(struct sl_node));
                if (new_node == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
                new_node->down = l;
                new_node->right = TAIL;
                new_node->element = 0; // Infinity
                l = new_node;
        }
        return l;
}
#endif
