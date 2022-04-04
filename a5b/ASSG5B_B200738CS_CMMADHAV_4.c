#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#define INF 10001
#define inf 10000000 
struct edge {
    int u;//src
    int v;//destination
    int w;//weight
};
typedef struct edge edge;
struct edgeList {
    edge edges[10000];
    int n;
};
typedef struct edgeList edgeList;

void print_matrix(int graph[][1001], int n){
    printf("DEBUG:\n");
    for(int i=0; i < n ;i++){
        for(int j=0; j< n ; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}
int bellmanFord(edgeList * E , int v){
    int dist[10000];
    for(int i=0; i < 10000; i++)
        dist[i] = 1000000;

    for(int i=0; i < v-1; i++){
        for(int j=0; j < E->n ; j++){
            if(dist[E->edges[j].u] + E->edges[j].w  < dist[E->edges[j].v])
                dist[E->edges[j].v]=dist[E->edges[j].u] + E->edges[j].w;
        }
    }
    for(int j=0; j < E->n ; j++){
        if(dist[E->edges[j].u] + E->edges[j].w  < dist[E->edges[j].v])
            return 1;
    }
    return 0;
}
int main(){
    edgeList E;
    int v, e;
    scanf("%d %d", &v, &e);
    for(int i=0 ; i< e  ; i++){
        scanf("%d", &E.edges[i].u);
        scanf("%d", &E.edges[i].v);
        scanf("%d", &E.edges[i].w);
    }
    E.n = e;

    int res = bellmanFord(&E,v ) ;
    if(res)
        printf("1\n");
    else
        printf("-1\n");
    return 0;
}

