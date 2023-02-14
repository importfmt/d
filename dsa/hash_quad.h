#ifndef _HQ_H
#define _HQ_H

#define HQ_MIN_TABLE_SIZE 10000

typedef unsigned int hq_position;
struct hq_table;
typedef struct hq_table *p_hq_table;

p_hq_table hq_initialize(int table_size);
void hq_destroy_hash(p_hq_table h); // TODO
hq_position hq_find(int key, p_hq_table h);
void hq_insert(int key, p_hq_table h);
p_hq_table hq_rehash(p_hq_table h);
int hq_next_prime(int x);             // TODO
int hq_hash(int key, int table_size); // TODO

enum hq_kind_of_entry
{
        legitimate,
        empty,
        deleted
};

struct hq_entry
{
        int element;
        enum hq_kind_of_entry info;
};

typedef struct hq_entry hq_cell;

struct hq_table
{
        int table_size;
        hq_cell *the_cells;
};

p_hq_table hq_initialize(int table_size)
{
        p_hq_table h;
        int i;

        if (table_size < hq_MIN_TABLE_SIZE)
        {
                perror("Table size too small.");
                return NULL;
        }

        h = (p_hq_table)malloc(sizeof(struct hq_table));
        if (h == NULL)
        {
                perror("Out of space.");
                return NULL;
        }

        h->table_size = hq_next_prime(table_size);
        h->the_cells = (hq_cell *)malloc(sizeof(hq_cell) * h->table_size);
        if (h->the_cells == NULL)
        {
                perror("Out of space.");
                free(h);
                return NULL;
        }

        for (i = 0; i < h->table_size; i++)
        {
                h->the_cells[i].info = empty;
        }

        return h;
}

hq_position hq_find(int key, p_hq_table h)
{
        hq_position current_pos;
        int collision_num;

        collision_num = 0;
        current_pos = hq_hash(key, h->table_size);

        while (h->the_cells[current_pos].info != empty &&
               h->the_cells[current_pos].element != key)
        {
                current_pos += 2 * ++collision_num - 1;
                if (current_pos >= h->table_size)
                        current_pos -= h->table_size;
        }
        return current_pos;
}

void hq_insert(int key, p_hq_table h)
{
        hq_position pos;

        pos = hq_find(key, h);
        if (h->the_cells[pos].info != legitimate)
        {
                h->the_cells[pos].info = legitimate;
                h->the_cells[pos].element = key;
        }
}

p_hq_table hq_rehash(p_hq_table h)
{
        int i, old_size;
        hq_cell *old_cells;

        old_cells = h->the_cells;
        old_size = h->table_size;

        h = hq_initialize(2 * old_size);
        for (i = 0; i < old_size; i++)
        {
                if (old_cells[i].info == legitimate)
                        hq_insert(old_cells[i].element, h);
        }
        free(old_cells);
        return h;
}

#endif
