#ifndef DUMPLIST_HPP
#define DUMPLIST_HPP

#include <sys/types.h>
#include <string.h>

#include "list.hpp"

#define NODE_COLOR "\"#CC7952\""
#define LABEL_COLOR "\"#943D2C\""
#define BORDER_COLOR "\"#474344\""
#define BACKGROUND_COLOR "\"#DFD0BB\""

void DotDump(List* lst, int* code_error);

void GraphCreate(void);

#endif // DUMPLIST_HPP