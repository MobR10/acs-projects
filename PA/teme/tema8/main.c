#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "input.csv"

int comparator(const void *a, const void *b) {
    int *edge1 = *(int **)a;
    int *edge2 = *(int **)b;
    return edge1[2] - edge2[2];
}

void makeSet(int parent[], int rank[], int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int node) {
    if (parent[node] != node)
        parent[node] = findParent(parent, parent[node]);
    return parent[node];
}

void unionSet(int u, int v, int parent[], int rank[]) {
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (u != v) {
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }
}

int kruskalMST(int numNodes, int **edges, size_t rows) {
    qsort(edges, rows, sizeof(edges[0]), comparator);

    int *parent = malloc(numNodes * sizeof(int));
    int *rank = malloc(numNodes * sizeof(int));
    makeSet(parent, rank, numNodes);

    int totalCost = 0;
    printf("Muchiile din arborele minim de acoperire:\n");
    for (size_t i = 0, count = 0; i < rows && count < numNodes - 1; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        if (findParent(parent, u) != findParent(parent, v)) {
            unionSet(u, v, parent, rank);
            printf("  %d - %d (cost: %d)\n", u, v, w);
            totalCost += w;
            count++;
        }
    }

    free(parent);
    free(rank);
    return totalCost;
}

void addEdge(int ***edges, size_t rows, int src, int dest, int weight) {
    *edges = realloc(*edges, (rows + 1) * sizeof(int *));
    (*edges)[rows] = malloc(3 * sizeof(int));
    (*edges)[rows][0] = src;
    (*edges)[rows][1] = dest;
    (*edges)[rows][2] = weight;
}

int main() {
    FILE *input = fopen(INPUT, "rb");
    if (!input) {
        fprintf(stderr, "Nu se poate citi fișierul de intrare.\n");
        exit(1);
    }

    fseek(input, 0, SEEK_END);
    size_t len = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *buffer = malloc(len + 1);
    fread(buffer, 1, len, input);
    buffer[len] = '\0';
    fclose(input);

    int **edges = NULL;
    size_t rows = 0;
    int maxNode = 0;

    char *token = strtok(buffer, ";\n");
    while (token) {
        int src = atoi(token);
        token = strtok(NULL, ";\n");
        int dest = atoi(token);
        token = strtok(NULL, ";\n");
        int weight = atoi(token);

        addEdge(&edges, rows++, src, dest, weight);
        if (src > maxNode) maxNode = src;
        if (dest > maxNode) maxNode = dest;

        token = strtok(NULL, ";\n");
    }
    maxNode++; // numărul total de noduri

    int totalCost = kruskalMST(maxNode, edges, rows);
    printf("Costul total al arborelui: %d\n", totalCost);

    for (size_t i = 0; i < rows; i++)
        free(edges[i]);
    free(edges);
    free(buffer);

    return 0;
}
