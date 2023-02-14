#ifndef _LL_H
#define _LL_H

struct ll_node;
typedef struct ll_node *P_ll_node;
typedef P_ll_node linked_list;
typedef P_ll_node ll_position;

struct ll_node
{
        int element;
        ll_position next;
};

linked_list ll_make_empty(linked_list l); // TODO
int ll_is_empty(linked_list l);
int ll_is_last(ll_position p, linked_list l);
ll_position linkd_list_find(int x, linked_list l);
void ll_delete(int x, linked_list l);
ll_position ll_find_previous(int x, linked_list l);
void ll_insert(int x, linked_list l, ll_position p);
void ll_delete_list(linked_list l);                      // TODO
ll_position ll_header(linked_list l);           // TODO
ll_position ll_first(linked_list l);            // TODO
ll_position ll_advance(ll_position p); // TODO
int ll_retrieve(ll_position p);                 // TODO

int ll_is_empty(linked_list l)
{
        return l->next == NULL;
}

int ll_is_last(ll_position p, linked_list l)
{
        return p->next == NULL;
}

ll_position linkd_list_find(int x, linked_list l)
{
        ll_position p;
        p = l->next;
        while (p != NULL && p->element != x)
                p = p->next;
        return p;
}

ll_position ll_find_previous(int x, linked_list l)
{
        ll_position p;
        p = l;

        while (p->next != NULL && p->next->element != x)
                p = p->next;
        return p;
}

void ll_delete(int x, linked_list l)
{
        ll_position p, tmp_cell;
        p = ll_find_previous(x, l);
        if (!ll_is_last(p, l))
        {
                tmp_cell = p->next;
                p->next = tmp_cell->next;
                free(tmp_cell);
        }
}

void ll_insert(int x, linked_list l, ll_position p)
{
        ll_position tmp_cell;

        tmp_cell = malloc(sizeof(struct ll_node));
        if (tmp_cell == NULL)
        {
                perror("Out of space.");
                return;
        }
        tmp_cell->element = x;
        tmp_cell->next = p->next;
        p->next = tmp_cell;
}

#endif
