#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256
#define MAX_LEN 1000

int max(int a, int b) { return (a > b) ? a : b; }

// Build bad character table
void badCharHeuristic(char *pat, int m, int badchar[NO_OF_CHARS]) {
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < m; i++)
        badchar[(unsigned char)pat[i]] = i;
}

// Boyer–Moore search using bad character heuristic, output to file
void BMSearchToFile(char *txt, char *pat, FILE *out) {
    int m = strlen(pat);
    int n = strlen(txt);

    if (m == 0 || n == 0 || m > n)
        return;

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    int s = 0; // shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Move from right to left while matching
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        // If pattern found
        if (j < 0) {
            fprintf(out, "Pattern found at index %d\n", s);

            // Shift so that next character in text aligns correctly
            s += (s + m < n) ? m - badchar[(unsigned char)txt[s + m]] : 1;
        } else {
            // Shift using bad character rule
            s += max(1, j - badchar[(unsigned char)txt[s + j]]);
        }
    }
}

int main() {
    char text[MAX_LEN];
    char pattern[MAX_LEN];

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

    // Read first line as text
    if (fgets(text, MAX_LEN, inputFile) == NULL) {
        printf("Error: input.txt is empty or couldn't read text\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n')
        text[len - 1] = '\0';

    // Read second line as pattern
    if (fgets(pattern, MAX_LEN, inputFile) == NULL) {
        printf("Error: pattern line missing in input.txt\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    len = strlen(pattern);
    if (len > 0 && pattern[len - 1] == '\n')
        pattern[len - 1] = '\0';

    BMSearchToFile(text, pattern, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
