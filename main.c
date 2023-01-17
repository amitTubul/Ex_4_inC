#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



int main() {
    pnode *head = malloc(sizeof(pnode));
    *head = NULL;
    char c;
    while(scanf("%c",&c)!=EOF)
    {
        switch(c) {
            case ('A'):
                build_graph_cmd(head);
                printGraph_cmd(*head);
                break;

            case ('B'):
                insert_node_cmd(head);
                printGraph_cmd(*head);
                break;
            case ('D'):
                delete_node_cmd(head);
                printGraph_cmd(*head);
                break;
            case ('S'):
                shortsPath_cmd(*head);
                break;
            case ('T'):
                TSP_cmd(*head);
                break;
            default:
                continue;
        }
    }
    deleteGraph_cmd(head);
    free(head);
    return 0;
}
