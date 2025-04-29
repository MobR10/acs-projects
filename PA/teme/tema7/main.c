#include <stdlib.h>
#include <stdio.h>

#define QUEUE_MAX 50
#define STACK_MAX 50

#include "stacks_queues.h"

struct node
{
    int data;
    struct node *next;
};
typedef struct node Node;

struct graph
{
    int vertices;
    int *visited;
    Node **adjacencyList;
};
typedef struct graph Graph;

Node *createNode(int data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    checkAllocation(new);
    new->data = data;
    new->next = NULL;
    return new;
}

Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacencyList = (Node **)malloc((unsigned long long int)(vertices + 1) * sizeof(Node *));

    graph->visited = (int *)malloc(sizeof(int) * (unsigned long long int)(vertices + 1));
    for (int i = 1; i <= vertices; i++)
    {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// function that adds an edge between 2 nodes in a not oriented graph
void addEdgeNotOriented(Graph *graph, int source, int destination)
{

    Node *node = createNode(source);
    node->next = graph->adjacencyList[destination];
    graph->adjacencyList[destination] = node;
    node = createNode(destination);
    node->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = node;
}

void addEdgeOriented(Graph *graph, int source, int destination)
{
    Node *node = createNode(destination);
    node->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = node;
}

void insertEdges(Graph *graph, int edges, int isOriented)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edges, graph->vertices);
    for (i = 0; i < edges; i++)
    {
        scanf("%d%d", &src, &dest);
        if (!isOriented)
            addEdgeNotOriented(graph, src, dest);
        else
            addEdgeOriented(graph, src, dest);
    }
}

void printGraph(Graph *graph)
{
    int i;
    for (i = 1; i <= graph->vertices; i++)
    {
        Node *adjacencyList = graph->adjacencyList[i];
        printf("%d: ", i);
        while (adjacencyList)
        {
            printf("%d ", adjacencyList->data);
            adjacencyList = adjacencyList->next;
        }
        printf("\n");
    }
}

void wipeVisitedList(Graph *graph)
{
    for (int i = 1; i <= graph->vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(Graph *graph, int currentVertex)
{
    Node *adjacencyList = graph->adjacencyList[currentVertex];

    graph->visited[currentVertex] = 1;
    printf("%d->", currentVertex);

    while (adjacencyList != NULL)
    {
        int neighbour = adjacencyList->data;

        if (graph->visited[neighbour] == 0)
        {
            DFS(graph, neighbour);
        }
        adjacencyList = adjacencyList->next;
    }
}

void BFS(Graph *graph, int start, Queue **front, Queue **rear)
{
    Node *queue = NULL;

    graph->visited[start] = 1;
    enqueue(front, rear, start);

    while (!isEmpty(queue))
    {
        int current = (*front)->data;
        dequeue(front, rear);
        printf("%d ", current);

        Node *adjacencyList = graph->adjacencyList[current];

        while (adjacencyList)
        {
            int neighbour = adjacencyList->data;

            if (graph->visited[neighbour] == 0)
            {
                graph->visited[neighbour] = 1;
                enqueue(front, rear, neighbour);
            }
            adjacencyList = adjacencyList->next;
        }
    }
}

// EX2
int isPath(Graph *graph, int source, int destination)
{
    if (source == destination)
        return 1;

    graph->visited[source] = 1;

    Node *adjacencyList = graph->adjacencyList[source];

    while (adjacencyList != NULL)
    {
        int neighbour = adjacencyList->data;
        if (!graph->visited[neighbour])
        {
            if (isPath(graph, neighbour, destination))
                return 1; // Path found through neighbor
        }
        adjacencyList = adjacencyList->next;
    }

    return 0; // No path found through any neighbors
}

int main()
{
    // variables to be read and used to create both oriented and not oriented graph
    int vertices;
    int edges;
    int startingVertex;

    Queue *front = NULL, *rear = NULL; // initialize queue for BFS

    // NOT ORIENTED GRAPH

    // printf("cate noduri are graful?");
    // scanf("%d", &vertices);

    // printf("cate muchii are graful?");
    // scanf("%d", &edges);

    // Graph *graph = createGraph(vertices);

    // insertEdges(graph, edges, 0);

    // printf("de unde plecam in DFS?");
    // scanf("%d", &startingVertex);

    // printf("parcurgere cu DFS:");
    // DFS(graph, startingVertex);

    // wipeVisitedList(graph);
    // printf("\n");

    // printf("de unde plecam in BFS?");
    // scanf("%d", &startingVertex);

    // printf("parcurgere cu BFS:");
    // BFS(graph, startingVertex, &front, &rear);
    // DFS(graph, 0);

    // ORIENTED GRAPH

    // printf("Cate noduri sa aiba graful orientat? ");
    // scanf("%d", &vertices);
    // Graph *ograph = createGraph(vertices);

    // printf("Cate muchii? ");
    // scanf("%d", &edges);

    // insertEdges(ograph, edges, 1);

    Graph *ograph=createGraph(5);
    addEdgeOriented(ograph,0,1);
    addEdgeOriented(ograph,0,2);
    addEdgeOriented(ograph,1,3);
    addEdgeOriented(ograph,1,2);
    addEdgeOriented(ograph,2,3);
    addEdgeOriented(ograph,3,4);
    addEdgeOriented(ograph,2,4);

    printf("%d",isPath(ograph,2,4));

    return 0;
}