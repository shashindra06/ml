#include <stdio.h>

#define MAX_N 100

int n, e;
int graph[MAX_N][MAX_N];
int color[MAX_N];

int isSafe(int v, int c) {
    for (int u = 0; u < n; u++) {
        if (graph[v][u]) {
            if (color[u] == c) return 0;
            if (color[u] == -1 && !isSafe(u, 1 - c)) return 0;
        }
    }
    return 1;
}

int isBipartiteUtil(int v) {
    color[v] = 0;
    for (int u = 0; u < n; u++) {
        if (graph[v][u]) {
            if (color[u] == -1) {
                if (!isBipartiteUtil(u)) return 0;
            } else if (color[u] == color[v]) {
                return 0;
            }
        }
    }
    return 1;
}

int isBipartite() {
    for (int i = 0; i < n; i++) color[i] = -1;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!isBipartiteUtil(i)) return 0;
        }
    }
    return 1;
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

    if (isBipartite())
        fprintf(outputFile, "Graph is bipartite\n");
    else
        fprintf(outputFile, "Graph is not bipartite\n");

    fclose(outputFile);
    return 0;
}
