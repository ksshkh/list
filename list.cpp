#include "list.hpp"

void ListCtor(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    MY_ASSERT(InitSize != 0, SIZE_ERROR);

    lst->size = InitSize;

    lst->data = (Node*)calloc(lst->size, sizeof(Node));
    MY_ASSERT(lst->data != NULL, PTR_ERROR);

    lst->data[PHANTOM_ELEM].value = POISON;

    for (size_t i = 1; i < InitSize; i++) {
        lst->data[i].next = i + 1;
        lst->data[i].prev = -1;
    }

    lst->free = 1;

}

void PhysInsertElem(List* lst, ListElem elem, size_t indx, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    size_t temp_free = lst->data[lst->free].next;

    lst->data[lst->data[indx].next].prev = lst->free;
    lst->data[lst->free].value = elem;
    lst->data[lst->free].prev = indx;
    lst->data[lst->free].next = lst->data[indx].next;
    lst->data[indx].next = lst->free;

    lst->free = temp_free;

}

void InsertElem(List* lst, ListElem elem, size_t position, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    size_t indx = IndxGet(lst, position, code_error);

    PhysInsertElem(lst, elem, indx, code_error);
}

size_t IndxGet(const List* lst, const size_t position, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    size_t counter = 1;
    size_t indx = 0;

    while(counter != position) {
        indx = lst->data[indx].next;
        counter++;
    }

    return indx;
}

void DeleteElem(List* lst, size_t position, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    size_t indx = IndxGet(lst, position, code_error);
    indx++;

    lst->data[lst->data[indx].prev].next = lst->data[indx].next;
    lst->data[lst->data[indx].next].prev = lst->data[indx].prev;

    lst->data[indx].next = lst->free;
    lst->free = indx;

}

void ListDtor(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    free(lst->data);
    lst->data = NULL;

    lst->size = InitSize;
    lst->head = 0;
    lst->tail = 0;
    lst->free = 0;

}