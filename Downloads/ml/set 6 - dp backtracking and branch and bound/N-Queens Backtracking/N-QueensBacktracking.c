#include <stdio.h>

#define MAX_N 12

int N;
int board[MAX_N][MAX_N];
int totalSolutions = 0;
FILE *outputFile;

int isSafe(int row, int col) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col] == 1)
            return 0;

    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return 0;

    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j] == 1)
            return 0;

    return 1;
}

void printSolution() {
    fprintf(outputFile, "Solution %d:\n", ++totalSolutions);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(outputFile, "%d ", board[i][j]);
        }
        fprintf(outputFile, "\n");
    }
    fprintf(outputFile, "\n");
}

void solveNQueens(int row) {
    // Base case: all queens placed
    if (row == N) {
        printSolution();
        return;
    }

    // Try placing queen in each column of current row
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            solveNQueens(row + 1);
            board[row][col] = 0;  // backtrack
        }
    }
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (!inputFile) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }
    if (!outputFile) {
        printf("Error: Could not create/open output.txt\n");
        fclose(inputFile);
        return 1;
    }

    // Read N
    if (fscanf(inputFile, "%d", &N) != 1 || N <= 0 || N > MAX_N) {
        printf("Error: invalid N in input.txt (1 <= N <= %d)\n", MAX_N);
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    fclose(inputFile);

    // Initialize board
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    fprintf(outputFile, "N-Queens solutions for N=%d\n", N);
    fprintf(outputFile, "Total solutions found: %d\n\n", totalSolutions);

    // Solve
    solveNQueens(0);

    // Update total solutions count at end
    rewind(outputFile);
    char line[100];
    int lineCount = 0;
    while (fgets(line, sizeof(line), outputFile)) {
        lineCount++;
    }
    fseek(outputFile, 0, SEEK_SET);
    fprintf(outputFile, "N=%d: Total solutions = %d\n\n", N, totalSolutions);

    fclose(outputFile);
    printf("Found %d solutions for N=%d. Check output.txt\n", totalSolutions, N);
    return 0;
}
