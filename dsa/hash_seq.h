#ifndef _HS_H
#define _HS_H

#define HS_MIN_TABLE_SIZE 10000

struct hs_list_node;
typedef struct hs_list_node *hs_position;
struct hs_table;
typedef struct hs_table *p_hs_table;

p_hs_table hs_initialize(int table_size);
void hs_destroy_(p_hs_table h); // TODO
hs_position hs_find(int key, p_hs_table h);
void hs_insert(int key, p_hs_table h);
int hs_retrieve(hs_position p); // TODO
int hs_next_prime(int x);             // TODO
int hs_hash(int key, int table_size); // TODO

struct hs_list_node
{
        int element;
        hs_position next;
};

typedef hs_position hs_list;

struct hs_table
{
        int table_size;
        hs_list *the_lists;
};

p_hs_table hs_initialize(int table_size)
{
        p_hs_table h;
        int i;

        if (table_size < hs_MIN_TABLE_SIZE)
        {
                perror("Table size too small.");
                return NULL;
        }

        h = (p_hs_table)malloc(sizeof(struct hs_table));
        if (h == NULL)
        {
                perror("Out of space.");
                return NULL;
        }

        h->table_size = hs_next_prime(table_size);
        h->the_lists = (hs_list *)malloc(sizeof(hs_list));
        if (h->the_lists == NULL)
        {
                perror("Out of space.");
                free(h);
                return NULL;
        }

        for (i = 0; i < h->table_size; i++)
        {
                h->the_lists[i] = (struct hs_list_node *)malloc(sizeof(struct hs_list_node));
                if (h->the_lists[i] == NULL)
                {
                        perror("Out of space.");
                        free(h->the_lists);
                        free(h);
                        return NULL;
                }
                else
                        h->the_lists[i]->next = NULL;
        }

        return h;
}

hs_position hs_find(int key, p_hs_table h)
{
        hs_position p;
        hs_list l;

        l = h->the_lists[hs_hash(key, h->table_size)];
        p = l->next;

        while (p != NULL && p->element != key)
                p = p->next;

        return p;
}

void hs_insert(int key, p_hs_table h)
{
        hs_position pos, new_cell;
        hs_list l;
        pos = hs_find(key, h);
        if (pos == NULL)
        {
                new_cell = (struct hs_list_node *)malloc(sizeof(struct hs_list_node));
                if (new_cell == NULL)
                {
                        perror("Out of space.");
                        return;
                }
                else
                {
                        l = h->the_lists[hs_hash(key, h->table_size)];
                        new_cell->next = l->next;
                        new_cell->element = key;
                        l->next = new_cell;
                }
        }
}
#endif
