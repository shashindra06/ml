#include <stdio.h>

#define MAX_N 100
#define MAX_W 1000

int main() {
    int N, W;
    int weights[MAX_N];
    int values[MAX_N];
    int dp[MAX_W + 1];

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

    // Read N and W
    if (fscanf(inputFile, "%d %d", &N, &W) != 2 || N <= 0 || N > MAX_N || W <= 0 || W > MAX_W) {
        printf("Error: invalid N or W in input.txt\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    // Read N items (weight, value)
    for (int i = 0; i < N; i++) {
        if (fscanf(inputFile, "%d %d", &weights[i], &values[i]) != 2) {
            printf("Error: invalid item format in input.txt\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
    }

    fclose(inputFile);

    // Initialize DP table
    for (int w = 0; w <= W; w++) {
        dp[w] = 0;
    }

    // Fill DP table
    for (int i = 0; i < N; i++) {
        for (int w = W; w >= weights[i]; w--) {
            if (dp[w - weights[i]] + values[i] > dp[w]) {
                dp[w] = dp[w - weights[i]] + values[i];
            }
        }
    }

    // Backtrack to find which items were selected
    int remainingW = W;
    int selected[MAX_N] = {0};

    for (int i = N - 1; i >= 0; i--) {
        if (remainingW >= weights[i] && dp[remainingW] == dp[remainingW - weights[i]] + values[i]) {
            selected[i] = 1;
            remainingW -= weights[i];
        }
    }

    // Write results to output.txt
    fprintf(outputFile, "%d\n", dp[W]);  // Maximum value

    for (int i = 0; i < N; i++) {
        fprintf(outputFile, "%d\n", selected[i]);  // Item selection (1=selected, 0=not)
    }

    fclose(outputFile);
    return 0;
}
