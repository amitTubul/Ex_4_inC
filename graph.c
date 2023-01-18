#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <limits.h>
#include <stdbool.h>

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

void delete_node_cmd(pnode *head){
    printGraph_cmd(*head);
    int number;
    scanf("%d ", &number);
    pnode temp_node = *head;
    pnode prev_node =NULL;
    while (temp_node->node_num != number ) {
        prev_node=temp_node;
        temp_node = temp_node->next;
    }

    pedge current_edge = temp_node->edges;
    while (current_edge != NULL) {
        pedge next_edge = current_edge->next;
        free(current_edge);
        current_edge = next_edge;
    }
    temp_node->edges=NULL;

    pnode tmp_node = *head;
    pedge prev_edge ;
    while (tmp_node != NULL ) {
        current_edge = tmp_node->edges;
        while (current_edge!=NULL) {
            if (current_edge->endpoint->node_num != number) {
                prev_edge = current_edge;
                current_edge = current_edge->next;
                continue;
            }
            pedge next_edge = current_edge->next;
            if (current_edge == tmp_node->edges) {
                tmp_node->edges = next_edge;
                free(current_edge);
                break;
            } else {
                prev_edge->next = next_edge;
                free(current_edge);
                break;
            }
        }
        tmp_node = tmp_node->next;
    }


    if(temp_node==*head){
        *head=temp_node->next;
        free(temp_node);
    }
    else {
        pnode next_node = temp_node->next;
        free(temp_node);
        prev_node->next=next_node;
    }
    printGraph_cmd(*head);
}

bool is_visited(pnode node, pnode visited_nodes) {
    pnode current = visited_nodes;
    while(current) {
        if(current->node_num == node->node_num) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Returns the node with the smallest distance in the unvisited set
pnode get_smallest_distance_node(pnode nodes, pnode visited_nodes) {
    pnode smallest_node = NULL;
    int smallest_distance = INT_MAX;
    pnode current_node = nodes;
    while (current_node) {
        if (!is_visited(current_node, visited_nodes) && current_node->distance <= smallest_distance) {
            smallest_node = current_node;
            smallest_distance = current_node->distance;
        }
        current_node = current_node->next;
    }
    return smallest_node;
}

int shortsPath_cmd_local(pnode head,int a,int b){
    if (!head) return-1;
    pnode visited_nodes = NULL; //keep track of visited node without changing the weight

    // Initialize distances for all nodes
    pnode current_node = head;
    while (current_node) {
        if (current_node->node_num == a) {
            current_node->distance = 0;
        } else {
            current_node->distance = INT_MAX;
        }
        current_node = current_node->next;
    }

    // Run Dijkstra's algorithm
    while (true) {
        pnode smallest_node = get_smallest_distance_node(head, visited_nodes);
        if (!smallest_node) break; // All nodes have been visited

        //Mark node as visited by adding to visited_nodes list
        pnode new_visited = (pnode)malloc(sizeof(node));
        new_visited->node_num = smallest_node->node_num;
        new_visited->next = visited_nodes;
        visited_nodes = new_visited;

        // Update distances of neighboring nodes
        pedge current_edge = smallest_node->edges;
        while (current_edge) {
            pnode endpoint = current_edge->endpoint;
            if (!is_visited(endpoint, visited_nodes) && smallest_node->distance + current_edge->weight < endpoint->distance) {
                endpoint->distance = smallest_node->distance + current_edge->weight;
            }
            current_edge = current_edge->next;
        }
    }

    // Print shortest distance
    pnode end = head;
    while (end && end->node_num != b) end = end->next;
    if (!end) return-1; // Ending node not found

    while(visited_nodes){
        pnode curr=visited_nodes->next;
        free(visited_nodes);
        visited_nodes=curr;
    }
    return end->distance;
}

void shortsPath_cmd(pnode head){
    int a;
    int b;
    scanf("%d ",&a);
    scanf("%d ",&b);

    int shortest=shortsPath_cmd_local(head,a,b);
    printf("Dijsktra shortest path: %d \n", shortest);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void permute(int* arr, int start, int end ,int *ptr ,pnode head) {
    if (start == end) {
        int count=0;
        int curr;
        for (int i = 0; i < end; i++) {
            curr=shortsPath_cmd_local(head,arr[i],arr[i+1]);
            if (curr==INT_MAX){
                count=INT_MAX;
                break;
            }
            count+=curr;
        }
        if(count<*ptr && count>=0) *ptr=count;
    } else {
        for (int i = start; i <= end; i++) {
            swap(&arr[start], &arr[i]);
            permute(arr, start + 1, end,ptr,head);
            swap(&arr[start], &arr[i]);
        }
    }
}

void TSP_cmd(pnode head){
    int size;
    int number;
    scanf("%d ",&size);

    int *arr= (int*)malloc(size*sizeof (int));
    for (int i = 0; i < size; i++) {
        scanf("%d ",&number);
        arr[i]=number;
    }
    int shortest=INT_MAX;
    int *ptr=&shortest;
    permute(arr, 0, size - 1,ptr,head);
    free(arr);
    if(*ptr==INT_MAX){
        *ptr=-1;
    }
    printf("TSP shortest path: %d \n",*ptr);
}


