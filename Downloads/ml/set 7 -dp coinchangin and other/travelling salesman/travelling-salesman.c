#include <stdio.h>
#include <limits.h>

#define MAX_N 20  // Limiting to 20 for practical runtime

int n;
int dist[MAX_N][MAX_N];
int VISITED_ALL;
int memo[MAX_N][1 << MAX_N];

int tsp(int pos, int mask) {
    if (mask == VISITED_ALL)
        return dist[pos][0];

    if (memo[pos][mask] != -1)
        return memo[pos][mask];

    int ans = INT_MAX;

    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(city, mask | (1 << city));
            if (newAns < ans)
                ans = newAns;
        }
    }
    return memo[pos][mask] = ans;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    fscanf(inputFile, "%d", &n);
    if (n > MAX_N) {
        fprintf(outputFile, "Node count exceeds max supported (%d)\n", MAX_N);
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(inputFile, "%d", &dist[i][j]);

    fclose(inputFile);

    VISITED_ALL = (1 << n) - 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < (1 << n); j++)
            memo[i][j] = -1;

    int minCost = tsp(0, 1 << 0);

    fprintf(outputFile, "Minimum cost of travelling salesman: %d\n", minCost);

    fclose(outputFile);
    return 0;
}
