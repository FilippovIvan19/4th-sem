// realisation of all methods using in model structure

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define ERR_VAL -17562984

#define DEBUG_BY_PRINTF_OFF

#ifdef DEBUG_BY_PRINTF_OFF
  #define printf(x, ...) ;
#endif

typedef struct list list;
typedef struct node node;

struct node {
  data_type data;
  // principally on the first place for SIMPLE private access to features of node
  node* next;
  node* prev;
};

struct list {
  struct box methods;
  // here comes data (polymorphysm: after struct box comes data)
  int list_size;
  node* head;

  int id;
};



void list_destroy(box* box_p) { // ready
  list* list_p = (list*) box_p;
  node* p = list_p->head;
  while (p != NULL) {
    p = p->next;
    if (p != NULL) {
      free(p->prev);
    }
  }
  free(p);
  printf("list_destroy: list #%d has been deleted.\n", list_p->id);
  free(list_p); // equal to free(box_p) because of the same value of pointers
}

data_type list_size(box* box_p) {
  if (box_p == NULL) {
    printf("list_size: wrong list adress: %p\n", box_p);
    return ERR_VAL;
  }
    list* list_p = (list*) box_p;
    printf("list_size: list #%d: size = %d\n", list_p->id, list_p->list_size);
    return list_p->list_size;
}

node* _create_node(data_type value) {
  node* node_p = malloc(sizeof(node));
  if (node_p == NULL)
    return NULL;
  node_p->data = value;
  node_p->next = NULL;
  node_p->prev = NULL;
  return node_p;
}

data_type* list_getAddr(box* box_p, int index) {

  if (box_p == NULL) {
    printf("list_getAddr: incorrect list adress (%p). Return NULL\n", box_p);
    return NULL;
  }
  else if (index < -1) {
    printf("list_getAddr: incorrect index %d. Return NULL\n", index);
    return NULL;
  }


  //printf("list_getAddr: converting list adress: (%p) <=> ", box_p);
  list* list_p = (list*) box_p;
  //printf("(%p)\n", list_p);

  if (index >= list_p->list_size) {
    printf("list_getAddr: Index %d for list #%d exceeds its size! Return NULL.\n", index, list_p->id);
    return NULL;
  }

  int i = 0;
  node* node_p = list_p->head;

  while(i != index && node_p != NULL) { // moving head[0]->node[1]->node[2]...
    node_p = node_p->next;
    i++;
  }

  printf("list_getAddr: list #%d: got adress %p\n", list_p->id, node_p);
  if (node_p == NULL)
    printf("list_getAddr: list #%d is empty!\n", list_p->id);

  return (data_type*) node_p;
}

data_type list_get(box* box_p, int index) {
  list* list_p = (list*) box_p;
  if (list_p == NULL) {
    printf("list_get: wrong list adress: %p.\n", list_p);
  }
  data_type* value_p = list_getAddr(box_p, index);
  if (!value_p) {
    printf("list_get: list #%d: wrong index %d. Return ERR_VAL\n", list_p->id, index);
    return ERR_VAL;
  }
  printf("list_get: list #%d: got node[%d] = %d\n", list_p->id, index, *value_p);
  return *value_p;
}

void list_set(box* box_p, int index, data_type value) {
  // list* list_p = (list*) box_p;
  data_type* value_p = list_getAddr(box_p, index);
  if (value_p == NULL) {
    printf("list_set: list #%d: can't set value - wrong index %d\n", list_p->id, index);
    exit(-1);
  }
  else {
    *value_p = value;
    printf("list_set: list #%d: set node[%d] = %d.\n", list_p->id, index, *value_p);
  }

}

data_type* list_next(box* box_p, data_type* current) {
  list* list_p = (list*) box_p;
  if (list_p == NULL) {
    printf("list_next: incorect adress of list: (%p)! Return NULL.\n", list_p);
    return NULL;
  }
  if (current == NULL) {
    printf("list_next: list #%d: wrong node adress: %p. Return NULL.\n", list_p->id, current);
    return NULL;
  }
  node* node_p = (node*) current;
  node_p = node_p->next;
  printf("list_next: list #%d: next node adress: %p.\n", list_p->id, node_p);
  return (data_type*) node_p;
}

data_type* list_prev(box* box_p, data_type* current) {
  list* list_p = (list*) box_p;
  if (list_p == NULL) {
    printf("list_prev: incorect adress of list: (%p)! Return NULL.\n", list_p);
    return NULL;
  }
  if (current == NULL) {
    printf("list_prev: list #%d: wrong node adress: %p. Return NULL.\n", list_p->id, current);
    return NULL;
  }
  node* node_p = (node*) current;
  node_p = node_p->prev;
  printf("list_prev: list #%d: prev node adress: %p.\n", list_p->id, node_p);
  return (data_type*) node_p;
}

void list_insertAfterPointer (box* box_p, data_type* current, data_type value) {
  list* list_p = (list*) box_p;

  if (list_p == NULL) {
    printf("list_insertAfterPointer: incorrect adress of list: (%p)!\n", list_p);
    exit(-1);
  }

  //printf("list_insertAfterPointer: list #%d:  inserting data after node %p...\n", list_p->id, current);

  node* cur_node = (node*) current; // after that node (state) appears the new node
  node* new_node = _create_node(value); // create a new node
  node* next_node;

  if (new_node == NULL) {
    printf("list_insertAfterPointer: fail to allocate mem for new node!\n");
    exit(-1);
  }

  if (cur_node == NULL && list_p->head == NULL) {
    list_p->head = new_node;
    printf("list_insertAfterPointer: inserted #%d %d %p\tFIRST_HEAD.\n", list_p->id, new_node->data, new_node);
  }
  else if (cur_node == NULL) {
    next_node = list_p->head;
    list_p->head = new_node;
    (list_p->head)->next = next_node; // head-->next_node
    next_node->prev = list_p->head; // head<--next_node
    printf("list_insertAfterPointer: inserted #%d %d  :\t NEW_HEAD [%p]<->[%p] OLD_HEAD.\n", list_p->id, list_p->head->data, list_p->head, next_node);
  }
  else {
    node* next_node = cur_node->next; // save an old node comes after state (next state)

    // connecting: state <--> new node
    cur_node->next = new_node;
    new_node->prev = cur_node;

    //connecting: new node <--> next state (or tail = NULL)
    new_node->next = next_node;
    if (next_node)
      next_node->prev = new_node;
    printf("list_insertAfterPointer: inserted #%d %d  :\t [%p]<->[%p]<->[%p]\t INTERSECTION.\n", list_p->id, new_node->data, new_node->prev, new_node, new_node->next);
  }

  list_p->list_size++;
  printf("\tSucsess, new size = %d.\n", list_p->list_size);
}

void list_insertAfterIndex (box* box_p, int index, data_type value) {
  list* list_p = (list*) box_p;
  if (list_p == NULL) {
    printf("list_insertAfterIndex: incorect adress of list: (%p)!\n", list_p);
    exit(-1);
  }
  else if (index < -1) {
    printf("list_insertAfterIndex: incorect index for list #%d!\n", list_p->id);
    exit(-1);
  }

  data_type* state;
  if (index == -1) {
    state = NULL;
    //printf("here:%p\n", state);
  }
  else {
    state = list_getAddr(box_p, index);
    if (state == NULL) {
      printf("list_insertAfterIndex: current node (%p) hasn't been found.\n", state);
      exit(-1);
    }
  }

// new node_p will be placed after state
  list_insertAfterPointer (box_p, state, value);
}

void list_removeByPointer (box* box_p, data_type* current) {
  if (box_p == NULL) {
    printf("list_removeByPointer: wrong list adress: %p\n", box_p);
    exit(-1);
  }
  list* list_p = (list*) box_p;
  if (current == NULL) {
    printf("list_removeByPointer: list #%d: wrong list adress: %p.\n", list_p->id, current);
    exit(-1);
  }


  node* rm_node = (node*) current;
  node* prev_node = rm_node->prev;
  node* next_node = rm_node->next;

  printf("list_removeByPointer: list #%d: deleted node %p: ", list_p->id, rm_node);
  free(rm_node);

  if (prev_node != NULL)
    prev_node->next = next_node;
  if (next_node != NULL)
    next_node->prev = prev_node;

  list_p->list_size--;
  printf("%p <-...-> %p. new size = %d.\n", prev_node, next_node, list_p->list_size);
}

void list_removeByIndex (box *box_p, int index) {
  if (box_p == NULL) {
    printf("list_removeByIndex: wrong list adress: %p\n", box_p);
    exit(-1);
  }
  // list* list_p = (list*) box_p;
  node* rm_node = (node*) list_getAddr(box_p, index);
  if (rm_node == NULL) {
    printf("list_removeByIndex: list #%d: fail to get node adress: %p\n", list_p->id, rm_node);
  }
  list_removeByPointer(box_p, (data_type*) rm_node);
}

/*
  ADD_METHOD(destroy) = l->methods.destroy = list_destroy;
  destroy - pointer to void (*destroy)(box *box_p); in box.h;
  list_destroy - pointer to function
*/
#define ADD_METHOD(meth) l->methods.meth = list_##meth;

box* list_create() { // ready
  list* l =  malloc(sizeof(list));
  l->head = NULL;
  l->list_size = 0;

  ADD_METHOD(destroy)
  ADD_METHOD(size)
  ADD_METHOD(insertAfterIndex)
  ADD_METHOD(getAddr)
  ADD_METHOD(get)
  ADD_METHOD(set)
  ADD_METHOD(next)
  ADD_METHOD(prev)
  ADD_METHOD(insertAfterPointer)
  ADD_METHOD(removeByIndex)
  ADD_METHOD(removeByPointer)

  l->id = rand();
  printf("list_create: List #%d (adr = %p) has created!\n", l->id, l);
  printf("\tsize = %d, head = %p\n", l->list_size, l->head);

  return (box*) l;

  /*
    struct [box][data] -> return pointer to [box]
    now [data] is private, we can get it using type cast (list*)
  */
}
