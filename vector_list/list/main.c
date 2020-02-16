#include <stdio.h>
#include "list.h"
//#include "vector.h"

void enter_sort(box* v) {
  for (int i = 1; i < v->size(v); i++)
      for (int j = i; j > 0 && v->get(v, j-1) > v->get(v, j); j--)

          {
              data_type tmp = v->get(v, j);
              v->set(v, j, v->get(v, j - 1));
              v->set(v, j - 1, tmp);
          }
}

int main(int argc, char const *argv[]) {
  //generate list
    box *v = list_create();
    for (int i = 0; i < 100; i++) {
      v->insertAfterIndex(v, i-1, 0);
      v->set(v, i, ((int) rand()) % 100);
      v->get(v, i);
    }

    printf("\n\n\n");
    // sort list
    enter_sort(v);
    printf("\n\n\n");
    printf("\n\n\n");
// show soretd list
    for (size_t i = 0; i < v->size(v); i++)
        printf("%d ", v->get(v, i));
    printf("\n");

    v->destroy(v);

  return 0;
}
