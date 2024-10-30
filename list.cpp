#include "list.hpp"

void ListCtor(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    MY_ASSERT(InitSize != 0, SIZE_ERROR);

    lst->size = InitSize;

    lst->data = (ListElem*)calloc(lst->size, sizeof(Node));
    MY_ASSERT(lst->data != NULL, PTR_ERROR);

    lst->head = 0;
    lst->tail = 0;
    lst->free = 1;

}

void ListDtor(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    free(lst->data);
    lst->data = NULL;

    lst->size = InitSize;
    lst->head = 0;
    lst->tail = 0;
    lst->free = 1;

}