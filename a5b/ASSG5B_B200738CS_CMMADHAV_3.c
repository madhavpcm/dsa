#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#define INF 10001
#define inf 10000000 
struct edge {
    int u;
    int v;
    int w;
};
typedef struct edge edge;
struct edgeList {
    edge edges[10000];
    int n;
};
typedef struct edgeList edgeList;

int ds_find(int* parent , const int x ){
    if(parent[x] != x){
        parent[x] = ds_find(parent, parent[x] );
    }
    return parent[x];
}
void ds_union(int* rank, int* parent, const int x, const int y ){
    int x_,y_;
    x_ = ds_find(parent, x ) ;
    y_ = ds_find(parent, y ) ;
    if( x_ == y_ && x_ != -1 ){
        return;
    }
    if(rank[x_] > rank[y_] ){
        parent[y_] = x_;
    }
    else if( rank[x_] == rank[y_]){
        parent[y_] = x_;
        rank[x_]++;
    }
    else{
        parent[x_] = y_;
    }

}
int cmp(const void* a, const void *b){
    edge* x = (edge* )a;
    edge* y = (edge* )b;
    return (x->w) - (y->w);
}
int count(int n)
{
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}
int isValidVertex(int graph[][1001], int n, int v){
    for(int i=0; i< n; i++  )
        if(graph[v][i] != INF)
            return 1;
    return 0;
}
void dijkstra(int graph[][1001] ,int n, int src, int dest){
    int dist[1001] = {0};
    int prev[1001] = {-1};
    int u[1001] = {0};
    int cost[1001][1001];
    int visited[1001] = {0};

    for(int i=0; i< n; i++){
        dist[i] = inf;
    }
    for(int i=0; i < n; i++ ){
        for(int j=0; j< n; j++){
            if(graph[i][j] == -1)
                cost[i][j] =  inf;
            else
                cost[i][j] = graph[i][j];
        }
    }


    dist[src] = 0;

    for(int i=0; i< n; i++){
        dist[i] = cost[src][i];
        prev[i] = src;
        visited[i] = 0;
    }
    dist[src] = 0;
    visited[src] = 1;
    int e = 1;
    int next;
    while(e < n - 1){
        int mn = inf;
        for(int i=0; i < n ; i++){
            if(dist[i] < mn && !visited[i]){
                mn = dist[i];
                next =i;
            }
        }
        visited[next] = 1;
        for(int i=0; i < n ; i++){
            if(!visited[i]){
                if(mn + cost[next][i] < dist[i]){
                    dist[i] = mn + cost[next][i];
                    prev[i] = next;
                }
            }
        }
        e++;
    }


    if(dest == -1){
        for(int i=0; i < n ; i++){
            if(i!=src)
            {
                if(dist[i] >= inf){
                    printf("INF ");
                }
                else{
                    printf("%d ", dist[i]);
                }
            }
            else{
                printf("%d ", 0);
            }
        }
    }
    else{
        if(dist[dest] >= inf){
            printf("UNREACHABLE\n");
        }
        else{
            printf("%d\n", dist[dest]);
        }
    }
}
void print_matrix(int graph[][1001], int n){
    printf("DEBUG:\n");
    for(int i=0; i < n ;i++){
        for(int j=0; j< n ; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}
int main(){
    int graph[1001][1001];
    int edges[1001];
    char buffer[4500]={0};

    for(int i=0; i < 1001; i++){
        for(int j=0; j < 1001; j++){
            graph[i][j] = -1;
        }
    }
    memset(edges, 0, 1000*sizeof(int));
    memset(buffer, 0, 4500);
    int n;
    int edge_count=0;
    char ch;
    scanf("%d",&n);

    for(int i=0; i < n ; i++){
        int index=0;
        char dummy;

        scanf("%d%c",&index, &dummy);
        if(dummy== '\n'){
            memset(buffer, 0, 4500);
            continue;
        }

        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        int bufferi=0; 
        int d;
        int j=0;
        do{
            if(sscanf(buffer+bufferi,"%d",&d )){
                graph[index][d]=1;
                bufferi+= count(d);
                bufferi+=1;
                j++;
            }
            else
                bufferi++;
        } while ( bufferi < strlen(buffer));

        edge_count +=j;
        edges[i] = j;
        memset(buffer, 0, 4500);
    }
    for(int i=0; i < n ; i++){
        int index;
        char dummy;
        int x;
        scanf("%d",&index );
        for(int ii =0; ii < n; ii++){
            if(graph[index][ii] != -1){
                scanf("%d", &graph[index][ii]);
            }
        }
    }
    scanf("%c", ch);
    while(fgets(buffer,sizeof(buffer), stdin) != NULL){
        if(!strcmp(buffer, "stop")){
            break;
        }
        char choice[5];
        sscanf(buffer,"%s",choice);
        int i = strlen(choice)+1;
        if(!strcmp(choice, "apsp")){
            int src;
            sscanf(buffer+i,"%d",&src);
            dijkstra(graph,n,src,-1);
            printf("\n");
        }
        else if ( !strcmp(choice, "sssp")){
            int src, dest;
            sscanf(buffer+i,"%d %d", &src, &dest);
            dijkstra(graph,n,src,dest);
        }
        else if ( !strcmp(choice, "stop")){
            break;
        }
        memset(buffer, 0, 4500);
    }
    return 0;
}

