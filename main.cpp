#include "list.hpp"
#include "dumplist.hpp"

int main(void) {

    List lst = {};
    int code_error = 0;

    ListCtor(&lst, 5, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();
    // LogInsertElem(&lst, 10, 1, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();
    // LogInsertElem(&lst, 20, 2, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();
    // LogInsertElem(&lst, 15, 2, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();

    for(int i = 1; i <= 3; i++) {
        LogInsertElem(&lst, i * 10, i, &code_error);
    }

    // DotDump(&lst, &code_error);
    // GraphCreate();

    LogInsertElem(&lst, 15, 2, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();

    // LogInsertElem(&lst, 45, 6, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();

    // LIST_DUMP(&lst, &code_error);

    // LogInsertElem(&lst, 15, 1, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();

    // PhysDeleteElem(&lst, 5, &code_error);
    // SwapElems(&lst, 4, 2, &code_error);
    // SwapElems(&lst, 3, 4, &code_error);
    ListLinear(&lst, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();

    ListDtor(&lst, &code_error);

    return 0;
}