#include <stdio.h>

#define MAX_N 50

int n, e, m;
int graph[MAX_N][MAX_N];

int isSafe(int v, int clique[], int size) {
    for (int i = 0; i < size; i++) {
        if (!graph[v][clique[i]])
            return 0;
    }
    return 1;
}

int findClique(int clique[], int pos, int start) {
    if (pos == m) return 1;

    for (int v = start; v < n; v++) {
        if (isSafe(v, clique, pos)) {
            clique[pos] = v;
            if (findClique(clique, pos + 1, v + 1))
                return 1;
        }
    }
    return 0;
}

int containsClique() {
    int clique[m];
    return findClique(clique, 0, 0);
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) {
        // Cannot open input file, nothing else to do
        return 1;
    }

    FILE *outputFile = fopen("output.txt", "w"); // open in write mode to overwrite
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    fscanf(inputFile, "%d %d %d", &n, &e, &m);

    if (m > n) {
        fprintf(outputFile, "Clique size m cannot be greater than n\n");
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

    if (containsClique())
        fprintf(outputFile, "Graph contains a clique of size %d\n", m);
    else
        fprintf(outputFile, "No clique of size %d found\n", m);

    fclose(outputFile);
    return 0;
}
