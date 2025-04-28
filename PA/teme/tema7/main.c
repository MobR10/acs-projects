#include <stdio.h>
#include <stdlib.h>
#define QUEUE_MAX 50
#define STACK_MAX 50
#include "stacks_queues.h"

struct node {
    int data;
    struct node *adj;
};
typedef struct node Node;

struct graph{
    int nodes;
    Node **adjacencyList;
};
typedef struct graph Graph;

Graph * createGraph(int data)
{
    Graph *graph=(Graph*)malloc(sizeof(Graph));
    graph->nodes=1;
    graph->adjacencyList=(Node**)malloc(sizeof(Node**));
    Node *node=(Node*)malloc(sizeof(Node));
    node->data=data;
    return graph;
}

int main()
{
    Graph *graph=NULL;
    graph=createGraph(1);


}