#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct queue{
    int m_head;
    int m_tail;
    int* m_queue;
};
typedef struct queue queue;

static int QUEUE_SIZE;
int queue_full(queue* Q){
    if(Q->m_tail - Q->m_head+ 1 == QUEUE_SIZE){
        return 1; 
    }
    return -1;
}
size_t queue_size(queue* Q){
    if(Q->m_head==-1 && Q->m_tail ==-1)
        return 0;
    return (Q->m_tail- Q->m_head+ 1);
}
void debugp(queue* Q){
    printf("[");
    for(int i=0; i < queue_size(Q); i++){
        printf("%p, ",Q->m_queue[i]);
    }
    printf("]\n");
}
void debug(queue* Q){
    FILE* err;
    err =fopen("err2.txt","a");
        fflush(err);
    if(!err)
        perror("asdf");
    for(int i=0; i < queue_size(Q); i++){
        fprintf(err,"%d ",Q->m_queue[i]);
    }
    fprintf(err,"\n");
    fclose(err);
}
int queue_empty(queue* Q){
    if(Q->m_tail == -1 && Q->m_head == -1){
        return 1;
    }
    return -1;
}
void enqueue(queue* Q, const int x){
    //empty q
    //printf("main: %p\n",Q);
    if(queue_full(Q) != 1){
        if(queue_empty(Q) == 1 ){
            (Q->m_head)++;
            (Q->m_tail)++;
            (Q->m_queue) = (int*)malloc(sizeof(int));
            Q->m_queue[0] = x;
        }else{
            (Q->m_tail)++;
            int* new_queue= (int*)realloc((Q)->m_queue,queue_size(Q)*sizeof(int));
            if( new_queue == NULL){
                printf("SIGABRT:***realloc failure***\n");
                exit(1);
            }
            Q->m_queue =new_queue;
            Q->m_queue[Q->m_tail] = x;
        }
    }
    else{
        printf("1\n");
    }
}
void dequeue(queue* Q){
    if(queue_empty(Q) != 1){
        //free memory before
        if(queue_size(Q) == 1){
            printf("%d\n",Q->m_queue[0]);

            free(Q->m_queue);

            Q->m_queue = NULL;
            Q->m_tail= -1;
            Q->m_head= -1; 
        }
        else{
            printf("%d\n",Q->m_queue[Q->m_head]);
            (Q->m_tail)--;
            int* new_queue = (int*)malloc(queue_size(Q)*sizeof(int));
            if( new_queue == NULL){
                printf("SIGABRT:***realloc failure***\n");
                exit(1);
            }
            memcpy(new_queue,Q->m_queue+1,queue_size(Q)*sizeof(int));
            free(Q->m_queue);
            Q->m_queue = new_queue;
        }

    }
    else{
        printf("1\n");
    }
}
void queue_purge(queue* Q){
    if(Q==NULL) return;
    if(Q->m_queue != NULL)
        free(Q->m_queue);
    Q->m_tail = -1;
    Q->m_head= -1;
    Q->m_queue= NULL;
}
int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&QUEUE_SIZE);
    queue *Q = (queue*)malloc(sizeof(queue));
    Q->m_head =-1;
    Q->m_tail =-1;
    char ch;
    //printf("main: %p\n",Q);
    while(EOF!= (ch = fgetc(stdin))){
        if(ch == 'i'){
            int x;
            scanf("%d", &x);
            enqueue(Q, x);
        debug(Q);
        }
        if(ch == 'd'){
            //debug(Q);
            dequeue(Q);
        debug(Q);
        }
        if(ch == 'f'){
            printf("%d\n", queue_full(Q));
        }
        if(ch == 'e'){
            printf("%d\n", queue_empty(Q));
        }
        if(ch == 't'){
            break;
        }
        
    }
    queue_purge(Q);
    free(Q);
    fclose(stderr);
    return 0;
}