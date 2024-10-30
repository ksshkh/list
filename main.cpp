#include "list.hpp"

int main(void) {

    List lst = {};
    int code_error = 0;

    ListCtor(&lst, &code_error);
    ListDtor(&lst, &code_error);

    return 0;
}