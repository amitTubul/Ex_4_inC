#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


void build_graph_cmd(pnode *head) {
    int num_of_nodes;
    scanf("%d ", &num_of_nodes);
    pnode nodes = (pnode) malloc(num_of_nodes * sizeof(node));
    head = &nodes;

    if (nodes == NULL) {
        printf("cannot allocate memory\n");
        return;
    }

    int i;
    for (i = 0; i < num_of_nodes - 1; i++) {
        (nodes + (i * sizeof(node)))->node_num = i;
        (nodes + (i * sizeof(node)))->next = (nodes + (i + 1) * sizeof(node));
    }

    (nodes + (i * sizeof(node)))->node_num = i;
    (nodes + (i * sizeof(node)))->next = NULL;


    char new_node;
    int number;
    int next_node;
    int weight;


    while (scanf("%c ", &new_node) != EOF) {
        printf("new node=%c\n",new_node);
        scanf("%d", &number);
        pnode temp_node = (nodes + number * sizeof(node));
        pedge edges=NULL;


        while (scanf("%d ", &next_node)>0) {

            pedge temp_edge= (pedge) malloc( sizeof(edge));

            temp_edge->endpoint = nodes+next_node*sizeof (node);

            scanf("%d ", &weight);
            temp_edge->weight = weight;

            temp_edge->next=edges;
            edges=temp_edge;

        }
        temp_node->edges = edges;
    }



//    pnode tmp = *head;
//
//    while ((tmp) != NULL) {
//        printf("node number:%d\n", (tmp)->node_num);
//        pedge tmpedge = &((tmp)->edges);
//        while ((*tmpedge) != NULL) {
//            printf("endpoint number :%d with weight %d\n", (*tmpedge)->endpoint->node_num, (*tmpedge)->weight);
//            *tmpedge = (*tmpedge)->next;
//        }
//    }
}
