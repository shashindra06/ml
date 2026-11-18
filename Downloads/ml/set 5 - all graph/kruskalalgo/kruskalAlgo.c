#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 1000

typedef struct {
    int u, v, weight;
} Edge;

int parent[MAX_EDGES];
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void union_set(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[b] = a;
}

int compare(const void *a, const void *b) {
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    return ea->weight - eb->weight;
}

void kruskal(Edge edges[], int E, int V, FILE *out) {
    for (int i = 0; i < V; i++) parent[i] = i;

    qsort(edges, E, sizeof(Edge), compare);

    int count = 0, total_weight = 0;
    fprintf(out, "Edges in MST:\n");
    for (int i = 0; i < E && count < V - 1; i++) {
        int u_set = find(edges[i].u);
        int v_set = find(edges[i].v);
        if (u_set != v_set) {
            union_set(u_set, v_set);
            fprintf(out, "%d - %d : %d\n", edges[i].u, edges[i].v, edges[i].weight);
            total_weight += edges[i].weight;
            count++;
        }
    }
    fprintf(out, "Total MST weight: %d\n", total_weight);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Cannot open input.txt\n");
        return 1;
    }

    FILE *output = fopen("output.txt", "w");
    if (!output) {
        printf("Cannot create output.txt\n");
        fclose(input);
        return 1;
    }

    int V, E;
    fscanf(input, "%d %d", &V, &E);
    Edge edges[E];
    for (int i = 0; i < E; i++) {
        fscanf(input, "%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }
    fclose(input);

    kruskal(edges, E, V, output);
    fclose(output);
    printf("MST written to output.txt\n");

    return 0;
}
