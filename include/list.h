#ifndef LIST_H
#define LIST_H
#include "common.h"

struct node {
    void* data;
    struct node* next;
};
typedef struct node Node;

struct list {
    Node* __head;
    Node* __tail;
};
typedef struct list List;

List* NewList();
void DestroyList(List* list);
void AddToList(List* list, void* elem);


#endif /* LIST_H */