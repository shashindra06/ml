#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_VERTICES 100
#define INF INT_MAX / 2

typedef struct {
    int vertex;
    int weight;
} Edge;

typedef struct {
    int dist[MAX_VERTICES];
    int prev[MAX_VERTICES];
    int visited[MAX_VERTICES];
} DijkstraState;

void dijkstra(FILE *input_file, FILE *output_file, int num_vertices, int start_vertex) {
    DijkstraState state = {0};
    int graph[MAX_VERTICES][MAX_VERTICES];
    
    // Initialize graph with infinity
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            graph[i][j] = INF;
        }
        state.dist[i] = INF;
        state.prev[i] = -1;
        state.visited[i] = 0;
    }
    
    // Read edges from input file - REWIND and read properly
    rewind(input_file);
    printf("Reading edges from input file...\n");
    int u, v, w, edge_count = 0;
    while (fscanf(input_file, "%d %d %d", &u, &v, &w) == 3) {
        if (u >= 0 && u < num_vertices && v >= 0 && v < num_vertices && w >= 0) {
            graph[u][v] = w;
            printf("Edge %d->%d weight %d\n", u, v, w);
            edge_count++;
        }
    }
    printf("Total edges read: %d\n", edge_count);
    
    // Set start vertex distance to 0
    state.dist[start_vertex] = 0;
    
    // Dijkstra's algorithm
    for (int count = 0; count < num_vertices; count++) {
        int min_dist = INF;
        int min_vertex = -1;
        
        // Find unvisited vertex with minimum distance
        for (int i = 0; i < num_vertices; i++) {
            if (!state.visited[i] && state.dist[i] < min_dist) {
                min_dist = state.dist[i];
                min_vertex = i;
            }
        }
        
        if (min_vertex == -1) break;
        
        state.visited[min_vertex] = 1;
        
        // Update distances to adjacent vertices
        for (int i = 0; i < num_vertices; i++) {
            if (!state.visited[i] && graph[min_vertex][i] != INF) {
                int new_dist = state.dist[min_vertex] + graph[min_vertex][i];
                if (new_dist < state.dist[i]) {
                    state.dist[i] = new_dist;
                    state.prev[i] = min_vertex;
                }
            }
        }
    }
    
    // Write results to output file
    fprintf(output_file, "Dijkstra's Algorithm Results\n");
    fprintf(output_file, "Number of vertices: %d\n", num_vertices);
    fprintf(output_file, "Start vertex: %d\n", start_vertex);
    fprintf(output_file, "Shortest distances:\n");
    fprintf(output_file, "Vertex\tDistance\tPath\n");
    fprintf(output_file, "------\t--------\t----\n");
    
    for (int i = 0; i < num_vertices; i++) {
        if (state.dist[i] == INF) {
            fprintf(output_file, "%d\tunreachable\t-\n", i);
        } else {
            fprintf(output_file, "%d\t%d\t", i, state.dist[i]);
            // Print simple path (just previous vertex for now)
            if (state.prev[i] != -1) {
                fprintf(output_file, "%d <- %d", i, state.prev[i]);
            }
            fprintf(output_file, "\n");
        }
    }
    
    printf("Results written to dijkstra_output.txt\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <num_vertices> <start_vertex>\n", argv[0]);
        printf("Input file format: u v w (one edge per line)\n");
        printf("Example: %s input.txt 4 0\n", argv[0]);
        return 1;
    }
    
    int num_vertices = atoi(argv[2]);
    int start_vertex = atoi(argv[3]);
    
    if (num_vertices > MAX_VERTICES || num_vertices <= 0 || start_vertex < 0 || start_vertex >= num_vertices) {
        printf("Error: Invalid number of vertices (%d) or start vertex (%d)\n", num_vertices, start_vertex);
        return 1;
    }
    
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error: Cannot open input file '%s'\n", argv[1]);
        return 1;
    }
    
    FILE *output_file = fopen("dijkstra_output.txt", "w");
    if (!output_file) {
        printf("Error: Cannot create output file 'dijkstra_output.txt'\n");
        fclose(input_file);
        return 1;
    }
    
    printf("Running Dijkstra's algorithm...\n");
    printf("Input file: %s\n", argv[1]);
    printf("Vertices: %d, Start: %d\n", num_vertices, start_vertex);
    
    dijkstra(input_file, output_file, num_vertices, start_vertex);
    
    fclose(input_file);
    fclose(output_file);
    
    printf("Completed! Check dijkstra_output.txt for results.\n");
    return 0;
}
