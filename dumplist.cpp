#include "dumplist.hpp"

#define NODE_COLOR "\"#F1C8CB\""
#define LABEL_COLOR "\"#F6B0BB\""
#define NODE_BORDER_COLOR "\"#9CAD8C\""
#define LABEL_BORDER_COLOR "\"#337357\""
#define BACKGROUND_COLOR "\"#ECE0DA\""

static const char* DOT_FILE_NAME = "./debug/list.dot";
static const char* DEBUG_FILE_NAME = "./debug/list_dump.txt";

static int GRAPH_NUM = 1;

void DotDump(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    FILE* dot_file = fopen(DOT_FILE_NAME, "w");

    if(dot_file != NULL) {
        fprintf(dot_file, "digraph List{\n");
        fprintf(dot_file, "\trankdir = LR;\n");
        fprintf(dot_file, "\tnode [shape = record];\n");
        fprintf(dot_file, "\tedge[color = " NODE_BORDER_COLOR "];\n");
        fprintf(dot_file, "\tbgcolor = " BACKGROUND_COLOR ";\n");

        for(size_t i = 0; i < lst->size; i++) {
           fprintf(dot_file, "\t%ld [color = " NODE_BORDER_COLOR ", shape = Mrecord, style = filled, fillcolor = " NODE_COLOR ", label = \"indx: %ld | data: %d | next: %ld | prev: %ld\"];\n",
                              i, i, lst->data[i].value, lst->data[i].next, lst->data[i].prev);
        }

        fprintf(dot_file, "\n\t");

        for (size_t i = 0; i < lst->size - 1; i++) {
            fprintf(dot_file, "%ld -> ", i);
        }

        fprintf(dot_file, "%ld [weight = 100, color = " BACKGROUND_COLOR "];\n", lst->size - 1);

        size_t i = 0;

        do {
            fprintf(dot_file, "\t%ld -> %ld [constraint = false];\n", i, lst->data[i].next);
            i = lst->data[i].next;
        } while(i != 0);

        fprintf(dot_file, "\n");

        i = lst->free;

        while(i < lst->size - 1) {
            fprintf(dot_file, "\t%ld -> %ld [constraint = false];\n", i, lst->data[i].next);
            i = lst->data[i].next;
        }
        fprintf(dot_file, "\n");

        fprintf(dot_file, "\thead [color = " LABEL_BORDER_COLOR ", shape = Mrecord, style = filled, fillcolor = " LABEL_COLOR ", label = \"head: %ld\"];\n", lst->data[PHANTOM_ELEM].next);
        fprintf(dot_file, "\ttail [color = " LABEL_BORDER_COLOR ", shape = Mrecord, style = filled, fillcolor = " LABEL_COLOR ", label = \"tail: %ld\"];\n", lst->data[PHANTOM_ELEM].prev);
        fprintf(dot_file, "\tfree [color = " LABEL_BORDER_COLOR ", shape = Mrecord, style = filled, fillcolor = " LABEL_COLOR ", label = \"free: %ld\"];\n", lst->free);
        fprintf(dot_file, "\thead -> tail -> free [weight = 100, color = %s];\n", BACKGROUND_COLOR);
        fprintf(dot_file, "\thead -> %ld [color = " LABEL_BORDER_COLOR ", constraint = false];\n", lst->data[PHANTOM_ELEM].next);
        fprintf(dot_file, "\ttail -> %ld [color = " LABEL_BORDER_COLOR ", constraint = false];\n", lst->data[PHANTOM_ELEM].prev);
        fprintf(dot_file, "\tfree -> %ld [color = " LABEL_BORDER_COLOR ", constraint = false];\n", lst->free);
        fprintf(dot_file, "}\n");
    }
    else {
        fprintf(stderr, "file did not open\n");
    }

    fclose(dot_file);
}

void GraphCreate(void) {

    char command[] = "dot -Tpng /home/ksenia/huawei/list/debug/list.dot -o /home/ksenia/huawei/list/debug/list";
    char exp[] = ".png";
    char graph_num_str[2] = {};

    snprintf(graph_num_str, 2,  "%d", GRAPH_NUM);
    strcat(command, graph_num_str);
    strcat(command, exp);
    system(command);

    GRAPH_NUM++;
}

void ListDump(const List* lst, int* code_error, const char* file, const char* func, int line) {

    FILE* debug_file = fopen(DEBUG_FILE_NAME, "a");

    if(debug_file != NULL) {
        fprintf(debug_file, "called from %s: %d (%s)\n", file, line, func);

        my_strerr(debug_file, code_error);

        if(*code_error) {
            fprintf(stderr, "code error %d\n", *code_error);
        }

        fprintf(debug_file, "List [%p] {\n", lst);

        if(lst) {
            fprintf(debug_file, "\tsize = %ld\n", lst->size);
            fprintf(debug_file, "\tdata [%p]\n\n", lst->data);
            fprintf(debug_file, "\tfree = %ld\n", lst->free);

            if(lst->data) {
                fprintf(debug_file, "\thead = %ld\n", LST_HEAD);
                fprintf(debug_file, "\ttail = %ld\n\n", LST_TAIL);
                fprintf(debug_file, "\tdata: {\n\n");

                for(size_t i = 1; i < lst->size; i++) {
                    fprintf(debug_file, "\t\tindx: %ld {\n", i);
                    fprintf(debug_file, "\t\t\tvalue: %d\n", lst->data[i].value);
                    fprintf(debug_file, "\t\t\tnext:  %ld\n", lst->data[i].next);
                    fprintf(debug_file, "\t\t\tprev:  %ld\n", lst->data[i].prev);
                    fprintf(debug_file, "\t\t}\n\n");
                }

                fprintf(debug_file, "\t}\n");
            }
        }

        fprintf(debug_file, "}\n");

        if(fclose(debug_file)) {
            fprintf(stderr, "file did not close\n");
        }
    }
    else {
        fprintf(stderr, "file did not open\n");
    }
}

#undef NODE_COLOR