#include "list.hpp"
#include "dumplist.hpp"

int main(void) {

    List lst = {};
    int code_error = 0;

    ListCtor(&lst, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();

    // debug

    for(int i = 1; i <= 5; i++) {
    InsertElem(&lst, i * 10, i, &code_error);
    }
    DotDump(&lst, &code_error);
    GraphCreate();

    // // debug

    InsertElem(&lst, 15, 2, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();
    // // DeleteElem(&lst, 1, &code_error);

    // debug

    // InsertElem(&lst, 15, 1, &code_error);
    // DotDump(&lst, &code_error);
    // GraphCreate();

    DeleteElem(&lst, 5, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();

    // debug

    // DotDump(&lst, &code_error);
    // GraphCreate();

    ListDtor(&lst, &code_error);

    return 0;
}