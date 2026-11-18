#include <stdio.h>

#define MAX_POINTS 1000

typedef struct {
    int x;
    int y;
} Point;

// To find orientation of ordered triplet (p, q, r).
// Returns:
// 0 -> collinear
// 1 -> clockwise
// 2 -> counterclockwise
int orientation(Point p, Point q, Point r) {
    long val = (long)(q.y - p.y) * (r.x - q.x) -
               (long)(q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Convex hull using Jarvis March, writing result to file
void convexHullToFile(Point points[], int n, FILE *out) {
    if (n < 3)
        return;

    int hullIdx[MAX_POINTS];
    int hullSize = 0;

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[l].x ||
           (points[i].x == points[l].x && points[i].y < points[l].y)) {
            l = i;
        }
    }

    // Start from leftmost point, move counterclockwise
    int p = l, q;
    do {
        hullIdx[hullSize++] = p;

        // Choose a candidate for next point
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            // If i is more counterclockwise than current q, update q
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }

        p = q;
    } while (p != l && hullSize < MAX_POINTS);

    // Write hull points to output file
    for (int i = 0; i < hullSize; i++) {
        Point h = points[hullIdx[i]];
        fprintf(out, "%d %d\n", h.x, h.y);
    }
}

int main() {
    Point points[MAX_POINTS];
    int n;

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

    // Read number of points
    if (fscanf(inputFile, "%d", &n) != 1 || n <= 0 || n > MAX_POINTS) {
        printf("Error: invalid number of points in input.txt\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    // Read N points
    for (int i = 0; i < n; i++) {
        if (fscanf(inputFile, "%d %d", &points[i].x, &points[i].y) != 2) {
            printf("Error: invalid point format in input.txt\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
    }

    convexHullToFile(points, n, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
