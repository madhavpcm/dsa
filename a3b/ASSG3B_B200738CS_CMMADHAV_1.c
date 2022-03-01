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
Node *minBST(Node *n)
{
    if (n == NULL)
    {
        return NULL;
    }
    Node *curr = n;
    while (curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}
Node *maxBST(Node *n)
{
    if (n == NULL)
    {
        return NULL;
    }
    Node *curr = n;
    while (curr->right != NULL)
    {
        curr = curr->right;
    }
    return curr;
}
Node *treeSuccessorHelper(Node *y, Node *x, Node *c)
{
    if (y == x)
        return c;
    if (x->data < y->data)
        return treeSuccessorHelper(y->left, x, y);
    else
        return treeSuccessorHelper(y->right, x, c);
}
Node *treeSuccessor(Node **n, const int k)
{
    Node *x = searchBST(*n, k);
    if (x == NULL)
        return NULL;

    if (x->right != NULL)
        return minBST(x->right);
    else
        return treeSuccessorHelper(*n, x, NULL);
}
Node *treePredecessorHelper(Node *y, Node *x, Node *c)
{
    if (y == x)
        return c;
    if (x->data < y->data)
        return treePredecessorHelper(y->left, x, c);
    else
        return treePredecessorHelper(y->right, x, y);
}
Node *treePredecessor(Node **n, const int k)
{
    Node *x = searchBST(*n, k);
    if (x == NULL)
        return NULL;

    if (x->left != NULL)
        return maxBST(x->left);
    else
        return treePredecessorHelper(*n, x, NULL);
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
int main()
{
    Node *tree = NULL;
    treeroot = &tree;
    char inp[1000];
    while (fgets(inp,1000,stdin) != NULL)
    {
        if (inp[0] == 't')
        {
            break;
        }
        else{
            int x;
            sscanf(inp,"%d",&x);
            tree = InsertRBTree(tree, x);
            balanceInsertionRB(tree, x);
            printTree(tree);
            printf("\n");
        }
    }
    purgeTree(tree);
    return 0;
}