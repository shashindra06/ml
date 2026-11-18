#include <stdio.h>
#include <stdlib.h>

#define N 4       // 4x4 puzzle

typedef struct {
    int board[N][N];
    int blank_x;
    int blank_y;
    int g;      // cost so far
    int h;      // heuristic cost estimate
    int f;      // total cost (g+h)
} State;

int isGoal(State *s) {
    int val = 1;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i==N-1 && j==N-1) {
                if (s->board[i][j] != 0) return 0;
            } else {
                if (s->board[i][j] != val) return 0;
                val++;
            }
        }
    }
    return 1;
}

int heuristic(State *s) {
    // Example: count misplaced tiles (excluding blank)
    int misplaced = 0;
    int val = 1;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (s->board[i][j] != 0 && s->board[i][j] != val) misplaced++;
            val++;
        }
    }
    return misplaced;
}

// Placeholder for expanding nodes, priority queue, etc.

void printBoard(State *s, FILE *out) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            fprintf(out, "%d ", s->board[i][j]);
        }
        fprintf(out, "\n");
    }
}

int main() {
    State start;
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read start board
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            fscanf(inputFile, "%d", &start.board[i][j]);
            if (start.board[i][j] == 0) {
                start.blank_x = i;
                start.blank_y = j;
            }
        }
    }

    fclose(inputFile);

    start.g = 0;
    start.h = heuristic(&start);
    start.f = start.g + start.h;

    // TODO: implement branch-and-bound search here, producing moves to goal

    // For now, just print the starting board to output.txt
    fprintf(outputFile, "Start board:\n");
    printBoard(&start, outputFile);

    fclose(outputFile);
    printf("Skeleton read initial state. Complete solver needed.\n");
    return 0;
}
