#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



int main() {
    pnode *head = malloc(sizeof(pnode));
    *head = NULL;
    char c;
    scanf("%c",&c);
    if(c=='A'){
        build_graph_cmd(head);
        printGraph_cmd(*head);
    }

    return 0;
}
