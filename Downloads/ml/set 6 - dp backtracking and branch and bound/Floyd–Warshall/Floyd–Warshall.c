#include <stdio.h>

#define MAX_V 100
#define INF 99999

int main() {
    int dist[MAX_V][MAX_V];
    int N;

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

    if (fscanf(inputFile, "%d", &N) != 1 || N <= 0 || N > MAX_V) {
        printf("Error: invalid number of vertices in input.txt\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(inputFile, "%d", &dist[i][j]) != 1) {
                printf("Error: invalid matrix entry in input.txt\n");
                fclose(inputFile);
                fclose(outputFile);
                return 1;
            }
            // Replace -1 with INF to indicate no edge if used
            if (dist[i][j] == -1)
                dist[i][j] = INF;
        }
    }

    fclose(inputFile);

    // Floyd-Warshall algorithm
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Write results to output.txt, print INF if no path
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dist[i][j] == INF)
                fprintf(outputFile, "INF ");
            else
                fprintf(outputFile, "%d ", dist[i][j]);
        }
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    return 0;
}
