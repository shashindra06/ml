#include <stdio.h>

#define MAX_N 100

int n, e;
int graph[MAX_N][MAX_N];
int indegree[MAX_N];
int topoOrder[MAX_N];

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    fscanf(inputFile, "%d %d", &n, &e);

    for (int i = 0; i < n; i++) {
        indegree[i] = 0;
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    for (int i = 0; i < e; i++) {
        int u, v;
        fscanf(inputFile, "%d %d", &u, &v);
        graph[u][v] = 1;
        indegree[v]++;
    }

    fclose(inputFile);

    int queue[MAX_N], front = 0, rear = 0;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0)
            queue[rear++] = i;
    }

    int count = 0;
    while (front < rear) {
        int u = queue[front++]; 
        topoOrder[count++] = u;

        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                indegree[v]--;
                if (indegree[v] == 0)
                    queue[rear++] = v;
            }
        }
    }

    if (count != n) {
        fprintf(outputFile, "Graph has a cycle, topological sort not possible\n");
    } else {
        fprintf(outputFile, "Topological Order:\n");
        for (int i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", topoOrder[i]);
        }
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    return 0;
}
