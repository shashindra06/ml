#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20
#define MAX_CYCLE 100

int graph[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int max_cycle = 0, min_cycle = MAX_VERTICES + 1;

void save_cycle(FILE *out, int path[], int len) {
    fprintf(out, "Cycle: ");
    for (int i = 0; i < len; i++) fprintf(out, "%d ", path[i]);
    fprintf(out, "(length: %d)\n", len);
    
    if (len > max_cycle) max_cycle = len;
    if (len < min_cycle) min_cycle = len;
}

bool has_cycle(int path[], int len, int curr) {
    for (int i = 0; i < len; i++) if (path[i] == curr) return true;
    return false;
}

void find_cycles(int u, int path[], int path_len, int V, FILE *out) {
    visited[u] = true;
    path[path_len] = u;
    
    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (v == path[0] && path_len > 2) {
                // **NOW WRITING TO OUTPUT FILE**
                save_cycle(out, path, path_len);
            }
            else if (!visited[v] && !has_cycle(path, path_len, v)) {
                find_cycles(v, path, path_len + 1, V, out);
            }
        }
    }
    
    visited[u] = false;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int V;
    fscanf(in, "%d", &V);
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(in, "%d", &graph[i][j]);
        }
        visited[i] = false;
    }
    fclose(in);
    
    fprintf(out, "All Cycles Found:\n\n");
    int path[MAX_VERTICES];
    
    for (int i = 0; i < V; i++) {
        find_cycles(i, path, 0, V, out);
    }
    
    fprintf(out, "\n=== SUMMARY ===\n");
    fprintf(out, "LONGEST cycle: %d vertices\n", max_cycle);
    fprintf(out, "SHORTEST cycle: %d vertices\n", min_cycle);
    
    fclose(out);
    printf("All cycles written to output.txt\n");
    return 0;
}
