#ifndef _AS_H
#define _AS_H

struct as_record;
typedef struct as_record *array_stack;

int as_is_empty(array_stack s);
int as_is_full(array_stack s);     // TODO
array_stack as_create(int max_elements);
void as_dispose(array_stack s);
void as_make_empty(array_stack s);
void as_push(int x, array_stack s);
int as_top(array_stack s);
void as_pop(array_stack s);
int as_top_and_pop(array_stack s);       // TODO

#define as_EMPTY_TO_S -1
#define as_MIN_STACK_SIZE 5

struct as_record
{
        int capacity;
        int top_of_stack;
        int *array;
};

array_stack as_create(int max_elements)
{
        array_stack s;
        if (max_elements < as_MIN_STACK_SIZE)
        {
                perror("Stack size is too small");
                return NULL;
        }

        s = (array_stack)malloc(sizeof(struct as_record));
        if (s == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        s->array = (int *)malloc(sizeof(int) * max_elements);
        if (s->array == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        s->capacity = max_elements;
        as_make_empty(s);
        return s;
}

void as_dispose_stack(array_stack s)
{
        if (s != NULL) {
                free(s->array);
                free(s);
        }
}

int as_is_empty(array_stack s)
{
        return s->top_of_stack = as_EMPTY_TO_S;
}

void as_make_empty(array_stack s)
{
        s->top_of_stack = as_EMPTY_TO_S;
}

void as_push(int x, array_stack s)
{
        if (as_is_full(s))
        {
                perror("Full stack.");
                return;
        }
        else
                s->array[++s->top_of_stack] = x;
}

int as_top(array_stack s)
{
        if (!as_is_empty(s)) return s->array[s->top_of_stack];
        perror("Empty stack.");
        return 0;
}

void as_pop(array_stack s) 
{
        if (as_is_empty(s))
        {
                perror("Empty stack.");
                return;
        }
        else
                s->top_of_stack--;
}

#endif
