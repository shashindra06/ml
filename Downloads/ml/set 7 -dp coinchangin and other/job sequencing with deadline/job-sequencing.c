#include <stdio.h>

#define MAX_JOBS 100

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    int n;
    int profit[MAX_JOBS], deadline[MAX_JOBS];
    int result[MAX_JOBS];
    
    fscanf(inputFile, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d", &profit[i], &deadline[i]);
    }
    fclose(inputFile);

    // Sort jobs by profit in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (profit[i] < profit[j]) {
                int tempProfit = profit[i];
                int tempDeadline = deadline[i];
                profit[i] = profit[j];
                deadline[i] = deadline[j];
                profit[j] = tempProfit;
                deadline[j] = tempDeadline;
            }
        }
    }

    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (deadline[i] > maxDeadline) maxDeadline = deadline[i];
    }

    int slot[maxDeadline];
    for (int i = 0; i < maxDeadline; i++) slot[i] = -1;

    int totalProfit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = deadline[i] - 1; j >= 0; j--) {
            if (j < maxDeadline && slot[j] == -1) {
                slot[j] = i;
                totalProfit += profit[i];
                result[i] = 1;
                break;
            }
        }
    }

    fprintf(outputFile, "Total Profit: %d\n", totalProfit);
    fprintf(outputFile, "Jobs selected (1=yes, 0=no):\n");
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "Job %d: %d\n", i, result[i]);
    }

    fclose(outputFile);
    return 0;
}
