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
    ListElem* data = NULL;

    size_t head = 0;
    size_t tail = 0;
    size_t free = 0;

    size_t size = 0;
};

const size_t InitSize = 10;

void ListCtor(List* lst, int* code_error);

void ListDtor(List* lst, int* code_error);

#endif // LIST_HPP