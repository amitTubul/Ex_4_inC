#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
void printGraph_cmd(pnode head)
{
    printf("Graph representation [src]---(weight)--->[dest]\n");
    while (head != NULL)
    {
        pedge current_edge = head->edges;
        if (current_edge == NULL)
        {
            printf("[%d]\n", head->node_num);
        }
        while (current_edge != NULL)
        {
            printf("[%d]---(%d)--->[%d]\n", head->node_num, current_edge->weight, current_edge->endpoint->node_num);
            current_edge = current_edge->next;
        }
        head = head->next;
    }
}


int main() {
    pnode *head=NULL;
    char c;
    scanf("%c",&c);
    if(c=='A'){
        build_graph_cmd(head);
        printGraph_cmd(*head);
    }

    return 0;
}
