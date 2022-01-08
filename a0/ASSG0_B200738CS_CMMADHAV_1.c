#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static int STACK_SIZE;
struct stack{
    int m_top;
    int* m_arr;
};
typedef struct stack stack;
void debug(stack* S){
    for(int i=0; i<= S->m_top; i++){
        printf("%c ",S->m_arr[i]);
    }
    printf("\n");
}
int stack_empty(stack* S){
    if( S->m_top== -1 ){
        return -1;
    }
    return 1;
}
int stack_full(stack* S){
    if( S->m_top == STACK_SIZE- 1){
        return -1;
    }
    return 1;
}
void stack_push(stack* S , const char k){
    if(stack_full(S) != -1){
        (S->m_top)++;
        if(S->m_top == 0){
            S->m_arr = (int*)malloc(sizeof(int));
        }else{
            int* new_arr = (int*)realloc(S->m_arr,(S->m_top + 1)*sizeof(int));
            S->m_arr = new_arr;
        }
        S->m_arr[S->m_top] = k;
        //debug(S);
    }
    else{
        int new_size =2*(S->m_top + 1);
        int* new_arr = (int*)realloc(S->m_arr, new_size*sizeof(int));
        S->m_arr = new_arr;
        (S->m_top)++;
        S->m_arr[S->m_top] = k;
        STACK_SIZE*=2;
        printf("1\n");
    }
}
void stack_pop(stack* S){
    if(stack_empty(S) != -1){
        int pop = S->m_arr[S->m_top];
        (S->m_top)--;
        if(S->m_top == -1){
            printf("%d\n",pop);
            free(S->m_arr);
            S->m_arr= NULL;
            return;
        }else{
            int* new_arr = (int*)malloc((S->m_top + 1)*sizeof(int));
            memcpy(new_arr, S->m_arr,(S->m_top+1)*sizeof(int));
            free(S->m_arr);
            S->m_arr = new_arr;
        }
        printf("%d\n",pop);
    }
    else{
        printf("-1\n");
    }
}
void stack_peek(stack* S){
    if(stack_empty(S) != -1){
        printf("%d\n", S->m_arr[S->m_top]);
    }
    else{
        printf("-1\n");
    }
}
int main(){
    scanf("%d",&STACK_SIZE);
    stack S ={-1,NULL};
    char ch;
    while(EOF!=(ch = fgetc(stdin))){
        if(ch == 'i'){
            int k;
            scanf(" %d",&k);
            stack_push(&S,k);
        //debug(&S);
        }
        if(ch == 'd'){
            stack_pop(&S);
        //debug(&S);
        }
        if(ch == 'p'){
            stack_peek(&S);
        }
        if(ch == 't'){
            break;
        }
    }
    if(S.m_arr != NULL){
        free(S.m_arr);
    }
    return 0;
}