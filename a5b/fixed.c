#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include<sys/param.h>
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
int getVertex(int* mst, int* prev){
    int mn=INF,mi=0;
    for(int v=0; v < 1001; v++){
        if(!mst[v] && prev[v] < mn ){
            mn = prev[v];
            mi = v;
        }
            
    }
    return mi;
}
int minKruskal(int graph[][1001], int V){
    int res= 0;
    int parent[10002] = {-1};//both ranked union and path compression
    memset(parent, -1, 10002* sizeof(int));/// only memset like this for 0 and -1

    int rank[10002] = {-1};
    memset(rank, -1, 10002* sizeof(int));
    edgeList e;
    e.n = 0;
    for(int i=0; i < 1001 ; i++){
        for(int ii =0; ii < 1001 ; ii++){
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

struct sNode{
    int data;
    struct sNode* next;
};
typedef struct sNode sNode;
struct Stack{
    sNode* top;
};
typedef struct Stack Stack;
Stack* create_node(const char k){
    sNode* s = malloc(sizeof(sNode));
    s->data = k;
    s->next = NULL;

    Stack* S = malloc(sizeof(Stack));
    S->top = s;
    return S;
}
int stack_empty(Stack*  s){

    if(s== NULL || s->top == NULL)
        return 1;
    return 0;
}
void push(Stack** s, char k){
    if(*s == NULL){
        *s = create_node(k);
        return;
    }
    sNode* n = malloc(sizeof(sNode));
    n->data = k;
    n->next = (*s)->top;
    (*s)->top = n;
}
int pop(Stack**s ){
    if(!stack_empty((*s))){
        sNode *d = ((*s)->top) ;
        int x = d->data;
        (*s)->top = (*s)->top->next;
        free(d);
        if((*s)->top == NULL){
            free((*s));
            (*s)= NULL;
        }
        return x;
    }
    else{
        return 0;
    }
}
void stack_purge(Stack** s){
    while(!stack_empty(*s)){
        pop(s);
    }
}
int minPrims(int graph[][1001], int n, int src, int dest){
    int res =0 ; 
    int *mst = calloc(1001,sizeof(int));
    int *prev = calloc(1001,sizeof(int));
    int *parent = calloc(1001,sizeof(int));
    for(int i=0; i< 1001; i++){
        prev[i] =INF;
    }
    prev[src] =0;
    parent[src]=-1;
    int e = 0;
    int lastu;
    int lastv=0;
    Stack* path=NULL;
    while(e < n - 1){
        int mn = INF;

        int u=getVertex(mst, prev);
        mst[u] = 1;
        int lastv=0;
        for(int v=0; v < 1001; v++){
            if(graph[u][v] && !mst[v]  ){
                if(graph[u][v] < prev[v]){
                    parent[v] =u;
                    prev[v] = graph[u][v];
                    lastu =u;
                    lastv= v;
                    push(&path,v);
                }
                else if(graph[u][v] == prev[v] ){
                    if(v + graph[u][v] < lastv + graph[u][lastv]){
                        parent[v] =u;
                        prev[v] = graph[u][v];
                        lastu =u;
                        lastv= v;
                        pop(&path);
                        push(&path,v);

                    }
                    
                }

            }
        }
        e++;
    }
    for(int i=src; i<= dest; i++){
        if( graph[i][parent[i]] != INF){
            res+=graph[i][parent[i]];
        }
    }
    while(!stack_empty(path)){
        int w=pop(&path) ;
        printf("%d ", w);
    }
    printf("%d ", src)
    printf("\n");
    
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

    int minValue=INT_MAX;
    int maxValue=-1;
    for(int i=0; i < n ; i++){
        int index=0;
        char dummy;
        
        scanf("%d%c",&index, &dummy);
        minValue = MIN(index, minValue);
        maxValue = MAX(index, maxValue);
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
        for(int ii =0; ii < 1001; ii++){
            if(graph[index][ii] != INF){
                scanf("%d", &graph[index][ii]);
            }
        }
    }
    if(ch == 'a'){
        printf("%d\n", minKruskal(graph, n));
    }
    else{
        printf("%d\n", minPrims(graph, n, minValue ,maxValue));

    }
    return 0;
}

