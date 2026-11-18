#include <stdio.h>

#define MAX_N 20  // Backtracking works for small N (<=20)

int N, W;
int weights[MAX_N];
int values[MAX_N];
int maxValue = 0;
int bestSolution[MAX_N];

void knapsackBacktrack(int idx, int currW, int currV, int solution[]) {
    // Base case: end of items
    if (idx == N) {
        if (currV > maxValue) {
            maxValue = currV;
            for (int i = 0; i < N; i++)
                bestSolution[i] = solution[i];
        }
        return;
    }

    // Pruning: remaining items can't improve solution
    int remainingW = 0, remainingV = 0;
    for (int i = idx; i < N; i++) {
        remainingW += weights[i];
        remainingV += values[i];
    }
    if (currV + remainingV <= maxValue)
        return;

    // Don't include current item
    solution[idx] = 0;
    knapsackBacktrack(idx + 1, currW, currV, solution);

    // Include current item if possible
    if (currW + weights[idx] <= W) {
        solution[idx] = 1;
        knapsackBacktrack(idx + 1, currW + weights[idx], currV + values[idx], solution);
    }
}

int main() {
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
    if (fscanf(inputFile, "%d %d", &N, &W) != 2 || N <= 0 || N > MAX_N || W <= 0) {
        printf("Error: invalid N or W in input.txt (N <= %d for backtracking)\n", MAX_N);
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    // Read N items
    for (int i = 0; i < N; i++) {
        if (fscanf(inputFile, "%d %d", &weights[i], &values[i]) != 2) {
            printf("Error: invalid item format in input.txt\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
    }

    fclose(inputFile);

    // Run backtracking
    int solution[MAX_N] = {0};
    knapsackBacktrack(0, 0, 0, solution);

    // Write results
    fprintf(outputFile, "%d\n", maxValue);
    for (int i = 0; i < N; i++) {
        fprintf(outputFile, "%d\n", bestSolution[i]);
    }

    fclose(outputFile);
    return 0;
}
