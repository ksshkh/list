#include "dumplist.hpp"

static const char* DOT_FILE_NAME = "./debug/list.dot";

static int GRAPH_NUM = 1;

void DotDump(List* lst, int* code_error) {

    MY_ASSERT(lst != NULL, PTR_ERROR);

    FILE* dot_file = fopen(DOT_FILE_NAME, "w");

    if(dot_file != NULL) {
        fprintf(dot_file, "digraph List{\n");
        fprintf(dot_file, "\trankdir = LR;\n");
        fprintf(dot_file, "\tnode [shape = record];\n");
        fprintf(dot_file, "\tedge[color = %s];\n", BORDER_COLOR);
        fprintf(dot_file, "\tbgcolor = " BACKGROUND_COLOR ";\n");
        for(size_t i = 0; i < lst->size; i++) {
           fprintf(dot_file, "\t%ld [color = %s, shape = Mrecord, style = filled, fillcolor = %s, label = \"indx: %ld | data: %d | next: %ld | prev: %ld\"];\n",
                              i, BORDER_COLOR, NODE_COLOR, i, lst->data[i].value, lst->data[i].next, lst->data[i].prev);
        }
        size_t i = 0;
        do {
            fprintf(dot_file, "\t%ld -> %ld", i, lst->data[i].next);
            i = lst->data[i].next;
        } while(i != 0);

        fprintf(dot_file, "\n");
        fprintf(dot_file, "\thead [shape = Mrecord, style = filled, fillcolor = " LABEL_COLOR ", label = \"head: %ld\"];\n", lst->head);
        fprintf(dot_file, "\ttail [shape = Mrecord, style = filled, fillcolor = " LABEL_COLOR ", label = \"tail: %ld\"];\n", lst->tail);
        fprintf(dot_file, "\tfree [shape = Mrecord, style = filled, fillcolor = " LABEL_COLOR ", label = \"free: %ld\"];\n", lst->free);
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