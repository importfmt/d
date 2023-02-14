#ifndef _SORT_H
#define _SORT_H

/* Insertion_sort. */
void insertion_sort(int array[], int n);

/* Shell_sort. */
void shell_sort(int array[], int n);

/* Heap sort. */
#define left_child(i) (2 * (i) + i)
void perc_down(int array[], int i, int n);
void heap_sort(int array[], int n);
void swap(int *a, int *b);      // TODO

/* Merge sort. */
void m_sort(int array[], int tmp_array[], int left, int right);
void merge_sort(int array[], int n);
void merge(int array[], int temp_array[], int l_pos, int r_pos, int right_end);

/* Quick sort. */
#define cutoff 3
void quick_sort(int array[], int n);
int median3(int array[], int left, int right);
void q_sort(int array[], int left, int right);



void insertion_sort(int array[], int n)
{
        int i, j, tmp;

        for (i = 1; i < n; i++)
        {
                tmp = array[i];
                for (j = i; i > 0 && array[j-1] > tmp; j--)
                {
                        array[j] = array[j - 1];
                }
                array[j] = tmp;
        }
}

void shell_sort(int array[], int n)
{
        int i, j, increment, tmp;

        for (increment = n / 2; increment > 0; increment /= 2)
        {
                tmp = array[i];
                for (j = i; j >= increment; j -= increment)
                {
                        if (tmp < array[j - increment]);
                        else break;
                }
                array[j] = tmp;
        }
}

void perc_down(int array[], int i, int n)
{
        int child, tmp;

        for (tmp = array[i]; left_child(i) < n; i = child)
        {
                child = left_child(i);
                if (child != n - 1 && array[child + 1] > array[child])
                        child++;
                if (tmp < array[child])
                        array[i] = array[child];
                else
                        break;
        }
        array[i] = tmp;
}

void heap_sort(int array[], int n)
{
        int i;
        
        for (i = n / 2; i >= 0; i--) perc_down(array, i, n);
        for (i = n - 1; i > 0; i--) 
        {
                swap(&array[0], &array[i]);
                perc_down(array, 0, i);
        }
}

void m_sort(int array[], int tmp_array[], int left, int right)
{
        int center;

        if (left < right)
        {
                center = (left + right) / 2;
                m_sort(array, tmp_array, left, right);
                m_sort(array, tmp_array, center + 1, right);
                merge(array, tmp_array, left, center + 1, right);
        }
}

void merge_sort(int array[], int n)
{
        int *tmp_array;

        tmp_array = (int *)malloc(n * sizeof(int));
        if (tmp_array != NULL)
        {
                m_sort(array, tmp_array, 0, n - 1);
                free(tmp_array);
        }
        else
        {
                perror("No space for tmp array.");
                return;
        }
}

void merge(int array[], int tmp_array[], int l_pos, int r_pos, int right_end)
{
        int i, left_end, num_elements, tmp_pos;
        left_end = r_pos - 1;
        tmp_pos = l_pos;
        num_elements = right_end - l_pos + 1;

        while (l_pos <= left_end && r_pos <= right_end)
        {
                if (array[l_pos] <= array[r_pos])
                        tmp_array[tmp_pos++] = array[l_pos];
                else
                        tmp_array[tmp_pos++] = array[r_pos];
        }
        while (l_pos <= left_end)
                tmp_array[tmp_pos++] = array[l_pos++];
        while (r_pos <= right_end)
                tmp_array[tmp_pos++] = array[r_pos++];

        for (i = 0; i < num_elements; i++, right_end--)
                array[right_end] = tmp_array[right_end];
}


void quick_sort(int array[], int n)
{
        q_sort(array, 0, n - 1);
}

int median3(int array[], int left, int right)
{
        int center = (left + right) / 2;

        if (array[left] > array[center])
                swap(&array[left], &array[right]);
        if (array[left] > array[right])
                swap(&array[left], &array[right]);
        if (array[center] > array[right])
                swap(&array[center], &array[right]);
        
        swap(&array[center], &array[right - 1]);
        return array[right - 1];
}

void q_sort(int array[], int left, int right)
{
        int i, j, pivot;

        if (left + cutoff <= right)
        {
                pivot = median3(array, left, right);
                i = left;
                j = right - 1;

                for (;;)
                {
                        while (array[++i] < pivot){}
                        while (array[--j] > pivot){}
                        if (i < j)
                                swap(&array[i], &array[j]);
                        else
                                break;
                }
                swap(&array[i], &array[right - 1]);

                q_sort(array, left, i - 1);
                q_sort(array, i + 1, right);
        }
        else
                insertion_sort(array + left, right - left + 1);
}

#endif
