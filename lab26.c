#include <stdlib.h>
#include <stdio.h>

#include "Deck.h" 

void udt_delete_max(udt* x) {

    int size = udt_size(x);

    if (size == 0) { return; }

    if (size == 1) { udt_pop_front(x); return; }

    int* tmp = (int*)calloc(size, sizeof(int));

    int max = x->front;
    int key = (size - 1);

    for (int i = 1; i <= size; i++)
    {
        tmp[size - i] = x->front;

        if (max < tmp[size - i]) {

            max = tmp[size - i];
            key = (size - i);

        }

        udt_pop_front(x);
    }

    for (int i = 0; i < key; ++i)
    {
        udt_push_front(x, tmp[i]);
    }

    for (int i = key + 1; i < size; ++i)
    {
        udt_push_front(x, tmp[i]);
    }

    free(tmp);
}

void udt_sort(udt* x) {

    int size = udt_size(x);

    if (size == 0) { return; }

    if (size == 1) { return; }

    int* tmp = (int*)calloc(size, sizeof(int));

    for (int i = 1; i <= size; i++)
    {
        tmp[size - i] = x->front;
        udt_pop_front(x);
    }

    for (int i = 0; i < size; i++)
    {
        int min = tmp[size - 1];
        int key = (size - 1);

        for (int j = i; j < size; j++)
        {

            if (min > tmp[j]) {

                min = tmp[j];
                key = j;

            }
        }

        int t = tmp[i];

        tmp[i] = min;

        tmp[key] = t;

    }

    for (int k = 0; k < size; ++k)
    {
        udt_push_front(x, tmp[k]);
    }

    free(tmp);
}

int main()
{
    udt x;
    udt_create(&x);

    udt_print(&x);

    for (int i = 0; i < 11; ++i)
    {
        udt_push_front(&x, (i * (-1)));

        udt_print(&x);
    }

    for (int i = 0; i < 11; ++i)
    {
        udt_push_back(&x, i);

        udt_print(&x);
    }

    udt_delete_max(&x);

    udt_print(&x);

    for (int i = 0; i < 8; i++)
    {
        udt_pop_front(&x);

        udt_print(&x);

        udt_pop_back(&x);

        udt_print(&x);

    }

    udt_push_back(&x, 30);

    udt_print(&x);

    udt_sort(&x);

    udt_print(&x);

    udt_delete_max(&x);

    udt_print(&x);
}