#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

// Build LPS (Longest Prefix Suffix) array
void computeLPSArray(char *pat, int m, int *lps) {
    int len = 0;      // length of previous longest prefix suffix
    lps[0] = 0;       // lps[0] is always 0
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // fall back to previous longest prefix
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search that writes matches to a file
void KMPSearchToFile(char *pat, char *txt, FILE *out) {
    int m = strlen(pat);
    int n = strlen(txt);

    if (m == 0 || n == 0 || m > n)
        return;

    int lps[m];
    computeLPSArray(pat, m, lps);

    int i = 0; // index for txt
    int j = 0; // index for pat

    while (i < n) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
        }

        if (j == m) {
            fprintf(out, "Pattern found at index %d\n", i - j);
            j = lps[j - 1];  // continue searching for next match
        } else if (i < n && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
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

    // Remove newline from text if present
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

    // Remove newline from pattern if present
    len = strlen(pattern);
    if (len > 0 && pattern[len - 1] == '\n')
        pattern[len - 1] = '\0';

    KMPSearchToFile(pattern, text, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
