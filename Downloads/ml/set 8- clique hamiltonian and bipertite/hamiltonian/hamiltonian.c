#include <stdio.h>

#define MAX_N 20  // limit for practical backtracking

int n, e;
int graph[MAX_N][MAX_N];
int path[MAX_N];

int isSafe(int v, int pos) {
    // Check if current vertex is adjacent to previous vertex in path
    if (!graph[path[pos - 1]][v])
        return 0;

    // Check if vertex is already included in path
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

int hamCycleUtil(int pos) {
    if (pos == n) {
        // Check if last vertex is connected to first to form a cycle
        if (graph[path[pos - 1]][path[0]])
            return 1;
        else
            return 0;
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamCycleUtil(pos + 1))
                return 1;
            // Backtrack
        }
    }
    return 0;
}

int containsHamiltonianCycle() {
    // Initialize path
    for (int i = 0; i < n; i++)
        path[i] = -1;
    path[0] = 0; // start at vertex 0
    return hamCycleUtil(1);
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    fscanf(inputFile, "%d %d", &n, &e);
    if (n > MAX_N) {
        fprintf(outputFile, "Graph too large (max %d vertices)\n", MAX_N);
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    for (int i = 0; i < e; i++) {
        int u, v;
        fscanf(inputFile, "%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    fclose(inputFile);

    if (containsHamiltonianCycle())
        fprintf(outputFile, "Graph contains a Hamiltonian cycle\n");
    else
        fprintf(outputFile, "No Hamiltonian cycle found\n");

    fclose(outputFile);
    return 0;
}
