// #pragma once
#include <string.h>
#include "vector.h"

typedef struct vector vector;
#define INIT_CAP 16
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


#define $(x) printf(#x " = %d\n", x);

struct vector
{
    box methods;
    int capacity;
    int cur_size;
    data_type *data;
};

void _vector_resize(box *box_p, short direction)
{
    vector* this = (vector*)box_p;
    if (direction < 0)
        this->capacity /= 2;
    else
        this->capacity *= 2;
    // $(this->capacity)
    this->data = realloc(this->data, this->capacity * sizeof(data_type));
}

void vector_destroy(box *box_p)
{
    vector* this = (vector*)box_p;
    free(this->data);
    free(box_p);
}

data_type vector_size(box *box_p)
{
    vector* this = (vector*)box_p;
    return this->cur_size;
}

data_type vector_get(box *box_p, int index)
{
    vector* this = (vector*)box_p;
    return this->data[index];
}

void vector_set(box *box_p, int index, data_type value)
{
    vector* this = (vector*)box_p;

    while (index >= this->capacity)
        _vector_resize(box_p, 1);

    this->data[index] = value;
    this->cur_size = MAX(this->cur_size, index + 1);
}

data_type *vector_next(box *box_p, data_type *current)
{
    vector* this = (vector*)box_p;
    int index = current - this->data;
    if (index < this->cur_size - 1 && index >= 0)
        return current + 1;
    else
        return NULL;
}

data_type *vector_prev(box *box_p, data_type *current)
{
    vector* this = (vector*)box_p;
    int index = current - this->data;
    if (index < this->cur_size && index > 0)
        return current - 1;
    else
        return NULL;
}

data_type *vector_getAddr(box *box_p, int index)
{
    vector* this = (vector*)box_p;
    return this->data + index;
}

void vector_insertAfterIndex(box *box_p, int index, data_type value)
{
    vector* this = (vector*)box_p;

    while (index >= this->capacity || this->cur_size >= this->capacity)
        _vector_resize(box_p, 1);

    if (this->cur_size - index - 1 > 0)
    {
        memmove (this->data + index + 2, this->data + index + 1,
            (this->cur_size - index - 1) * sizeof(data_type));
        // printf("memmove\n");
    }

    this->data[index + 1] = value;
    // $(this->cur_size)
    // $(index + 1)
    // $(MAX(this->cur_size, index + 1))
    this->cur_size = MAX(this->cur_size, index + 1) + 1;
    // $(this->cur_size)
    // for (size_t i = 0; i < 4; i++)
    //     printf("%d ", this->data[i]);
    // printf("\n%d\n", this->cur_size);
}

void vector_insertAfterPointer(box *box_p, data_type *current, data_type value)
{
    vector* this = (vector*)box_p;

    int index;
    if (current == NULL)
        index = -1;
    else
        index = current - this->data;
    
    this->methods.insertAfterIndex(box_p, index, value);
}

void vector_removeByIndex(box *box_p, int index)
{
    vector* this = (vector*)box_p;

    if (index >= this->cur_size || index < 0)
        return;

    memmove (this->data + index, this->data + index + 1,
        (this->cur_size - index - 1) * sizeof(data_type));
    this->cur_size--;
    if (this->cur_size * 4 < this->capacity)
        _vector_resize(box_p, -1);
}

void vector_removeByPointer(box *box_p, data_type *current)
{
    vector* this = (vector*)box_p;
    if (current == NULL)
        return;
    int index = current - this->data;
    this->methods.removeByIndex(box_p, index);
}



#define ADD_METHOD(meth) this->methods.meth = vector_##meth;

box *vector_create()
{
    vector *this = calloc(1, sizeof(vector));
    this->data = calloc(INIT_CAP, sizeof(data_type));
    this->cur_size = 0;
    this->capacity = INIT_CAP;

    ADD_METHOD(size)
    ADD_METHOD(destroy)
    ADD_METHOD(getAddr)
    ADD_METHOD(get)
    ADD_METHOD(set)
    ADD_METHOD(next)
    ADD_METHOD(prev)
    ADD_METHOD(insertAfterIndex)
    ADD_METHOD(insertAfterPointer)
    ADD_METHOD(removeByIndex)
    ADD_METHOD(removeByPointer)

    return (box*)this;
}