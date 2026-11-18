#include <stdio.h>
#include <string.h>

#define d 256   // number of characters in input alphabet
#define q 101   // a prime number for hashing
#define MAX_LEN 1000

void rabinKarpToFile(char pat[], char txt[], FILE *out) {
    int m = strlen(pat);
    int n = strlen(txt);
    int h = 1, p = 0, t = 0;

    if (m == 0 || n == 0 || m > n)
        return;

    // h = d^(m-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Initial hash values
    for (int i = 0; i < m; i++) {
        p = (d * p + (unsigned char)pat[i]) % q;
        t = (d * t + (unsigned char)txt[i]) % q;
    }

    // Slide over text
    for (int i = 0; i <= n - m; i++) {

        if (p == t) { // hash match
            int j = 0;
            while (j < m && txt[i + j] == pat[j]) j++;
            if (j == m)
                fprintf(out, "Pattern found at index %d\n", i);
        }

        // next hash
        if (i < n - m) {
            t = (d * (t - (unsigned char)txt[i] * h)
                 + (unsigned char)txt[i + m]) % q;
            if (t < 0) t += q;
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

    rabinKarpToFile(pattern, text, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
