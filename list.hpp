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
    size_t free = 0;
    size_t size = 0;
};

const size_t PHANTOM_ELEM = 0;
const ListElem POISON = -666;
const size_t PREV_DEFAULT = -1;

#define LST_HEAD lst->data[PHANTOM_ELEM].next
#define LST_TAIL lst->data[PHANTOM_ELEM].prev

#define LIST_ASSERT(lst) {                                           \
    int err = ListVerification(lst, code_error);                     \
    if (err != NO_ERROR) {                                           \
        LIST_DUMP(lst, code_error);                                  \
    }                                                                \
}

void ListCtor(List* lst, size_t InitSize, int* code_error);

void ListFilling(List* lst, int* code_error);

int ListVerification(List* lst, int* code_error);

void PhysInsertElem(List* lst, ListElem elem, size_t position, int* code_error);

void LogInsertElem(List* lst, ListElem elem, size_t position, int* code_error);

size_t IndxGet(List* lst, const size_t position, int* code_error);

void PhysDeleteElem(List* lst, size_t indx, int* code_error);

void LogDeleteElem(List* lst, size_t position, int* code_error);

void SwapElems(List* lst, size_t indx1, size_t indx2, int* code_error);

void ListLinear(List* lst, int* code_error);

void ListReallocation(List* lst, int* code_error);

void ListDtor(List* lst, int* code_error);

#endif // LIST_HPP