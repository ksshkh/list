#include "list.hpp"
#include "dumplist.hpp"

int main(void) {

    List lst = {};
    int code_error = 0;

    ListCtor(&lst, 20, &code_error);

    for(int i = 1; i <= 10; i++) {
        LogInsertElem(&lst, i * 10, i, &code_error);
    }

    DotDump(&lst, &code_error);

    // LogInsertElem(&lst, 15, 2, &code_error);
    // DotDump(&lst, &code_error);

    // LogInsertElem(&lst, 45, 6, &code_error);
    // DotDump(&lst, &code_error);

    PhysDeleteElem(&lst, 1, &code_error);

    PhysDeleteElem(&lst, 4, &code_error);

    PhysDeleteElem(&lst, 5, &code_error);

    LogInsertElem(&lst, 1, 17, &code_error);

    LogInsertElem(&lst, 2, 18, &code_error);

    PhysDeleteElem(&lst, 9, &code_error);
    DotDump(&lst, &code_error);

    ListLinear(&lst, &code_error);
    // // SwapElems(&lst, 6, 2, &code_error);
    DotDump(&lst, &code_error);
    LIST_DUMP(&lst, &code_error);

    ListDtor(&lst, &code_error);

    return 0;
}