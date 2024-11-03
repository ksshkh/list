#ifndef LIST_HPP
#define LIST_HPP

#include <stdio.h>
#include <stdlib.h>

#include "errors.hpp"

typedef int ListElem;

struct Node {
    ListElem value = 0;
    size_t next = 0;
    size_t prev = 0;
};

struct List {
    Node* data = NULL;

    size_t head = 0;
    size_t tail = 0;
    size_t free = 0;

    size_t size = 0;
};


const size_t PHANTOM_ELEM = 0;
const size_t InitSize = 10;
const ListElem POISON = -666;

#define debug fprintf(stderr, "head: %d tail: %d free: %d\n", lst.head, lst.tail, lst.free); \
    for(size_t i = 0; i < InitSize; i++) { \
        fprintf(stderr, "%4d", lst.data[i].value); \
    } \
    fprintf(stderr, "\n"); \
    for(size_t i = 0; i < InitSize; i++) { \
        fprintf(stderr, "%4d", lst.data[i].next); \
    } \
    fprintf(stderr, "\n"); \
    for(size_t i = 0; i < InitSize; i++) { \
        fprintf(stderr, "%4d", lst.data[i].prev); \
    } \
    fprintf(stderr, "\n"); \

void ListCtor(List* lst, int* code_error);

void PhysInsertElem(List* lst, ListElem elem, size_t position, int* code_error);

void DeleteElem(List* lst, size_t position, int* code_error);

void ListDtor(List* lst, int* code_error);

#endif // LIST_HPP