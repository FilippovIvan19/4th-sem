#include "vector.h"
// #include "list.h"


int main(int argc, char const *argv[])
{
    // box l = list_create();
    // v->insertAfterIndex(v, -1, 5);
    // v->insertAfterIndex(v, 0, 7);
    // v->insertAfterIndex(v, 1, 12);
    // v->insertAfterIndex(v, -1, 6);

    // v->getAddr(v, 0);

    // v->insertAfterPointer(v, NULL, 5);
    // v->insertAfterPointer(v, v->getAddr(v, 0), 7);
    // v->insertAfterPointer(v, v->getAddr(v, 1), 12);
    // v->insertAfterPointer(v, v->getAddr(v, 2), 6);



    // v->insertAfterPointer(v, v->getAddr(v, 0), 16);
    // v->insertAfterIndex(v, 0, 17);

    // v->set(v, 0, 5);
    // v->set(v, 1, 6);
    // v->set(v, 2, 7);
    // v->set(v, 3, 8);
    // v->set(v, 4, 9);
    // v->set(v, 5, 10);
    // v->set(v, 7, 11);

    // for (size_t i = 0; i < 16; i++)
    //     printf("%d ", v->get(v, i));
    // printf("\n%d\n", v->size(v));

    // v->removeByIndex(v, 4);

    // for (size_t i = 0; i < 16; i++)
    //     printf("%d ", v->get(v, i));
    // printf("\n%d\n", v->size(v));

    // v->removeByPointer(v, v->getAddr(v, 2));

    // for (size_t i = 0; i < 16; i++)
    //     printf("%d ", v->get(v, i));
    // printf("\n%d\n", v->size(v));
    
    // printf("%d\n", *(v->prev(v, v->getAddr(v, 3))));


    box *v = vector_create();

    v->set(v, 0, 0);
    v->set(v, 1, 5);
    v->set(v, 2, 3);
    v->set(v, 3, 6);
    v->set(v, 4, 2);
    v->set(v, 5, 1);
    v->set(v, 6, 4);



    for (size_t i = 0; i < v->size(v); i++)
        printf("%d ", v->get(v, i));
    printf("\n");

    for (int i = 0; i < v->size(v) - 1; i++)
        for (int j = 0; j < v->size(v) - i - 1; j++)
            if (v->get(v, j) > v->get(v, j + 1))
            {
                data_type tmp = v->get(v, j);
                v->set(v, j, v->get(v, j + 1));
                v->set(v, j + 1, tmp);
            }

    for (size_t i = 0; i < v->size(v); i++)
        printf("%d ", v->get(v, i));
    printf("\n");

    v->destroy(v);

    return 0;
}
