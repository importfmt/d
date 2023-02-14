#ifndef _BH_H
#define _BH_H
#define MIN_PQ_SIZE 100 /* min priority queue size. */

struct binary_heap;
typedef struct binary_heap *bh_priority_queue;

bh_priority_queue binaray_heap_initialize(int max_elements);
void bh_destroy(bh_priority_queue h);     // TODO
void bh_make_empty(bh_priority_queue h);  // TODO
void bh_insert(int x, bh_priority_queue h);
int bh_delete_min(bh_priority_queue h);
int bh_find_min(bh_priority_queue h);     // TODO
int bh_is_empty(bh_priority_queue h);     // TODO
int bh_is_full(bh_priority_queue h);      // TODO

struct binary_heap
{
        int capacity;
        int size;
        int *elements;
};

bh_priority_queue initialize(int max_elements)
{
        bh_priority_queue h;

        if (max_elements < MIN_PQ_SIZE)
        {
                perror("Priority queue size is too small.");
                return NULL;
        }

        h = (bh_priority_queue)malloc(sizeof(struct binary_heap));
        if (h == NULL)
        {
                perror("Out of space.");
                return NULL;
        }

        h->elements = (int *)malloc((max_elements + 1) * sizeof(int));
        if (h->elements == NULL)
        {
                perror("Out of space.");
                return NULL;
        }

        h->capacity = max_elements;
        h->size = 0;
        h->elements[0] = 0;     /* Here need modify 0 to min data. */
        
        return h;
}

void bh_insert(int x, bh_priority_queue h)
{
        int i;

        if (bh_is_full(h))
        {
                perror("Pirority queue is full.");
                return;
        }

        for (i = ++h->size; h->elements[i / 2] > x; i /= 2)
                h->elements[i] = h->elements[i / 2];
        h->elements[i] = x;
}

int bh_delete_min(bh_priority_queue h)
{
        int i, child;
        int min_element, last_element;

        if (bh_is_empty(h))
        {
                perror("Priority queue is empty.");
                return h->elements[0];
        }

        min_element = h->elements[1];   /* Root node */
        last_element = h->elements[h->size--];

        for (i = 1; i * 2 <= h->size; i = child)
        {
                child = i * 2;
                if (child != h->size && h->elements[child+1] < h->elements[child])
                        child++;
                
                if (last_element > h->elements[child])
                        h->elements[i] = h->elements[child];
                else
                        break;
        }

        h->elements[i] = last_element;
        return min_element;
}

#endif
