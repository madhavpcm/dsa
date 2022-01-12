#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* p;
};
typedef struct Node Node;
struct BTree{
    Node* head;
};
typedef struct BTree BTree;

struct qNode{
    Node* data;
    struct qNode* next;
};
typedef struct qNode qNode;
struct Queue{
    qNode* tail;
    qNode* head;
};
typedef struct Queue Queue;

Queue* create_node(Node* k){
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
void enqueue(Queue** q, Node* x){
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
Node* dequeue(Queue** q){
    if(!queue_empty(*q)){
        qNode* d = (*q)->head ;
        (*q)->head = (*q)->head->next;
        Node* res = d->data;
        d->next = NULL;
        free(d);
        if((*q)->head == NULL){
            (*q)->tail = NULL;
            free((*q));
            (*q) = NULL;
        }
        return res;
    }
    else{
        //printf("-1\n");
        return NULL;
    }
}
void queue_purge(Queue** q){
    while(!queue_empty(*q)){
        ddequeue(q) ;
    }
}

void Print(Node* root){
    if(root == NULL){
        printf("( ) ");
        return;
    }
    printf("( %d ",root->key);
    Print(root->left);
    Print(root->right);
    printf(") ");
}
Node* createNode(const int x){
    Node* new_node = malloc(sizeof(Node));
    new_node->key = x;
    new_node->left = new_node->right = new_node->p = NULL;
    return new_node;
}
void Insert(BTree* root, const int x){
    if(root->head== NULL){
        root->head = createNode(x) ;
        return;
    }
    Node* ng = createNode(x);
    Queue* q;
    enqueue(&q,root->head);
    while(!queue_empty(q)){
        Node* n = dequeue(&q);
        if(n->left !=NULL){
            enqueue(&q,n->left);
        }
        else {
            n->left= ng;
            ng->p = n->left;
            queue_purge(&q);
            return;
        }
        if (n->right != NULL){
            enqueue(&q,n->right);
        }
        else {
            n->right = ng; 
            ng->p = n->right;
            queue_purge(&q);
            return;
        }
    }

}
void purgeTree(Node* root){
    if(root == NULL){
        return;
    }
    purgeTree(root->left);
    purgeTree(root->right);
    free(root);
}
int main(){
    BTree* tree = malloc(sizeof(struct BTree));
    tree->head = NULL;

    char ch;
    while(EOF!=(ch = fgetc(stdin))){
        if(ch == 'i'){
            int x;
            scanf("%d", &x);
            Insert(tree,x);
        }
        if(ch == 'p'){
            Print(tree->head);
            printf("\n");
        }
        if(ch == 'e'){
            break;
        }
    }
    purgeTree(tree->head);
    free(tree);
    return 0;
}
//( 4 ( 3 ( 5 ( ) ( ) ) ( 6 ( ) ( ) ) ) ( 9 ( 1 ( ) ( ) ) ( 8 ( ) ( ) ) ) )