#include "list.hpp"
#include "dumplist.hpp"

int main(void) {

    List lst = {};
    int code_error = 0;

    ListCtor(&lst, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();

    // debug

    PhysInsertElem(&lst, 10, 0, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();

    // debug

    PhysInsertElem(&lst, 20, 1, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();
    // // DeleteElem(&lst, 1, &code_error);

    // debug

    PhysInsertElem(&lst, 15, 8, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();
    DeleteElem(&lst, 1, &code_error);
    DotDump(&lst, &code_error);
    GraphCreate();

    // debug

    // DotDump(&lst, &code_error);
    // GraphCreate();

    ListDtor(&lst, &code_error);

    return 0;
}