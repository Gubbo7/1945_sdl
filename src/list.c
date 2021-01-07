#include "list.h"

List* NewList() {
    List* list = (List*)malloc(sizeof(List));
    list->__head = NULL;
    list->__tail = NULL;
    return list;
}

void DestroyList(List* list) {
    Node* each = list->__head;
    while(each != NULL) {
        Node* next = each->next;
        free(each);
        each = next;
    }
    free(list);
}

void AddToList(List* list, void* elem) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = elem;
    node->next = NULL;

    if (list->__head == NULL) {
        list->__head = node;
        list->__tail = node;
    } else {
        list->__tail->next = node;
        list->__tail = node;
    }
}