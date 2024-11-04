#ifndef DUMPLIST_HPP
#define DUMPLIST_HPP

#include <sys/types.h>
#include <string.h>

#include "list.hpp"

#define NODE_COLOR "\"#F1C8CB\""
#define LABEL_COLOR "\"#F6B0BB\""
#define NODE_BORDER_COLOR "\"#9CAD8C\""
#define LABEL_BORDER_COLOR "\"#337357\""
#define BACKGROUND_COLOR "\"#ECE0DA\""

void DotDump(List* lst, int* code_error);

void GraphCreate(void);

#endif // DUMPLIST_HPP