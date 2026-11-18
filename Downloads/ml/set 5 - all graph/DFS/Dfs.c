#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int disc[MAX_VERTICES], low[MAX_VERTICES], parent[MAX_VERTICES];
int time_stamp = 0;
FILE *out;

void DFS(int u, int V) {
    visited[u] = true;
    disc[u] = low[u] = time_stamp++;
    
    for (int v = 0; v < V; v++) {
        if (graph[u][v] == 0) continue;
        
        if (!visited[v]) {
            parent[v] = u;
            DFS(v, V);
            
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
            
            // Tree edge
            if (parent[v] == u) {
                fprintf(out, "Tree edge: %d -> %d\n", u, v);
            }
            // Back edge
            else if (v == parent[u]) {
                fprintf(out, "Back edge: %d -> %d\n", u, v);
            }
        }
        else if (v != parent[u]) {
            // Forward or Cross edge
            if (disc[v] > disc[u]) {
                fprintf(out, "Forward edge: %d -> %d\n", u, v);
            } else {
                fprintf(out, "Cross edge: %d -> %d\n", u, v);
            }
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    out = output;
    
    int V;
    fscanf(in, "%d", &V);
    
    // Read adjacency matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(in, "%d", &graph[i][j]);
        }
        visited[i] = false;
        disc[i] = -1;
        low[i] = -1;
        parent[i] = -1;
    }
    fclose(in);
    
    fprintf(output, "DFS Edge Classification (starting from vertex 0):\n\n");
    DFS(0, V);
    
    fclose(output);
    printf("DFS results written to output.txt\n");
    return 0;
}
