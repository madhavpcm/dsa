#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;
Node *createNode(const int x)
{
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->left = NULL;
    n->right = NULL;
}
Node *InsertBST(Node **n, const int k)
{
    if ((*n) == NULL)
    {
        *n = createNode(k);
        return *n;
    }
    if ((*n)->data > k)
    {
        Node *x = InsertBST(&((*n)->left), k);
        (*n)->left = x;
        //  x->p = *n;
    }
    else if ((*n)->data < k)
    {
        Node *x = InsertBST(&((*n)->right), k);
        (*n)->right = x;
        // x->p = *n;
    }
    return *n;
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
int getHeight(Node*root){
    if(root == NULL){
        return 0;
    }
    return 1+max(getHeight(root->left),getHeight( root->right));
}
int isAVL(Node* root){
    if (root == NULL)
        return 1;
    
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    if(isAVL(root->left) && isAVL(root->right) && abs(lh - rh) <=1 )
        return 1;
    else
        return 0;
}
void printTree(Node *root)
{
    if (root == NULL)
    {
        printf("( ) ");
        return;
    }
    printf("( %d ", root->data);
    printTree(root->left);
    printTree(root->right);
    printf(") ");
}
void inorder(Node* root){
    if(root != NULL){
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void purgeTree(Node* root){
    if(root!=NULL){
        purgeTree(root->left);
        purgeTree(root->right);
        free(root);
    }
}
int checkLevel(Node* root, int height, int color){
    if(root == NULL)
        return 1;
    if(height == 1){
        if(color == black && root.color)
    }
}
void levelOrderTraversal(Node* root){

}
int main()
{
    Node* tree = NULL;
    char ch;
    while(EOF != (ch = fgetc(stdin))){
        if(ch == 'i'){
            int x;
            scanf("%d", &x);
            tree = InsertBST(&tree, x);
        }
        if(ch == 'c'){
            printf("%d\n", isAVL(tree));
        }
        if(ch == 't'){
            break;
        }
    }

    purgeTree(tree);
    return 0;
}