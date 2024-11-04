#include "list.hpp"
#include "dumplist.hpp"

void ListCtor(List* lst, size_t InitSize, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    MY_ASSERT(InitSize != 0, SIZE_ERROR);

    lst->size = InitSize;

    lst->data = (Node*)calloc(lst->size, sizeof(Node));
    MY_ASSERT(lst->data != NULL, PTR_ERROR);

    lst->data[PHANTOM_ELEM].value = POISON;

    lst->free = 1;

    ListFilling(lst, code_error);

    LIST_ASSERT(lst);
}

void ListFilling(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    for (size_t i = lst->free; i < lst->size; i++) {
        lst->data[i].next = i + 1;
        lst->data[i].value = 0;
        lst->data[i].prev = PREV_DEFAULT;
    }

    LIST_ASSERT(lst);
}

int ListVerification(List* lst, int* code_error) {

    if(!lst) {
        *code_error |= PTR_ERROR;
        return *code_error;
    }

    if(lst->size == 0 || lst->size == 1) {
        *code_error |= SIZE_ERROR;
    }

    if(lst->free > lst->size) {
        *code_error |= BAD_LIST_FREE;
    }

    if(!lst->data) {
        *code_error |= NO_DATA;
        return *code_error;
    }

    if(LST_HEAD >= lst->size) {
        *code_error |= BAD_LIST_HEAD;
    }

    if(LST_TAIL >= lst->size) {
        *code_error |= BAD_LIST_TAIL;
    }

    size_t i = 0;
    size_t counter = 0;

    do {
        if(lst->data[lst->data[i].prev].next != i) {
            *code_error |= BREAK_LIST;
        }

        if(lst->data[i].prev == PREV_DEFAULT) {
            *code_error |= MIXED_LIST;
        }

        counter++;
        i = lst->data[i].next;
    } while(i != 0);

    i = lst->free;

    while(i < lst->size) {

        if(lst->data[i].prev != PREV_DEFAULT) {
            *code_error |= MIXED_LIST;
        }

        i = lst->data[i].next;
        counter++;
    }

    if(counter != lst->size) {
        *code_error |= LOST_NODE;
    }

    return *code_error;
}

void PhysInsertElem(List* lst, ListElem elem, size_t indx, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    if(lst->free == lst->size) {
        ListReallocation(lst, code_error);
    }

    size_t temp_free = lst->data[lst->free].next;

    lst->data[lst->data[indx].next].prev = lst->free;
    lst->data[lst->free].value = elem;
    lst->data[lst->free].prev = indx;
    lst->data[lst->free].next = lst->data[indx].next;
    lst->data[indx].next = lst->free;

    lst->free = temp_free;

    LIST_ASSERT(lst);
}

void LogInsertElem(List* lst, ListElem elem, size_t position, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    size_t indx = IndxGet(lst, position, code_error);

    PhysInsertElem(lst, elem, indx, code_error);

    LIST_ASSERT(lst);
}

size_t IndxGet(List* lst, const size_t position, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    size_t counter = 1;
    size_t indx = 0;

    while(counter != position) {
        indx = lst->data[indx].next;
        counter++;
    }

    LIST_ASSERT(lst);

    return indx;
}

void PhysDeleteElem(List* lst, size_t indx, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    lst->data[lst->data[indx].prev].next = lst->data[indx].next;
    lst->data[lst->data[indx].next].prev = lst->data[indx].prev;
    lst->data[indx].prev = PREV_DEFAULT;

    lst->data[indx].next = lst->free;
    lst->free = indx;

    LIST_ASSERT(lst);
}

void LogDeleteElem(List* lst, size_t position, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    size_t indx = IndxGet(lst, position, code_error);
    indx++;

    PhysDeleteElem(lst, indx, code_error);

    LIST_ASSERT(lst);
}

void SwapElems(List* lst, size_t indx1, size_t indx2, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    ListElem save_value1 = lst->data[indx1].value;
    ListElem save_value2 = lst->data[indx2].value;

    PhysInsertElem(lst, save_value2, indx1, code_error);
    PhysDeleteElem(lst, indx1, code_error);

    PhysInsertElem(lst, save_value1, indx2, code_error);
    PhysDeleteElem(lst, indx2, code_error);

    LIST_ASSERT(lst);
}

void ListLinear(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    size_t i = 0;

    do {
        if(i + 1 != lst->data[i].next) {
            size_t indx = IndxGet(lst, lst->data[i].next, code_error);
            SwapElems(lst, indx, i + 1, code_error);
        }

        i++;

    } while(i != 0);

    LIST_ASSERT(lst);
}

void ListReallocation(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    lst->size *= 2;
    lst->data = (Node*)realloc(lst->data, lst->size * sizeof(Node));
    MY_ASSERT(lst->data != NULL, PTR_ERROR);

    ListFilling(lst, code_error);

    LIST_ASSERT(lst);
}

void ListDtor(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    free(lst->data);
    lst->data = NULL;

    lst->size = 0;
    lst->free = 0;

}