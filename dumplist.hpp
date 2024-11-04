#ifndef DUMPLIST_HPP
#define DUMPLIST_HPP

#include <sys/types.h>
#include <string.h>

#include "list.hpp"

#define LIST_DUMP(lst, code_error) ListDump((lst), (code_error), __FILE__, __func__, __LINE__)

void DotDump(List* lst, int* code_error);

void GraphCreate(void);

void ListDump(const List* lst, int* code_error, const char* file, const char* func, int line);

#endif // DUMPLIST_HPP