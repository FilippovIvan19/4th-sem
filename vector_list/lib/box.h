// contains declaration of global methods for objects
#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct box box;
typedef int data_type;

struct box
{
    void (*destroy)(box *box_p);

    data_type  (*size)               (box *box_p);
    data_type  (*get)                (box *box_p, int index);
    void       (*set)                (box *box_p, int index, data_type value);
    data_type *(*prev)               (box *box_p, data_type *current);
    data_type *(*next)               (box *box_p, data_type *current);
    data_type *(*getAddr)            (box *box_p, int index);
    void       (*insertAfterIndex)   (box *box_p, int index, data_type value);
    void       (*insertAfterPointer) (box *box_p, data_type *current, data_type value);
    void       (*removeByIndex)      (box *box_p, int index);
    void       (*removeByPointer)    (box *box_p, data_type *current);
};
