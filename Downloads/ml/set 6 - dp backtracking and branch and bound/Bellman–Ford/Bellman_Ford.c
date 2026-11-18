#include <stdio.h>
#include <limits.h>

#define MAX_V 1000
#define MAX_E 2000
#define INF INT_MAX

typedef struct {
    int u;
    int v;
    int w;
} Edge;

int main() {
    int V, E;
    Edge edges[MAX_E];
    int dist[MAX_V];
    int source;

    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (!inputFile) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }
    if (!outputFile) {
        printf("Error: Could not create/open output.txt\n");
        fclose(inputFile);
        return 1;
    }

    // Read V and E
    if (fscanf(inputFile, "%d %d", &V, &E) != 2 || V <= 0 || V > MAX_V || E < 0 || E > MAX_E) {
        printf("Error: invalid V or E in input.txt\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    // Read edges u v w
    for (int i = 0; i < E; i++) {
        if (fscanf(inputFile, "%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w) != 3) {
            printf("Error: invalid edge format in input.txt\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
        if (edges[i].u < 0 || edges[i].u >= V || edges[i].v < 0 || edges[i].v >= V) {
            printf("Error: vertex index out of range in input.txt\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
    }

    // Read source vertex
    if (fscanf(inputFile, "%d", &source) != 1 || source < 0 || source >= V) {
        printf("Error: invalid source vertex in input.txt\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    fclose(inputFile);

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[source] = 0;

    // Relax edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        int updated = 0;
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }
        // Early stop if no update in this pass
        if (!updated)
            break;
    }

    // Check for negative-weight cycle reachable from source
    int hasNegCycle = 0;
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            hasNegCycle = 1;
            break;
        }
    }

    if (hasNegCycle) {
        fprintf(outputFile, "Negative weight cycle detected from source\n");
    } else {
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF)
                fprintf(outputFile, "Vertex %d: INF\n", i);
            else
                fprintf(outputFile, "Vertex %d: %d\n", i, dist[i]);
        }
    }

    fclose(outputFile);
    return 0;
}
