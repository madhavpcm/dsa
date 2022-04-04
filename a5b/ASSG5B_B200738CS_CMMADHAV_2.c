#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 10001
#define EMAX 500501
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
int ds_makeset( int* rank, int* parent, const int x){
    if(parent[x] != -1){
        return -1;
    }
    parent[x] = x;
    rank[x] = 0;
    return x;
}
int minKruskal(int graph[][1001], int V){
    int res= 0;
    int parent[10002] = {-1};//both ranked union and path compression
    memset(parent, -1, 10002* sizeof(int));/// only memset like this for 0 and -1

    int rank[10002] = {-1};
    memset(rank, -1, 10002* sizeof(int));

    edgeList e;
    e.n = 0;
    for(int i=0; i < V ; i++){
        for(int ii =0; ii < V ; ii++){
            if(graph[i][ii] != INF){
                e.edges[e.n].u = i;
                e.edges[e.n].v = ii;
                e.edges[e.n].w = graph[i][ii];
                (e.n)++;

                ds_makeset(rank,parent, i);
                ds_makeset(rank,parent, ii);
            }
        }
    }
    qsort(&(e.edges), e.n, sizeof(edge), cmp);
    for(int i=0; i < e.n; i++){
        int x = ds_find(parent, e.edges[i].u);
        int y = ds_find(parent, e.edges[i].v);
        //printf("Edge[%d] : (%d, %d) weight : %d\n", i, e.edges[i].u, e.edges[i].v, e.edges[i].w);
        if( x != y){
            res+=e.edges[i].w;
            ds_union(rank, parent, e.edges[i].u,e.edges[i].v);
        }
    }
    return res;
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

int minPrims(int graph[][1001], int n){
    int res =0 ; 
    int *mst = calloc(n,sizeof(int));
    mst[0] = 1;
    
    int e = 0;
    while(e < n - 1){
        int mn = INF;
        int u = -1;int  v = -1;
        for(int i=0 ; i < n; i++){// O(n*n) = O (|v|*|v|)
            for(int ii=0; ii< n; ii++){
                //printf("(%d %d : %d)", i, ii, graph[i][ii]);
                if(graph[i][ii] < mn){
                    if(i != ii && mst[i] != mst[ii]){
                        mn = graph[i][ii];
                        u = i;
                        v = ii;
                    }
                }
            }
        }
        if(u != -1 && v != -1){
            e++;
            res += mn;
            mst[u] = 1;
            mst[v] = 1;
        }
    }
    free(mst);
    return res;
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
int main(){
    int graph[1001][1001];
    int edges[1001];
    char buffer[4500]={0};

    for(int i=0; i < 1001; i++){
        for(int j=0; j < 1001; j++){
            graph[i][j] = INF;
        }
    }
    memset(edges, 0, 1000*sizeof(int));
    memset(buffer, 0, 4500);
    int n;
    int edge_count=0;
    char ch;
    scanf("%c", &ch);
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
            if(graph[index][ii] != INF){
                scanf("%d", &graph[index][ii]);
            }
        }
    }
    if(ch == 'a'){
        printf("%d\n", minKruskal(graph, n));
    }
    else{
        printf("%d\n", minPrims(graph, n));

    }
    return 0;
}

