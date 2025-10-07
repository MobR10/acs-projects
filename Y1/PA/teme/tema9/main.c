#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define QUEUE_MAX 50 // maximum number of elements in queue (default is defined in stacks_queues.h)
#define STACK_MAX 50

#include "stacks_queues.h" // my file containing queue and stack structures

#define INPUT_TEMA8 "tema8_input.csv"
#define INPUT_1 "input1.csv" // only positive weights
#define INPUT_2 "input2.csv" // both positive and negative weights (for bellman-ford)

// Explaining the weight attribute of node
/*
    When adding one vertex as a neighbour to the neighbour list of 2 different vertices, the instances of that vertex
    may have the same index, but they are 2 different instances created in memory. Let's take an example: we have an edge
    from 0 to 2 and from 1 to 2. Given how the implementation of the function that adds vertices to the adjacencyList,
    we can act as if adjacencyList[0], being the first neighbour of vertex 0, is a vertex with index 2 and weight 3,
    representing the weight of the edge from 0 to 2 and adjacencyList[1] is a vertex with also index 2, but its weight is 5,
    meaning the weight of the edge from vertex 1 to 2 is 5. In this case, the adjacencyList looks like this:
    0: 2
    1: 2
    Here we see 2 twice, it is not the same instance, but 2 separate instances inside memory, so we can use this opportunity to implement
    the weight attribute inside the node data structure so that we do not create other data structures that are going to
    overcomplicate the code even more.

*/
struct node
{

    int index;
    int weight;
    struct node *next;
};
typedef struct node Node;

struct graph
{
    int vertices;
    int *values, *setValues; // values[i] is the value for node i and setValues[i]=0/1 whether a node's value has been set (for when the node is first created)
    int *visited;
    Node **adjacencyList;
    Queue *front, *rear;
};
typedef struct graph Graph;

Node *createNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    checkAllocation(node);
    node->index = data;
    node->next = NULL;
    return node;
}

Graph *createGraph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    checkAllocation(graph);
    graph->vertices = 0;
    graph->adjacencyList = NULL;
    graph->visited = NULL;
    graph->values = NULL;
    graph->setValues = NULL;
    graph->front = NULL;
    graph->rear = NULL;
    return graph;
}

void freeGraph(Graph *graph)
{
    if (!graph)
        return;

    // Free each adjacency list (each linked list of neighbors)
    for (int i = 0; i < graph->vertices; i++)
    {
        Node *current = graph->adjacencyList[i];
        while (current)
        {
            Node *temp = current;
            current = current->next;
            free(temp); // Free each node in the adjacency list
        }
    }

    // Free adjacency list array
    free(graph->adjacencyList);

    // Free other dynamically allocated arrays
    free(graph->visited);
    free(graph->values);
    free(graph->setValues);
    free(graph->front);
    free(graph->rear);

    // Free the graph structure itself
    free(graph);
}

void allocateNode(Graph *graph)
{
    if (isEmpty(graph))
    {
        puts("The graph is NULL. Can't add nodes! You must first create the graph, using createGraph().\n");
        return;
    }
    if (graph->vertices == 0)
    {
        graph->adjacencyList = (Node **)malloc(sizeof(Node *));
        graph->visited = (int *)malloc(sizeof(int));
        graph->values = (int *)malloc(sizeof(int));
        graph->setValues = (int *)malloc(sizeof(int));
    }
    else
    {
        graph->adjacencyList = (Node **)realloc(graph->adjacencyList, (size_t)(graph->vertices + 1) * sizeof(Node *));
        graph->visited = (int *)realloc(graph->visited, (size_t)(graph->vertices + 1) * sizeof(int));
        graph->values = (int *)realloc(graph->values, (size_t)(graph->vertices + 1) * sizeof(int));
        graph->setValues = (int *)realloc(graph->setValues, (size_t)(graph->vertices + 1) * sizeof(int));
    }
    checkAllocation(graph->adjacencyList);
    checkAllocation(graph->visited);
    checkAllocation(graph->values);
    checkAllocation(graph->setValues);
    graph->adjacencyList[graph->vertices] = NULL;
    graph->visited[graph->vertices] = 0;
    graph->values[graph->vertices] = 0;
    graph->setValues[graph->vertices] = 0;
    graph->vertices++;
}

void setValue(Graph *graph, int index)
{
    printf("Introdu valoarea pentru nodul %d: ", index);
    scanf("%d", &graph->values[index]);
    graph->setValues[index] = 1;
}
// function that adds one-way edge between 2 nodes (directed graph)
int addOneEdge(Graph *graph, int sourceIndex, int destinationIndex, int weight)
{
    if (isEmpty(graph))
    {
        puts("The graph is NULL. Cant add edge! You must first create the graph. Use createGraph().\n");
        return 0;
    }
    if (sourceIndex == destinationIndex)
    {
        puts("You cant add an edge between one and the same node.\n");
        return 0;
    }
    if (sourceIndex < 0 || destinationIndex < 0)
    {
        puts("Source index or destination Index is negative. If you want to isolate a node, just don't call this function mentioning it and set its value manually!");
        return 0;
    }
    // Dinamically allocate memory for as many nodes as necessary if the specified indexes are bigger than the current number of vertices
    if (sourceIndex > graph->vertices - 1 || destinationIndex > graph->vertices - 1)
        for (int i = graph->vertices; i < (sourceIndex > destinationIndex ? sourceIndex + 1 : destinationIndex + 1); i++)
            allocateNode(graph);

    Node *neighbours = graph->adjacencyList[sourceIndex];
    while (neighbours)
    {
        if (neighbours->index == destinationIndex)
        {
            printf("Tried adding edge between nodes %d and %d, but there is already an edge!\n", sourceIndex, destinationIndex);
            return 0;
        }
        neighbours = neighbours->next;
    }

    // Create the node to be added in the adjacency list of the source node
    Node *node = createNode(destinationIndex);
    checkAllocation(node);
    node->next = graph->adjacencyList[sourceIndex];
    node->weight = weight;
    graph->adjacencyList[sourceIndex] = node;

    // removed so that we work with indexes only
    // if(!graph->setValues[sourceIndex])
    //     setValue(graph,sourceIndex);
    // if(!graph->setValues[destinationIndex])
    //     setValue(graph,destinationIndex);
    return 1;
}

// function that adds two-way edge between 2 nodes (undirected graph)
void addTwoEdges(Graph *graph, int sourceIndex, int destinationIndex, int weight)
{
    if (isEmpty(graph))
    {
        puts("The graph is NULL. Can't add edge! You must first create the graph. Use createGraph().\n");
        return;
    }
    if (addOneEdge(graph, sourceIndex, destinationIndex, weight))
        addOneEdge(graph, destinationIndex, sourceIndex, weight);
}

void printGraph(Graph *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i++)
    {
        Node *neighbour = graph->adjacencyList[i];
        printf("%d: ", i);
        while (neighbour)
        {
            printf("%d ", neighbour->index);
            neighbour = neighbour->next;
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

// Loads edges from a CSV file and returns the number of edges
void loadEdges(const char *filename, Graph **graph)
{
    if (*graph)
        freeGraph(*graph);

    *graph = createGraph();

    FILE *input = fopen(filename, "rb");
    if (!input)
    {
        fprintf(stderr, "Cannot open input file.\n");
        exit(1);
    }

    // Read entire file into memory
    fseek(input, 0L, SEEK_END);
    size_t len = (size_t)ftell(input);
    fseek(input, 0L, SEEK_SET);
    char *s = malloc(len + 1);
    fread(s, sizeof(char), len, input);
    s[len] = '\0';
    fclose(input);

    // Parse CSV values using ";" or "\n" as delimiters
    char *p = strtok(s, ";\n");
    while (p)
    {
        int src = atoi(p);
        p = strtok(NULL, ";\n");
        int dest = atoi(p);
        p = strtok(NULL, ";\n");
        int weight = atoi(p);

        addOneEdge(*graph, src, dest, weight);

        p = strtok(NULL, ";\n");
    }

    free(s);
}

int *dijkstraAlgorithm(Graph *graph, int start)
{
    int *dist = malloc(sizeof(int) * (size_t)graph->vertices);
    int *visited = malloc(sizeof(int) * (size_t)graph->vertices);

    for (int i = 0; i < graph->vertices; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int count = 0; count < graph->vertices - 1; count++)
    {
        int min = INT_MAX, u = -1;

        // Find the unvisited vertex with the smallest distance
        for (int v = 0; v < graph->vertices; v++)
        {
            if (!visited[v] && dist[v] <= min)
            {
                min = dist[v];
                u = v;
            }
        }

        if (u == -1)
            break; // No more reachable vertices
        visited[u] = 1;

        // Update distances of neighbors
        Node *neighbor = graph->adjacencyList[u];
        while (neighbor)
        {
            int v = neighbor->index;
            int weight = neighbor->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }
            neighbor = neighbor->next;
        }
    }

    // print all the distances
    // printf("Shortest distances from node %d:\n", start);
    // for (int i = 0; i < graph->vertices; i++) {
    //     if (dist[i] == INT_MAX)
    //         printf("Node %d: INF\n", i);
    //     else
    //         printf("Node %d: %d\n", i, dist[i]);
    // }

    // free(dist);
    free(visited);
    return dist;
}

void dijkstra(Graph *graph, int start, int destination)
{
    printf("Dijkstra -> ");
    if (start > graph->vertices - 1)
    {
        printf("Graful nu contine nodul start.\n");
    }
    else if (destination > graph->vertices - 1)
    {
        printf("Graful nu contine nodul destinatie.\n");
    }
    else
    {
        int *dist = dijkstraAlgorithm(graph, start);
        if (dist[destination] == INT_MAX)
        {
            printf("Nu exista drum de la %d la %d.\n", start, destination);
        }
        else
        {
            printf("Distanta de la nodul %d la %d este %d.\n", start, destination, dist[destination]);
        }

        free(dist);
    }
}

int *bellmanFordAlgorithm(Graph *graph, int start)
{
    int V = graph->vertices;
    int *dist = malloc(sizeof(int) * (size_t)V);

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++)
    {
        for (int u = 0; u < V; u++)
        {
            Node *neighbor = graph->adjacencyList[u];
            while (neighbor)
            {
                int v = neighbor->index;
                int weight = neighbor->weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                }
                neighbor = neighbor->next;
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < V; u++)
    {
        Node *neighbor = graph->adjacencyList[u];
        while (neighbor)
        {
            int v = neighbor->index;
            int weight = neighbor->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                printf("Graficul contine un ciclu negativ. Nu putem afisa cea mai scurta cale.\n");
                free(dist);
                return NULL;
            }
            neighbor = neighbor->next;
        }
    }

    // Print all distances
    // printf("Shortest distances from node %d using Bellman-Ford:\n", start);
    // for (int i = 0; i < V; i++) {
    //     if (dist[i] == INT_MAX)
    //         printf("Node %d: INF\n", i);
    //     else
    //         printf("Node %d: %d\n", i, dist[i]);
    // }

    // free(dist);
    return dist;
}

void bellmanFord(Graph *graph, int start, int destination)
{
    printf("Bellman Ford -> ");
    if (start > graph->vertices - 1)
    {
        printf("Graful nu contine nodul start.\n");
    }
    else if (destination > graph->vertices - 1)
    {
        printf("Graful nu contine nodul destinatie.\n");
    }
    else
    {
        int *dist = bellmanFordAlgorithm(graph, start);

        if (dist)
        {
            if (dist[destination] == INT_MAX)
            {
                printf("Nu exista drum de la %d la %d.\n", start, destination);
            }
            else
            {
                printf("Distanta de la %d la %d este %d.\n", start, destination, dist[destination]);
            }
            free(dist);
        }
    }
}

int main()
{
    Graph *graph = NULL;

    printf("Rulam Dijkstra si Bellman Ford pe graful de la tema 8:\n");
    loadEdges(INPUT_TEMA8, &graph);
    dijkstra(graph, 0, 14);
    bellmanFord(graph, 5, 13);

    printf("\nRulam Dijkstra si Bellman Ford pe graful de la input1.csv:\n");
    loadEdges(INPUT_1, &graph);
    Node *nod=graph->adjacencyList[5];
    printf("%d: ",5);
    while(nod)
    {
        printf("%d ",nod->index);
        nod=nod->next;
    }
    puts("");
    dijkstra(graph, 2, 12);
    bellmanFord(graph, 5, 6);

    printf("\nRulam Bellman Ford pe graful de la input2.csv:\n");
    loadEdges(INPUT_2, &graph);
    bellmanFord(graph, 15, 16);
    return 0;
}