#include <stdio.h>

#define MAX_N 100

int n, e;
int graph[MAX_N][MAX_N];
int color[MAX_N];
int maxColors;

int isSafe(int v, int c) {
    for (int u = 0; u < n; u++) {
        if (graph[v][u] && color[u] == c)
            return 0;
    }
    return 1;
}

int graphColoringUtil(int v) {
    if (v == n)
        return 1;

    for (int c = 1; c <= maxColors; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            if (graphColoringUtil(v + 1))
                return 1;
            color[v] = 0;
        }
    }
    return 0;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    fscanf(inputFile, "%d %d %d", &n, &e, &maxColors);

    for (int i = 0; i < n; i++) {
        color[i] = 0;
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < e; i++) {
        int u, v;
        fscanf(inputFile, "%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    fclose(inputFile);

    if (graphColoringUtil(0)) {
        fprintf(outputFile, "Graph can be colored with %d colors\n", maxColors);
        fprintf(outputFile, "Coloring of vertices:\n");
        for (int i = 0; i < n; i++) {
            fprintf(outputFile, "Vertex %d --> Color %d\n", i, color[i]);
        }
    } else {
        fprintf(outputFile, "Graph cannot be colored with %d colors\n", maxColors);
    }

    fclose(outputFile);
    return 0;
}
