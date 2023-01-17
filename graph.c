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
void deleteGraph_cmd(pnode* head) {
    if (*head == NULL) {
        printf("Graph is already empty\n");
        return;
    }
    pnode current_node = *head;
    while (current_node != NULL) {
        pedge current_edge = current_node->edges;
        while (current_edge != NULL) {
            pedge next_edge = current_edge->next;
            free(current_edge);
            current_edge = next_edge;
        }
        pnode next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    *head = NULL;
}


void build_graph_cmd(pnode *head) {
    deleteGraph_cmd(head);
    int num_of_nodes;
    scanf("%d ", &num_of_nodes);

    for (int i = num_of_nodes-1; i >= 0; i--) {
        pnode tmpnode = (pnode) malloc(sizeof(node));
        if (tmpnode == NULL) {
            printf("cannot allocate memory\n");
            return;
        }
        tmpnode->node_num = i;

        tmpnode->next = *head;
        *head = tmpnode;
    }


    char new_node;
    int number;
    int next_node;
    int weight;


    while (scanf("%c ", &new_node) != EOF) {
        if(new_node=='n') {
            scanf("%d ", &number);
            pnode temp_node = *head;
            while (temp_node->node_num != number) {
                temp_node = temp_node->next;
            }
            pedge edges = NULL;

            while (scanf("%d ", &next_node) > 0) {

                pedge temp_edge = (pedge) malloc(sizeof(edge));
                if (temp_edge == NULL) {
                    printf("cannot allocate memory for new edge\n");
                    return;
                }

                temp_edge->endpoint = *head;
                while (temp_edge->endpoint->node_num != next_node) {
                    temp_edge->endpoint = temp_edge->endpoint->next;
                }

                scanf("%d ", &weight);
                temp_edge->weight = weight;

                temp_edge->next = edges;
                edges = temp_edge;

            }
            temp_node->edges = edges;
        }
        else{
            ungetc(new_node,stdin);//return to input the previous scanned char
            return;
        }
    }
}

void insert_node_cmd(pnode *head){
    int number;
    scanf("%d ", &number);
    pnode temp_node = *head;
    while (temp_node->node_num != number ) {
        if(temp_node->next!=NULL) temp_node = temp_node->next;
        else{
            temp_node=NULL;
            break;
        }
    }

    if(temp_node==NULL){
        pnode new_node=(pnode) malloc(sizeof (node));
        if (new_node == NULL) {
            printf("cannot allocate memory\n");
            return;
        }
        new_node->node_num = number;

        new_node->next = *head;
        *head = new_node;
        temp_node=new_node;

    }
    else{
        pedge current_edge = temp_node->edges;
        while (current_edge != NULL) {
            pedge next_edge = current_edge->next;
            free(current_edge);
            current_edge = next_edge;
        }
    }

    int next_node;
    int weight;
    pedge edges = NULL;

    while (scanf("%d ", &next_node) > 0) {
        pedge temp_edge = (pedge) malloc(sizeof(edge));
        if (temp_edge == NULL) {
            printf("cannot allocate memory for new edge\n");
            return;
        }

        temp_edge->endpoint = *head;
        while (temp_edge->endpoint->node_num != next_node) {
            temp_edge->endpoint = temp_edge->endpoint->next;
        }

        scanf("%d ", &weight);
        temp_edge->weight = weight;

        temp_edge->next = edges;
        edges = temp_edge;

    }
    temp_node->edges = edges;
}




