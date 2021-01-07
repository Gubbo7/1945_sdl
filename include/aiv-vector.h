#ifndef AIV_VECTOR_H
#define AIV_VECTOR_H
#include "common.h"

struct aiv_vector {
    void** __items; 
    unsigned int __count;
    unsigned int __capacity;
};

typedef struct aiv_vector avector;

//Prototipi
avector* aiv_vector_new();
void aiv_vector_destroy(avector* vect);
void aiv_vector_add(avector* vect, void* item);
void* aiv_vector_at(avector* vect, uint index);
avector* aiv_vector_resize(avector* vect, uint capacity);
avector* aiv_vector_new_with_cap(uint capacity);
void aiv_vector_foreach(avector* vect, void (*action)(void* elem));
//
boolean aiv_vector_is_empty(avector* v);
uint aiv_vector_size(avector* v);
void aiv_vector_set(avector* v, int index, void* elem);
void aiv_vector_add_all(avector* v, avector* other);
void aiv_vector_remove_at(avector*v, int index);
void aiv_vector_insert_at(avector*v, int index, void* elem);
//
void* aiv_vector_find_one(avector*v, int index, void* elem);
avector* aiv_vector_find_all(avector*v, int index, void* elem);
#endif /* AIV_VECTOR_H */