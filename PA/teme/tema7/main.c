#include <stdlib.h>
#include <stdio.h>

#define QUEUE_MAX 50 // maximum number of elements in queue (default is defined in stacks_queues.h)
#define STACK_MAX 50

#include "stacks_queues.h" // my file containing queue and stack structures

struct node
{

    int index;
    struct node *next;
};
typedef struct node Node;

struct graph
{
    int vertices;
    int *values,*setValues; // values[i] is the value for node i and setValues[i]=0/1 whether a node's value has been set (for when the node is first created)
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
    graph->vertices = 0;
    graph->adjacencyList = NULL;
    graph->visited = NULL;
    graph->values = NULL;
    graph->setValues=NULL;
    graph->front = NULL;
    graph->rear = NULL;
    return graph;
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
    graph->adjacencyList[graph->vertices] = NULL;
    graph->visited[graph->vertices] = 0;
    graph->values[graph->vertices] = 0;
    graph->setValues[graph->vertices] = 0;
    graph->vertices++;
}

void setValue(Graph *graph,int index)
{
    printf("Introdu valoarea pentru nodul %d: ",index);
    scanf("%d",&graph->values[index]);
    graph->setValues[index]=1;
}
// function that adds one-way edge between 2 nodes (directed graph)
int addOneEdge(Graph *graph, int sourceIndex, int destinationIndex)
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
    if(sourceIndex < 0 || destinationIndex < 0)
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
            printf("Tried adding edge between nodes %d and %d, but there is already an edge!\n",sourceIndex,destinationIndex);
            return 0;
        }
        neighbours = neighbours->next;
    }

    // Create the node to be added in the adjacency list of the source node
    Node *node = createNode(destinationIndex);
    checkAllocation(node);
    node->next = graph->adjacencyList[sourceIndex];
    graph->adjacencyList[sourceIndex] = node;

    if(!graph->setValues[sourceIndex])
        setValue(graph,sourceIndex);
    if(!graph->setValues[destinationIndex])
        setValue(graph,destinationIndex);
    return 1;
}

// function that adds two-way edge between 2 nodes (undirected graph)
void addTwoEdges(Graph *graph, int sourceIndex, int destinationIndex)
{
    if (isEmpty(graph))
    {
        puts("The graph is NULL. Cant add edge! You must first create the graph. Use createGraph().\n");
        return;
    }
    if (addOneEdge(graph, sourceIndex, destinationIndex))
        addOneEdge(graph, destinationIndex, sourceIndex);
}

void insertEdges(Graph *graph, int edges, int isOriented)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edges, graph->vertices);
    for (i = 0; i < edges; i++)
    {
        scanf("%d%d", &src, &dest);
        if (!isOriented)
            addTwoEdges(graph, src, dest);
        else
            addOneEdge(graph, src, dest);
    }
}

void printGraph(Graph *graph)
{
    int i;
    for (i = 1; i < graph->vertices; i++)
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

// parcurgeri
void dfsAlgorithm(Graph *graph, int currentVertex)
{
    Node *neighbour = graph->adjacencyList[currentVertex];

    graph->visited[currentVertex] = 1;
    printf("%d->", currentVertex);

    while (neighbour != NULL)
    {
        if (graph->visited[neighbour->index] == 0)
        {
            dfsAlgorithm(graph, neighbour->index);
        }
        neighbour = neighbour->next;
    }
}
void DFS(Graph *graph,int currentVertex)
{
    dfsAlgorithm(graph,currentVertex);
    wipeVisitedList(graph);
}

void BFS(Graph *graph, int start)
{
    graph->visited[start] = 1;
    enqueue(&graph->front, &graph->rear, start);

    while (!isEmpty(graph->front))
    {
        int current = graph->front->data;
        dequeue(&graph->front, &graph->rear);
        printf("%d->", current);

        Node *neighbour = graph->adjacencyList[current];

        while (neighbour)
        {
            if (graph->visited[neighbour->index] == 0)
            {
                graph->visited[neighbour->index] = 1;
                enqueue(&graph->front, &graph->rear, neighbour->index);
            }
            neighbour = neighbour->next;
        }
    }
    wipeVisitedList(graph);
}

// EX2
int isPath(Graph *graph, int source, int destination) 
{
    if (source == destination)
        return 1;

    graph->visited[source] = 1;

    Node *neighbour = graph->adjacencyList[source];

    while (neighbour != NULL)
    {
        if (!graph->visited[neighbour->index])
        {
            if (isPath(graph, neighbour->index, destination))
                return 1; // Path found through neighbor
        }
        neighbour = neighbour->next;
    }

    return 0; // No path found through any neighbors
}

// EX3
// Function is called inside hasLoop() to count for the situation when the specified node is isolated, therefore it won't progress through the rest of graph
int hasLoopAlgorithm(Graph *graph, int parent, int current)
{
    graph->visited[current] = 1;
    Node *neighbour = graph->adjacencyList[current];

    while (neighbour)
    {
        if (!graph->visited[neighbour->index])
        {
            if (hasLoopAlgorithm(graph, current, neighbour->index))
            {
                return 1;
            }
        }
        else if (neighbour->index != parent)
        {
            return 1;
        }
        neighbour = neighbour->next;
    }

    return 0;
}

int hasLoop(Graph *graph, int parent, int current)
{
    // Check all nodes until one that is not isolated is reached
    for(int i=0;i<graph->vertices;i++)
        if(hasLoopAlgorithm(graph,i,i))
            return 1;
    return 0;
}

// EX4 cu chat gpt, efectiv nu pot. am citit si bineinteles ca am inteles, dar pur si simplu nu am reusit sa o fac eu :)
int max(int a, int b) {
    return a > b ? a : b;
}

// Helper function to find longest simple path between two nodes
int dfsLongestPath(Graph *graph, int current, int destination, int *visited) {
    if (current == destination) return 0; // reached destination

    visited[current] = 1;  
    int longest = -1;

    Node *neighbour = graph->adjacencyList[current];
    while (neighbour) {
        if (!visited[neighbour->index]) {
            int subPath = dfsLongestPath(graph, neighbour->index, destination, visited);
            if (subPath != -1) {
                longest = max(longest, 1 + subPath);
            }
        }
        neighbour = neighbour->next;
    }

    visited[current] = 0;
    return longest;
}

int findLongestValuePath(Graph *graph) {
    if (isEmpty(graph)) return -1;

    int minVal = 99;
    int maxVal = -10;

    // Find min and max values among nodes that have set values
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->setValues[i]) {
            if (graph->values[i] < minVal) minVal = graph->values[i];
            if (graph->values[i] > maxVal) maxVal = graph->values[i];
        }
    }

    // Get lists of all min and max nodes
    int *minNodes = malloc((size_t)(graph->vertices) * sizeof(int));
    int *maxNodes = malloc((size_t)(graph->vertices) * sizeof(int));
    int minCount = 0, maxCount = 0;

    for (int i = 0; i < graph->vertices; i++) {
        if (!graph->setValues[i]) continue;
        if (graph->values[i] == minVal) minNodes[minCount++] = i;
        if (graph->values[i] == maxVal) maxNodes[maxCount++] = i;
    }

    // If no valid min or max nodes were found, exit early
    if (minCount == 0 || maxCount == 0) {
        free(minNodes);
        free(maxNodes);
        return -1;
    }

    int *visited = calloc((size_t)(graph->vertices), sizeof(int));
    int longestPath = -1;

    for (int i = 0; i < minCount; i++) {
        for (int j = 0; j < maxCount; j++) {
            int len = dfsLongestPath(graph, minNodes[i], maxNodes[j], visited);
            longestPath = max(longestPath, len);
        }
    }

    free(minNodes);
    free(maxNodes);
    free(visited);

    return longestPath;
}


int main()
{
    puts("EXERCITIUL 1:\n");
    //  UNDIRECTED GRAPH
    Graph *graph = createGraph();

    addTwoEdges(graph, 1, 4);
    addTwoEdges(graph, 1, 5);
    addTwoEdges(graph, 4, 6);
    addTwoEdges(graph, 4, 3);
    addTwoEdges(graph, 2, 3);
    addTwoEdges(graph, 2, 6);
    addTwoEdges(graph, 3, 5);

    printf("\nDFS: "); DFS(graph,1);
    puts("");

    printf("BFS: "); BFS(graph,1);
    puts("");

    puts("\nEXERCITIUL 2:\n");
    // DIRECTED GRAPH
    Graph *ograph = createGraph();
    addOneEdge(ograph, 0, 1);
    addOneEdge(ograph, 0, 2);
    addOneEdge(ograph, 1, 3);
    addOneEdge(ograph, 1, 2);
    addOneEdge(ograph, 2, 3);
    addOneEdge(ograph, 3, 4);
    addOneEdge(ograph, 2, 4);

    printf("\nExista drum intre nodurile %d si %d? Raspuns: %d\n",2,4,isPath(graph,2,4));

    puts("\nEXERCITIUL 3:\n");
    wipeVisitedList(graph);
    printf("Exista cicluri in primul graf (da sau nu / 1 sau 0): %d.\n",hasLoop(graph,0,0));
    puts("\nEXERCITIUL 4:\n");
    printf("Cel mai lung drum de la cel mai mic nod la cel mai mare in primul graf este: %d.",findLongestValuePath(graph));

    return 0;
}