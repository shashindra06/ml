#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int n, e;
int graph[MAX_N][MAX_N];

// For SCC (Tarjan's algorithm)
int disc[MAX_N], low[MAX_N], stackMember[MAX_N], stack[MAX_N];
int timeSCC = 0, topSCC = -1;

// For Biconnected Components, APs and Bridges (Undirected)
int timeBCC = 0, discBCC[MAX_N], lowBCC[MAX_N], parentBCC[MAX_N];
int ap[MAX_N]; // articulation points
int bridges[MAX_N][2], bridgeCount = 0;

void push(int v) {
    stack[++topSCC] = v;
    stackMember[v] = 1;
}

int pop() {
    int w = stack[topSCC--];
    stackMember[w] = 0;
    return w;
}

void SCCUtil(int u, FILE *outputFile) {
    disc[u] = low[u] = ++timeSCC;
    push(u);

    for (int v = 0; v < n; v++) {
        if (!graph[u][v]) continue;
        if (disc[v] == -1) {
            SCCUtil(v, outputFile);
            if(low[v] < low[u]) low[u] = low[v];
        } else if (stackMember[v]) {
            if(disc[v] < low[u]) low[u] = disc[v];
        }
    }

    // If u is head node of SCC
    if (low[u] == disc[u]) {
        fprintf(outputFile, "SCC: ");
        int w = -1;
        do {
            w = pop();
            fprintf(outputFile, "%d ", w);
        } while (w != u);
        fprintf(outputFile, "\n");
    }
}

// For Biconnected Components: APs and Bridges DFS
void BCCUtil(int u, FILE *outputFile) {
    discBCC[u] = lowBCC[u] = ++timeBCC;
    int children = 0;

    for (int v = 0; v < n; v++) {
        if (!graph[u][v]) continue;

        if (discBCC[v] == -1) {
            children++;
            parentBCC[v] = u;
            BCCUtil(v, outputFile);

            if (lowBCC[v] < lowBCC[u]) lowBCC[u] = lowBCC[v];

            if (parentBCC[u] == -1 && children > 1)
                ap[u] = 1;

            if (parentBCC[u] != -1 && lowBCC[v] >= discBCC[u])
                ap[u] = 1;

            if (lowBCC[v] > discBCC[u]) {
                bridges[bridgeCount][0] = u;
                bridges[bridgeCount][1] = v;
                bridgeCount++;
            }
        }
        else if (v != parentBCC[u] && discBCC[v] < lowBCC[u]) {
            lowBCC[u] = discBCC[v];
        }
    }
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    int u, v;
    for (int i = 0; i < e; i++) {
        fscanf(inputFile, "%d %d", &u, &v);
        graph[u][v] = 1; // Directed graph edge
    }

    fclose(inputFile);

    // Strongly Connected Components (Tarjan's)
    for (int i = 0; i < n; i++) {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = 0;
    }
    timeSCC = 0; topSCC = -1;
    fprintf(outputFile, "Strongly Connected Components:\n");
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            SCCUtil(i, outputFile);
        }
    }

    // For articulation points and bridges, we consider the underlying undirected graph
    // Build undirected graph from directed
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = (graph[i][j] || graph[j][i]) ? 1 : 0;

    for (int i = 0; i < n; i++) {
        discBCC[i] = -1;
        lowBCC[i] = -1;
        parentBCC[i] = -1;
        ap[i] = 0;
    }
    timeBCC = 0; bridgeCount = 0;

    for (int i = 0; i < n; i++) {
        if (discBCC[i] == -1) {
            BCCUtil(i, outputFile);
        }
    }

    fprintf(outputFile, "\nArticulation Points:\n");
    int apCount = 0;
    for (int i = 0; i < n; i++) {
        if (ap[i]) {
            fprintf(outputFile, "%d ", i);
            apCount++;
        }
    }
    if (apCount == 0)
        fprintf(outputFile, "None");
    fprintf(outputFile, "\n");

    fprintf(outputFile, "\nBridges:\n");
    if (bridgeCount == 0) {
        fprintf(outputFile, "None\n");
    } else {
        for (int i = 0; i < bridgeCount; i++) {
            fprintf(outputFile, "%d - %d\n", bridges[i][0], bridges[i][1]);
        }
    }

    fclose(outputFile);
    return 0;
}
