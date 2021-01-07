#include "aiv-vector.h"

avector* aiv_vector_new() {
    return aiv_vector_new_with_cap(10);
}

avector* aiv_vector_new_with_cap(uint capacity) {
    avector* vect = (avector*)malloc(sizeof(avector));
    if (vect == NULL) return NULL;
    vect->__count = 0;  // -> is like: (*vect).count = 0;
    vect->__capacity = capacity;
    vect->__items = malloc(vect->__capacity * sizeof(void*));
    if (vect->__items == NULL) return NULL;
    return vect;
}

void aiv_vector_destroy(avector* vect) {
    vect->__count = 0;
    free(vect->__items);
    free(vect);
}

void aiv_vector_add(avector* vect, void* item) {
    if (vect->__count == vect->__capacity) {
        aiv_vector_resize(vect, vect->__capacity * 2);
    }

    int curr_index = vect->__count;
    vect->__items[curr_index] = item;
    vect->__count++;
}

void* aiv_vector_at(avector* vect, uint index) {
    if (index >= vect->__count) return NULL;
    return vect->__items[index];
}

avector* aiv_vector_resize(avector* vect, uint capacity) {
    void* ptr = realloc(vect->__items, capacity * sizeof(void*));
    if (ptr == NULL) return NULL;
    vect->__items = ptr;
    vect->__capacity = capacity;
    return vect;
}

void aiv_vector_foreach(avector* vect, void (*action)(void* elem)) {
    for(size_t i=0; i < vect->__count; i++) {
        action(vect->__items[i]);
    }
}

bool aiv_vector_is_empty(avector* vect){
    if(vect->__count == 0){   //Null e 0 non sono come in C#, so diversi dio  porco
        return true;
    }
    else return false;
}

uint aiv_vector_size(avector* vect){
    return vect->__count;    
}

void aiv_vector_set(avector* vect, int index, void* elem){
    vect->__items[index] = elem;    
}

void aiv_vector_add_all(avector* vect, avector* other){
    for (size_t i = 0; i < other->__count; i++)
    {
       aiv_vector_add(vect, other->__items[i]);
    }
}

void aiv_vector_remove_at(avector* vect, int index){
    if(index >= vect->__count){
        aiv_vector_resize(vect,vect->__capacity * 2);
    }

    for (size_t i = 0; i < vect->__count - 1; i++)
    {
        if(i >= index){
            vect->__items[i] = vect->__items[i + 1];   
        }
    }
    vect->__count--;
}

void aiv_vector_insert_at(avector* vect, int index, void* elem){
    vect->__count++;
    if(index >= vect->__count && vect->__count == vect->__capacity){
        aiv_vector_resize(vect,vect->__capacity * 2);
    }
    
    for (size_t i = vect->__count; i > 0; i--)
    {
        if(i > index){
            
            vect->__items[i] = vect->__items[i - 1];
        }
        
        if(i == index){
            vect->__items[index] = elem;
        }

        if(index == 0 && i == 1){
            vect->__items[index] = elem;
        }
        
    }
}