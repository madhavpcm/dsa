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

struct qNode{
    int data;
    struct qNode* next;
};
typedef struct qNode qNode;
struct Queue{
    qNode* tail;
    qNode* head;
};
typedef struct Queue Queue;

Queue* create_node(const int k){
    qNode* s =malloc(sizeof(qNode));
    s->data = k;
    s->next = NULL;

    Queue* q = malloc(sizeof(Queue));
    q->head = s;
    q->tail = s;

    return q;
}
int queue_empty(Queue* q){
    if(q == NULL){
        return 1;
    }
    return 0;
}
void enqueue(Queue** q, const int x){
    if(queue_empty(*q)){
        *q = create_node(x);
        return;
    }
    qNode* n = malloc(sizeof(qNode));
    n->data = x;
    n->next = NULL;

    (*q)->tail->next = n;
    (*q)->tail = (*q)->tail->next;
}
void ddequeue(Queue** q){
    if(!queue_empty(*q)){
        qNode* d = (*q)->head ;
        (*q)->head = (*q)->head->next;
        //   printf("%d\n", d->data);
        d->next = NULL;
        free(d);
        if((*q)->head == NULL){
            (*q)->tail = NULL;
            free((*q));
            (*q) = NULL;
        }
    }
    else{
        //  printf("-1\n");
    }
}
int dequeue(Queue** q){
    if(!queue_empty(*q)){
        qNode* d = (*q)->head ;
        (*q)->head = (*q)->head->next;
        int ret =  d->data;
        d->next = NULL;
        free(d);
        if((*q)->head == NULL){
            (*q)->tail = NULL;
            free((*q));
            (*q) = NULL;
        }
        return ret;
    }
    else{
        return -1;
    }

}
void queue_purge(Queue** q){
    while(!queue_empty(*q)){
        ddequeue(q) ;
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
void print_matrix(int graph[][1001], int n){
    printf("DEBUG:\n");
    for(int i=0; i < n ;i++){
        for(int j=0; j< n ; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}
void bfs(graph [][1001], int N,int src){

    int visited[1001] = {0};
    int dist[1001] = {0};
    int prev[1001] = {0};
    Queue* q=NULL;
    enqueue(&q,src );
    visited[src]= 1;
    while(q->m_head != NULL && q->m_tail !=NULL){
        int n = dequeue(&q);
        printf("%d ", n);
        for(int ii=0; ii< N ; ii++){
            if(graph[n][ii] != -1){
                if(!visited[ii]){
                    visited[ii] = 1;
                    enqueue(&q, graph[n][ii]);
                    dist[ii] = dist[n] + 1;
                    prev[ii] = n;
                }
            }
        }

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
void dfs(graph[][1001], int n, int src){
    int visited[1001] = {0};
    Stack* s;
    push(&s, src);
    visited[src] = 1;
    while(!stack_empty()){
        int x = pop(&s);
        if(!visited[x]){
            printf("%d ", x);
            visited[x] = 1;
        }
        for(int i=0; i< n; i++){
            if(!visited[i]){
                push(&s, i);
            }
        }
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

