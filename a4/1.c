#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

#define degree(x) (x->degree)
struct Node{
    int data;
    int degree;
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
};
typedef struct Node Node;
struct Heap{
    Node* head;
};
typedef struct Heap Heap;
struct qNode{
    Node* data;
    struct qNode* next;
};
typedef struct qNode qNode;
qNode*createQNode(Node** data){
    qNode* p = malloc(sizeof(qNode));
    p->data = *data;
    p->next = NULL;
    return p;
}
void enQ(qNode** q, Node** data){
    if( *q == NULL){
        *q = createQNode(data);
        return;
    }
    qNode* front =  createQNode(data);
    front->next = *q;
    *q = front;
}
Node* deQ(qNode** q){
    if(*q == NULL)
        return NULL;
    qNode* curr=*q;qNode* prev = NULL; 
    while(curr->next!= NULL) {
        prev = curr;
        curr = curr->next;
    }
    Node* ret = curr->data;
    free(curr);
    if(prev != NULL)
        prev->next = NULL;
    else
        *q = NULL;
    return ret;
}
void swap(int* a, int *b){
    int c=*b;
    *b = *a;
    *a = c;
}
Node* createNode(const int k){
    Node* new = malloc(sizeof(Node)) ;
    new->child = NULL;
    new->sibling = NULL;
    new->data =k;
    new->degree = 0;
    new->parent = NULL;
    return new;
}
Heap* makeHeap(){
    Heap* heap = malloc(sizeof(Heap));
    heap->head = NULL;
    return heap;
}
Heap* binomialHeapMerge(Heap* h1, Heap* h2){
    if(h1->head == NULL){
        free(h1);
        return h2;
    }
    if(h2->head == NULL){
        free(h2);
        return h1;
        
    }

    Node* n1 = h1->head;
    Node* n2 = h2->head;
    Node* front;
    Node* back; 
    Heap* h = makeHeap();
    if(n1->degree <= n2->degree ){
        front = h1->head; 
        n1 = n1->sibling;
    }
    else{
        front = h2->head;
        n2 = n2->sibling;
    }
    back = front;
    while(n1 != NULL && n2 != NULL){
        if(n1->degree <= n2->degree){
            back->sibling = n1;
            n1 = n1->sibling;
        }
        else{
            back->sibling = n2;
            n2 = n2->sibling;
        }
        back = back->sibling;
    }
    if(n1)
        back->sibling = n1;
    else
        back->sibling = n2;
    h->head = front; 
    free(h1);
    free(h2);
    return h;
}
void binomialLink(Node* y, Node* z){
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    (z->degree)++;
}
Node* binomialHeapFindNode(Node* l, const int key){
    if(l == NULL)
        return NULL;
    if(l->data == key)
        return l;
    Node* res = binomialHeapFindNode(l->child, key);
    if(res == NULL)
        return binomialHeapFindNode(l->sibling, key);
    return res;
}
Node* binomialHeapMinimum(Heap* h){
    Node* y = NULL;
    Node* x = h->head;
    int mn = INT_MAX;
    while(x != NULL){
        if(x->data < mn){
            mn = x->data;
            y =x;
        }
        x = x->sibling;
    }
    return y;
}
Heap* binomialHeapUnion(Heap* h1, Heap* h2){
    Heap* h = binomialHeapMerge(h1, h2);
    if(h->head == NULL)
        return h;
    Node* prevx = NULL;
    Node* x = h->head;
    Node* nextx = x->sibling;
    
    while(nextx != NULL){
        if(x->degree != nextx->degree || nextx->sibling != NULL && nextx->sibling->degree == x->degree){
            prevx = x;//case 1 & 2
            x = nextx;//case 1 & 2
        }
        else {
            if(x->data <= nextx->data){
                x->sibling = nextx->sibling;// case 3
                binomialLink(nextx, x);//case 3
            }
            else{
                if (prevx == NULL)
                    h->head = nextx;
                else
                    prevx->sibling = nextx;
                binomialLink(x,nextx);//case 4
                x = nextx;//case 4
            }
        }
        nextx = x->sibling;
    }
    return h;
}
Node* reverseList(Node* n){
    Node* newhead = NULL;
    while(n != NULL){
        Node* nnext = n->sibling;
        n->sibling = newhead;
        n->parent = NULL;//remove parent
        newhead = n;
        n = nnext;
    }
    return newhead;
}
Heap* heapRemoveRoot(Heap* h,Node* curr,Node* prevcurr){
    if(h->head == curr)
        h->head = curr->sibling;
    else
        prevcurr->sibling = curr->sibling;
    
    Heap* newheap = makeHeap();
    Heap* old = h;
    newheap->head = reverseList(curr->child);
    free(curr);
    return newheap;
}
Heap* binomialHeapExtractMin(Heap* h, int flag){
    if(h == NULL || h->head == NULL)
        return NULL;
    Node* n = h->head;  
    Node* prev = n;
    Node* curr = n;
    Node* prevcurr = NULL;
    int mn = INT_MAX;
    while(n != NULL){
        if(n->data < mn){
            prevcurr = prev;
            curr = n;
            mn = n->data;
        }
        prev = n;
        n = n->sibling;
    }
    prevcurr->sibling = curr->sibling;
    Heap* h_;
    Heap* old =h;
    h_ = heapRemoveRoot(h,curr,prevcurr);
    h = binomialHeapUnion(h, h_);
    if(mn != INT_MIN && flag){
        printf("%d\n", mn);
    }
    return h;
}

Heap* binomialHeapDecrKey(Heap* h, int x, const int k){
    Node* f = binomialHeapFindNode(h->head,x);
    if( f== NULL){
        printf("-1\n");
        return h;
    }
    if(f->data >= k){
        f->data -= k;
        printf("%d\n",f->data );
    }
    else{
        printf("-1\n");
    }
    Node* fp = f->parent;
    while(fp != NULL && fp->data > f->data){
        swap(&fp->data, &f->data);
        f=fp;
        fp = f->parent;
    }
    return h;

}
Heap* binomialHeapDelete(Heap* h, const int k){
    Node* t = h->head;
    Node* f = binomialHeapFindNode(h->head, k);
    if(f == NULL){
        printf("-1\n");
        return h;
    }
    printf("%d\n", k);
    f->data = INT_MIN;
    Node* fp = f->parent; 
    while(fp != NULL && fp->data > f->data){
        swap(&fp->data, &f->data);
        f = fp;
        fp = fp->parent;
    }
    h = binomialHeapExtractMin(h, 1);
    return h;
}
Heap* binomialHeapInsert(Heap* h, const int k){
    Node* new = createNode(k);
    Heap* h_ = malloc(sizeof(Heap));
    h_->head = new;
    h = binomialHeapUnion(h, h_);
    return h;
}
void printLevel(Node* root, qNode** queue){
    while(root != NULL){
        printf("%d ", root->data);
        if(root->child != NULL)
            enQ(queue,&root->child);
        root = root->sibling;
    }

    Node* ret = deQ(queue);
    while(ret !=NULL){
        printLevel(ret, queue);
        ret = deQ(queue);
    }
}
void binomialHeapPurge(Heap* h){
    while(h->head != NULL){
        h = binomialHeapExtractMin(h, 0);
    }
    free(h);
}
int main(){
    char ch;
    Heap* heap = makeHeap();
    qNode* queue = NULL;
    while(EOF != (ch = fgetc(stdin))){
        if(ch == 'i'){
            int x;
            scanf("%d", &x);
            heap = binomialHeapInsert(heap, x);
            x = 2;
        }
        if(ch == 'd'){
            int x;
            scanf("%d", &x);
            heap = binomialHeapDelete(heap, x);
        }
        if(ch == 'p'){
            printLevel(heap->head, &queue) ;
            printf("\n");
        }
        if(ch == 'm'){
            Node* f = binomialHeapMinimum(heap) ;
            if(f != NULL)
                printf("%d\n", f->data);

        }
        if(ch == 'x'){
            heap = binomialHeapExtractMin(heap, 1);
        }
        if(ch == 'r'){
            int y,z; 
            scanf("%d %d", &y, &z);
            heap = binomialHeapDecrKey(heap, y, z);
        }
        if(ch == 'e'){
            break;
        }
    }
    binomialHeapPurge(heap);
    return 0;
}