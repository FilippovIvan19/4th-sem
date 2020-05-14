#include <stdio.h>
#include "lib/vector.h"
#include "lib/list.h"
#include <time.h> 


void enter_sort(box* v)
{
    for (int i = 1; i < v->size(v); i++)
        for (int j = i; j > 0 && v->get(v, j-1) > v->get(v, j); j--)
        {
            data_type tmp = v->get(v, j);
            v->set(v, j, v->get(v, j - 1));
            v->set(v, j - 1, tmp);
        }
}

void bubl_sort(box* v)
{
    for (int i = 0; i < v->size(v) - 1; i++)
        for (int j = 0; j < v->size(v) - i - 1; j++)
            if (v->get(v, j) > v->get(v, j + 1))
            {
                data_type tmp = v->get(v, j);
                v->set(v, j, v->get(v, j + 1));
                v->set(v, j + 1, tmp);
            }
}

void print_box(box* v)
{
    for (size_t i = 0; i < v->size(v); i++)
        printf("%2d ", v->get(v, i));
    printf("\n");
}

void fill_box(box* v, int count)
{
    for (int i = 0; i < count; i++)
        v->insertAfterIndex(v, i-1, ((int) rand()) % 100);
}


int main(int argc, char const *argv[])
{
    srand(time(0));

    box *v = vector_create();
    fill_box(v, 20);
    print_box(v);
    bubl_sort(v);
    print_box(v);
    v->destroy(v);

    v = vector_create();
    fill_box(v, 20);
    print_box(v);
    enter_sort(v);
    print_box(v);
    v->destroy(v);

    v = list_create();
    fill_box(v, 20);
    print_box(v);
    bubl_sort(v);
    print_box(v);
    v->destroy(v);

    v = list_create();
    fill_box(v, 20);
    print_box(v);
    enter_sort(v);
    print_box(v);
    v->destroy(v);



    return 0;
}
