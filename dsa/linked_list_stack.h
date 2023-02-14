#ifndef _LLS_H
#define _LLS_H

struct lls_node;
typedef struct lls_node *p_lls_node;
typedef p_lls_node linked_list_stack;

int lls_is_empty(linked_list_stack s);
linked_list_stack lls_create(void);
void lls_dispose(linked_list_stack s); // TODO
void lls_make_empty(linked_list_stack s);
void lls_push(int x, linked_list_stack s);
int lls_top(linked_list_stack s); // TODO
void lls_pop(linked_list_stack s);

struct lls_node
{
        int element;
        p_lls_node next;
};

int lls_is_empty(linked_list_stack s)
{
        return s->next == NULL;
}

void lls_make_empty(linked_list_stack s)
{
        if (s == NULL)
        {
                perror("Must use lls_create first.");
                return;
        }
        else
                while (!lls_is_empty(s))
                        lls_pop(s);
}

linked_list_stack lls_create(void)
{
        linked_list_stack s = (linked_list_stack)malloc(sizeof(struct lls_node));
        if (s == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        s->next = NULL;
        lls_make_empty(s);
        return s;
}

void lls_push(int x, linked_list_stack s)
{
        p_lls_node tmp_cell;
        tmp_cell = (p_lls_node)malloc(sizeof(struct lls_node));
        if (tmp_cell == NULL)
        {
                perror("Out of space.");
                return;
        }
        else
        {
                tmp_cell->element = x;
                tmp_cell->next = s->next;
                s->next = tmp_cell;
        }
}

void lls_pop(linked_list_stack s)
{
        p_lls_node first_cell;
        if (lls_is_empty(s))
        {
                perror("Empty stack.");
                return;
        }
        else
        {
                first_cell = s->next;
                s->next = s->next->next;
                free(first_cell);
        }
}

#endif
