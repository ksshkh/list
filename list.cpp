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
    lst->linear = true;
    lst->num_of_elems = 0;

    ListFilling(lst, code_error);

    LIST_ASSERT(lst);
}

void ListFilling(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    for (size_t i = lst->free; i < lst->size; i++) {
        lst->data[i].next = i + 1;
        lst->data[i].prev = i - 1;
        lst->data[i].value = POISON;
    }
    lst->data[lst->free].prev = lst->size - 1;
    lst->data[lst->size - 1].next = lst->free;

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

        if(lst->data[i].value == POISON && i != PHANTOM_ELEM) {
            *code_error |= MIXED_LIST;
        }

        counter++;
        i = lst->data[i].next;
    } while(i != 0);

    i = lst->free;

    do {

        if(lst->data[i].value != POISON) {
            *code_error |= MIXED_LIST;
        }

        i = lst->data[i].next;
        counter++;
    } while(i != lst->free);

    if(counter != lst->size) {
        *code_error |= LOST_NODE;
    }

    return *code_error;
}

void PhysInsertElem(List* lst, ListElem elem, size_t indx, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    lst->num_of_elems++;

    if(indx != LST_TAIL) {
        lst->linear = false;
    }

    if(lst->free == lst->size - 1) {
        ListReallocation(lst, UP_ID, code_error);
    }

    size_t temp_free = lst->data[lst->free].next;

    lst->data[lst->data[indx].next].prev = lst->free;
    lst->data[lst->free].value = elem;
    lst->data[lst->free].prev = indx;
    lst->data[lst->free].next = lst->data[indx].next;
    lst->data[indx].next = lst->free;

    lst->free = temp_free;
    lst->data[lst->free].prev = lst->size - 1;
    lst->data[lst->size - 1].next = lst->free;

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

    lst->num_of_elems--;

    if(indx != LST_TAIL) {
        lst->linear = false;
    }

    lst->data[lst->data[indx].prev].next = lst->data[indx].next;
    lst->data[lst->data[indx].next].prev = lst->data[indx].prev;
    lst->data[indx].value = POISON;
    lst->data[indx].prev = lst->data[lst->free].prev;
    lst->data[lst->free].prev = indx;

    lst->data[indx].next = lst->free;
    lst->free = indx;
    lst->data[lst->free].prev = lst->size - 1;
    lst->data[lst->size - 1].next = lst->free;

    if((lst->num_of_elems * 2) < lst->size) {
        ListReallocation(lst, DOWN_ID, code_error);
    }

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

        size_t next1 = lst->data[indx1].next;
        size_t prev1 = lst->data[indx1].prev;

        size_t next2 = lst->data[indx2].next;
        size_t prev2 = lst->data[indx2].prev;

        ListElem value1 = lst->data[indx1].value;
        ListElem value2 = lst->data[indx2].value;

        lst->data[indx1].value = value2;
        lst->data[indx2].value = value1;

        lst->data[prev1].next = indx2;
        lst->data[indx2].prev = prev1;

        if(next1 == indx2 || next2 == indx1) {
            lst->data[next1].prev = prev1;
            lst->data[indx2].next = indx1;

            lst->data[prev2].next = next2;
            lst->data[indx1].prev = indx2;
        }
        else {
            lst->data[next1].prev = indx2;
            lst->data[indx2].next = next1;

            lst->data[prev2].next = indx1;
            lst->data[indx1].prev = prev2;
        }

        lst->data[next2].prev = indx1;
        lst->data[indx1].next = next2;

        if(indx1 == lst->free || indx2 == lst->free) {
            size_t indx_free = (lst->data[indx1].value == POISON) ? indx1 : indx2;
            lst->free = indx_free;
        }

    LIST_ASSERT(lst);
}

void ListLinear(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    size_t i = 0;

    do {

        if(i + 1 != lst->data[i].next) {
            SwapElems(lst, lst->data[i].next, i + 1, code_error);
        }

        i++;

    } while(lst->data[i].next != 0);

    LIST_ASSERT(lst);
}

void ListReallocation(List* lst, ID id, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);
    LIST_ASSERT(lst);

    if(lst->linear == false) {
        ListLinear(lst, code_error);
    }

    if(id == UP_ID) {
        lst->size *= 2;
    }
    else if(id == DOWN_ID) {
        lst->size = lst->size / 2 + 1;
    }

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
    lst->linear = 0;
    lst->num_of_elems = 0;

}