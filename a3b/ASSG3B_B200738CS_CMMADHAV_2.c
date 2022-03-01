#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b)                   \
    (                               \
        {                           \
            __typeof__(a) _a = (a); \
            __typeof__(b) _b = (b); \
            _a > _b ? _a : _b;      \
        }                           \
    )
enum{
    black,
    red
};
struct Node
{
    int data;
    int color; // black = 0; red = 1     
    struct Node *p;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;
Node** treeroot;
int visited[1000000];
void swap(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void leftRotate( Node* x)
{
    Node* y = x->right;
    
    x->right = y->left;
    if (x->right != NULL)
        x->right->p = x;
    y->p = x->p;
    if (x->p == NULL)
        *treeroot = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}
void rightRotate( Node* x)
{
    Node* y = x->left;
    if(y == NULL)
        return;
    
    x->left = y->right;
    if(x->left != NULL){
        x->left->p = x; 
    }
    y->p = x->p; 
    if(x->p == NULL)
        *treeroot = y; 
    else if(x == x->p->left) 
        x->p->left =y; 
    else
        x->p->right = y; 
    y->right = x;
    x->p = y; 
}
Node *createNode(const int x)
{
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->p = NULL;
    n->left = NULL;
    n->right = NULL;
    n->color = 0;
}
Node *searchBST(Node *n, const int x)
{
    if (n == NULL)
    {
        return NULL;
    }
    if (n->data == x)
    {
        return n;
    }
    else if (n->data > x)
    {
        return searchBST(n->left, x);
    }
    else if (n->data < x)
    {
        return searchBST(n->right, x);
    }
}
void balanceInsertionRB(Node *tree, const int key)
{
    Node *k = searchBST(tree,key);

    while(  k != tree && k->color != black && k->p->color == red){
        Node* pParent = k->p;
        Node* pGrandParent = pParent->p;
        Node* pUncle;
        if (pParent == pGrandParent->left){
            pUncle = pGrandParent->right;

            if(pUncle != NULL && pUncle->color == red){
                //uncle red and parent black
                pUncle->color = black;
                pParent->color = black;
                pGrandParent->color = red;
                k=pGrandParent;
            }
            else{
                if(k == pParent->right){
                    leftRotate( pParent);
                    k = pParent;
                    pParent = k->p;
                }
                rightRotate( pGrandParent);
                swap(&(pGrandParent->color), &(pParent->color));
                k = pParent;
            }
        }
        else{
            pUncle = pGrandParent->left;
                
            if(pUncle != NULL && pUncle->color == red){
                //uncle red and parent
                pUncle->color = black;
                pParent->color = black;
                pGrandParent->color = red;
                k=pGrandParent;
            }
            else{
                if(k == pParent->left) {
                    rightRotate(pParent);
                    k = pParent;
                    pParent = k->p;
                }
                leftRotate( pGrandParent);
                swap(&(pParent->color), &(pGrandParent->color));
                k = pParent;
            }
        }
    }
    (*treeroot)->color =black;
}
Node *InsertRBTree(Node *n, const int k)
{
    if ((n) == NULL)
    {
        n = createNode(k);
        n->color = 1;
        return n;
    }
    if ((n)->data > k)
    {
        Node *x = InsertRBTree(n->left, k);
          x->p = n;
        (n)->left = x;
    }
    else if ((n)->data < k)
    {
        Node *x = InsertRBTree(n->right, k);
         x->p = n;
        (n)->right = x;
    }

    return n;
}
void printTree(Node *root)
{
    if (root == NULL)
    {
        printf("( ) ");
        return;
    }
    printf("( %d %c ", root->data , root->color == black ? 'B' : 'R');
    printTree(root->left);
    printTree(root->right);
    printf(") ");
}
void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void purgeTree(Node *root)
{
    if (root != NULL)
    {
        purgeTree(root->left);
        purgeTree(root->right);
        free(root);
    }
}
int isBeautiful(Node* tree, int dist , int x){
    visited[tree->data] = 1;

    if(tree == NULL)
        return 1;

    if(dist == x)
        if(tree->color == black)
            return 1;
        else
            return 0;

    int p=0,l=0,r=0;
    if(tree->p != NULL && !visited[tree->p->data])
        p = isBeautiful(tree->p, dist+1, x);

    if(tree->left != NULL && !visited[tree->left->data])
        l = isBeautiful(tree->left, dist+1, x);

    if(tree->right != NULL && !visited[tree->right->data])
        r = isBeautiful(tree->right, dist+1, x);

    if(p || l || r){
        return 1; 
    }
    else
        return 0;

}
void traverseRBTree(Node* tree,const int x,int* count){
    if(tree != NULL){
        int res = isBeautiful(tree,0,x);
        (*count)+=res;
        memset(visited,0,1000000*sizeof(int));
        traverseRBTree(tree->left, x, count);
        traverseRBTree(tree->right, x, count);
    }
}
int main()
{
    Node *tree = NULL;
    memset(visited, 0, sizeof(int)*10000);
    treeroot = &tree;
    int x,n;
    int count=0;
    scanf("%d %d", &x, &n);
    for(int i=0; i < n; i++){
        int key;
        scanf("%d", &key);
        tree = InsertRBTree(tree , key);
        balanceInsertionRB(tree, key);
    }
    traverseRBTree(tree, x, &count);
    printf("%d\n", count);
    purgeTree(tree);
    return 0;
}