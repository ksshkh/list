#include "list.hpp"
#include "dumplist.hpp"

int main(void) {

    List lst = {};
    int code_error = 0;

    ListCtor(&lst, 9, &code_error);

    for(int i = 1; i <= 5; i++) {
        LogInsertElem(&lst, i * 10, i, &code_error);
    }

    DotDump(&lst, &code_error);

    LogInsertElem(&lst, 25, 3, &code_error);
    PhysDeleteElem(&lst, 3, &code_error);
    SwapElems(&lst, 3, 1, &code_error);
    ListLinear(&lst, &code_error);
    
    DotDump(&lst, &code_error);
    LIST_DUMP(&lst, &code_error);

    ListDtor(&lst, &code_error);

    return 0;
}