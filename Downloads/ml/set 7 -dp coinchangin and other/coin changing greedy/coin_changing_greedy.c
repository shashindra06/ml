#include <stdio.h>

#define MAX_COINS 100

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    int n;          // number of coin denominations
    int coins[MAX_COINS];
    int amount;

    fscanf(inputFile, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &coins[i]);
    }

    fscanf(inputFile, "%d", &amount);

    fclose(inputFile);

    // Sort coins in decreasing order (simple selection sort)
    for (int i = 0; i < n -1; i++) {
        for (int j = i +1; j < n; j++) {
            if (coins[i] < coins[j]) {
                int temp = coins[i];
                coins[i] = coins[j];
                coins[j] = temp;
            }
        }
    }

    int countCoins[MAX_COINS] = {0};
    int remaining = amount;

    for (int i = 0; i < n && remaining > 0; i++) {
        if (coins[i] <= remaining) {
            countCoins[i] = remaining / coins[i];
            remaining = remaining % coins[i];
        }
    }

    if (remaining != 0) {
        fprintf(outputFile, "Amount cannot be represented exactly with given coins\n");
    } else {
        fprintf(outputFile, "Coins used to make amount %d:\n", amount);
        for (int i = 0; i < n; i++) {
            if (countCoins[i] > 0)
                fprintf(outputFile, "%d coin(s) of %d\n", countCoins[i], coins[i]);
        }
    }

    fclose(outputFile);
    return 0;
}
