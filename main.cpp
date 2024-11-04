#include "list.hpp"
#include "dumplist.hpp"

int main(void) {

    List lst = {};
    int code_error = 0;

    ListCtor(&lst, 10, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();

    for(int i = 1; i <= 5; i++) {
        LogInsertElem(&lst, i * 10, i, &code_error);
    }

    DotDump(&lst, &code_error);
    GraphCreate();

    LogInsertElem(&lst, 15, 2, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();

    LIST_DUMP(&lst, &code_error);

    // LogInsertElem(&lst, 15, 1, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();

    DeleteElem(&lst, 5, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();

    ListDtor(&lst, &code_error);

    return 0;
}