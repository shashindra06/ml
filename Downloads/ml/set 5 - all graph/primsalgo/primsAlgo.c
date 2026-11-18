#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF INT_MAX/2

int main(int argc, char *argv[]) {
    FILE *in = fopen(argc>1?argv[1]:"input.txt", "r");
    FILE *out = fopen("prim_output.txt", "w");
    
    int n; fscanf(in, "%d", &n);
    int graph[MAX_VERTICES][MAX_VERTICES];
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) fscanf(in, "%d", &graph[i][j]);
    
    int key[MAX_VERTICES], parent[MAX_VERTICES]; bool mst[MAX_VERTICES]={0};
    for(int i=0; i<n; i++) key[i]=INF, parent[i]=-1;
    key[0]=0;
    
    for(int c=0; c<n-1; c++) {
        int u=-1, min=INF;
        for(int v=0; v<n; v++) if(!mst[v] && key[v]<min) min=key[v], u=v;
        if(u==-1) break;
        mst[u]=1;
        for(int v=0; v<n; v++) if(graph[u][v] && !mst[v] && graph[u][v]<key[v])
            key[v]=graph[u][v], parent[v]=u;
    }
    
    fprintf(out, "Prim's MST:\n");
    for(int i=1; i<n; i++) if(parent[i]!=-1)
        fprintf(out, "%d-%d: %d\n", parent[i], i, graph[i][parent[i]]);
    
    fclose(in); fclose(out);
    return 0;
}
