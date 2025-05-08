#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

// Define input/output file paths
#define INPUT "input.csv"
#define OUTPUT_KRUSKAL "kruskal.csv"
#define OUTPUT_PRIM "prim.csv"
#define OUTPUT_DIFFERENCES "diferente.txt"

// ---------------- CSV INPUT FORMAT ----------------
// For each line the CSV input format describes an edge by the (source-destination) nodes pair and its weight
// 'SOURCE-NODE';'DESTINATION-NODE';'EDGE-WEIGHT'

// ---------------- Edge Input From CSV ----------------

// Dynamically adds an edge (src, dest, weight) to the edges array
void addEdge(int ***edges, size_t rows, int src, int dest, int weight)
{
    *edges = realloc(*edges, (rows + 1) * sizeof(int *));
    (*edges)[rows] = malloc(3 * sizeof(int));
    (*edges)[rows][0] = src;
    (*edges)[rows][1] = dest;
    (*edges)[rows][2] = weight;
}

// Loads edges from a CSV file and returns the number of edges
int loadEdges(const char *filename, int ***edges, int *numNodes)
{
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

    *edges = NULL;
    size_t rows = 0;
    int maxNode = 0;

    // Parse CSV values using ";" or "\n" as delimiters
    char *p = strtok(s, ";\n");
    while (p)
    {
        int src = atoi(p);
        p = strtok(NULL, ";\n");
        int dest = atoi(p);
        p = strtok(NULL, ";\n");
        int weight = atoi(p);

        addEdge(edges, rows++, src, dest, weight);

        if (src > maxNode) maxNode = src;
        if (dest > maxNode) maxNode = dest;

        p = strtok(NULL, ";\n");
    }

    *numNodes = maxNode + 1;
    free(s);
    return (int)rows;
}

// ---------------- Kruskal Implementation ----------------

// Comparator for qsort to sort edges by weight (ascending)
int comparator(const void *a, const void *b)
{
    int *edge1 = *(int **)a;
    int *edge2 = *(int **)b;
    return edge1[2] - edge2[2];
}

// Initializes parent and rank arrays for Union-Find
void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Find operation with path compression
int findParent(int parent[], int node)
{
    if (parent[node] != node)
        parent[node] = findParent(parent, parent[node]);
    return parent[node];
}

// Union by rank for Union-Find
void unionSet(int u, int v, int parent[], int rank[])
{
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (u != v)
    {
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else
        {
            parent[v] = u;
            rank[u]++;
        }
    }
}

// Constructs MST using Kruskal's algorithm and saves it to a CSV
void kruskalMST(int numNodes, int **edges, size_t rows)
{
    qsort(edges, rows, sizeof(edges[0]), comparator); // Sort edges by weight

    int *parent = malloc(numNodes * sizeof(int));
    int *rank = malloc(numNodes * sizeof(int));
    makeSet(parent, rank, numNodes);

    FILE *output = fopen(OUTPUT_KRUSKAL, "wt");
    if (!output)
    {
        fprintf(stderr, "Failed to create Kruskal output file!\n");
        exit(1);
    }

    int totalCost = 0;
    fprintf(output, "Edges in Minimum Spanning Tree (Kruskal):\n");
    printf("\nEdges in Minimum Spanning Tree (Kruskal):\n");
    for (size_t i = 0, count = 0; i < rows && count < numNodes - 1; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        // Add edge to MST if it connects different components
        if (findParent(parent, u) != findParent(parent, v))
        {
            unionSet(u, v, parent, rank);
            fprintf(output, "%d;%d;(cost:%d)\n", u, v, w);
            printf("%d - %d\t(cost: %d)\n", u, v, w);
            totalCost += w;
            count++;
        }
    }

    fprintf(output, "Total cost:%d\n", totalCost);
    printf("Total cost (Kruskal): %d\n", totalCost);
    fclose(output);
    free(parent);
    free(rank);
}

// ---------------- Prim Implementation ----------------

// Structures for adjacency list
typedef struct adjNode
{
    int dest;
    int weight;
    struct adjNode *next;
} AdjNode;

typedef struct
{
    AdjNode *head;
} AdjList;

// Create new adjacency list node
AdjNode *newAdjNode(int dest, int weight)
{
    AdjNode *node = malloc(sizeof(AdjNode));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

// Build adjacency list from edge list
AdjList *buildAdjList(int **edges, int numEdges, int numNodes)
{
    AdjList *adjList = malloc((size_t)numNodes * sizeof(AdjList));
    for (int i = 0; i < numNodes; i++)
        adjList[i].head = NULL;

    for (int i = 0; i < numEdges; i++)
    {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        // Add edge to both nodes (undirected graph)
        AdjNode *node1 = newAdjNode(v, w);
        node1->next = adjList[u].head;
        adjList[u].head = node1;
        AdjNode *node2 = newAdjNode(u, w);
        node2->next = adjList[v].head;
        adjList[v].head = node2;
    }

    return adjList;
}

// Find node with minimum key not yet included in MST
int minKey(int key[], bool mstSet[], int n)
{
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

// Output the MST built using Prim's algorithm
void printMSTPrim(int parent[], int **weights, int n)
{
    FILE *output = fopen(OUTPUT_PRIM, "wt");
    if (!output)
    {
        fprintf(stderr, "Failed to create Prim output file!\n");
        exit(1);
    }

    int totalCost = 0;
    fprintf(output, "Edges in Minimum Spanning Tree (Prim):\n");
    printf("\nEdges in Minimum Spanning Tree (Prim):\n");
    for (int i = 1; i < n; i++)
    {
        fprintf(output, "%d;%d;(cost:%d)\n", parent[i], i, weights[i][parent[i]]);
        printf("%d - %d\t(cost: %d)\n", parent[i], i, weights[i][parent[i]]);
        totalCost += weights[i][parent[i]];
    }

    fprintf(output, "Total cost:%d\n", totalCost);
    printf("Total cost (Prim): %d\n", totalCost);
    fclose(output);
}

// Constructs MST using Prim's algorithm
void primMST(int **edges, int numEdges, int numNodes)
{
    AdjList *adjList = buildAdjList(edges, numEdges, numNodes);

    // Initialization
    int *parent = malloc(numNodes * sizeof(int));
    int *key = malloc(numNodes * sizeof(int));
    bool *mstSet = malloc(numNodes * sizeof(bool));
    for (int i = 0; i < numNodes; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    // Main loop: construct MST node-by-node
    for (int count = 0; count < numNodes - 1; count++)
    {
        int u = minKey(key, mstSet, numNodes);
        mstSet[u] = true;

        // Update adjacent vertices
        AdjNode *temp = adjList[u].head;
        while (temp != NULL)
        {
            int v = temp->dest, weight = temp->weight;
            if (!mstSet[v] && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
            }
            temp = temp->next;
        }
    }

    // Build weight matrix for printing
    int **weightMatrix = malloc(numNodes * sizeof(int *));
    for (int i = 0; i < numNodes; i++)
        weightMatrix[i] = calloc(numNodes, sizeof(int));
    for (int i = 0; i < numEdges; i++)
    {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        weightMatrix[u][v] = w;
        weightMatrix[v][u] = w;
    }

    printMSTPrim(parent, weightMatrix, numNodes);

    // Free memory
    for (int i = 0; i < numNodes; i++)
    {
        AdjNode *current = adjList[i].head;
        while (current)
        {
            AdjNode *next = current->next;
            free(current);
            current = next;
        }
        free(weightMatrix[i]);
    }

    free(weightMatrix);
    free(adjList);
    free(parent);
    free(key);
    free(mstSet);
}

// Writes differences and similarities between Kruskal and Prim to file
void printDifferences()
{
    FILE *output = fopen(OUTPUT_DIFFERENCES, "wt");
    if (!output)
    {
        fprintf(stderr, "Failed to create differences file!");
        exit(1);
    }

    // Write theoretical comparison of the two algorithms
    fprintf(output,
        "                       Asemanari:\n"
        "1. Amandoi algoritmii determina arborele minim de acoperire;\n"
        "2. Funcționează doar pe grafuri ponderate, conexe si neorientate;\n"
        "3. Complexitatea lor poate fi similară în funcție de implementare (O(ElogE) sau O(E+VlogV)).\n\n"
        "                       Diferențe:\n"
        "Criteriu                   Kruskal                                     Prim\n"
        "Metodologie            Abordare pe muchii.                          Abordare pe noduri.\n"
        "Inițializare           Sortează toate muchiile.                     Pornește de la un nod sursă.\n"
        "Performanță            Mai rapid în grafuri sparte(sparse).         Mai eficient în grafuri dense.\n\n"
        "                       Avantaje:\n"
        "Kruskal:\n"
        "-  Ideal pentru grafuri cu multe noduri și puține muchii(sparse).\n"
        "-  Ușor de implementat folosind sortare și Union-Find.\n"
        "-  Flexibil: poate fi adaptat și pentru grafuri cu componente conexe multiple.\n\n"
        "Prim:\n"
        "-  Mai eficient în grafuri dense, mai ales cu implementare pe heap.\n"
        "-  Construiește arborele incremental, util pentru aplicații online.\n"
        "-  Poate fi mai intuitiv pentru aplicații geografice (hărți, rețele)."
    );
    fclose(output);
}

// Entry point
int main()
{
    int **edges = NULL;
    int numNodes = 0;
    int numEdges = loadEdges(INPUT, &edges, &numNodes); // Load graph

    kruskalMST(numNodes, edges, numEdges); // Run Kruskal
    primMST(edges, numEdges, numNodes);    // Run Prim

    // Free edge list
    for (int i = 0; i < numEdges; i++)
        free(edges[i]);
    free(edges);

    printDifferences(); // Output comparison
    return 0;
}
