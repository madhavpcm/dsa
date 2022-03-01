#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b)                   \
    (                               \
        {                           \
            __typeof__(a) _a = (a); \
            __typeof__(b) _b = (b); \
            _a > _b ? _a : _b;      \
        })
struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;
int balanceFactor(Node *n)
{
    int l = 0, r = 0;
    if (n->left == NULL)
        l = 0;
    else
        l = n->left->height;

    if (n->right == NULL)
        r = 0;
    else
        r = n->right->height;

    return l - r;
}
int getBalance(Node *n)
{
    return balanceFactor(n);
}
void leftRotate(Node **n, const int key)
{
    Node *x = *n;
    if (x == NULL)
    {
        return; // error
    }
    Node *y = x->right;
    if (y != NULL)
    {
        Node *beta = y->left;
        y->left = x;
        x->right = beta;
        int lh = (y->left == NULL) ? 0 : y->left->height;
        int rh = (y->right == NULL) ? 0 : y->right->height;
        y->height = 1 + max(lh, rh);
    }

    int lh = (x->left == NULL) ? 0 : x->left->height;
    int rh = (x->right == NULL) ? 0 : x->right->height;
    x->height = 1 + max(lh, rh);
    *n = y;
}
void rightRotate(Node **n, const int key)
{
    Node *x = *n;
    Node *y = x->left;
    if (y != NULL)
    {
        Node *beta = y->right;
        y->right = x;
        x->left = beta;
        int lh = (y->left == NULL) ? 0 : y->left->height;
        int rh = (y->right == NULL) ? 0 : y->right->height;
        y->height = 1 + max(lh, rh);
    }

    int lh = (x->left == NULL) ? 0 : x->left->height;
    int rh = (x->right == NULL) ? 0 : x->right->height;
    x->height = 1 + max(lh, rh);

    *n = y;
}
Node *createNode(const int x)
{
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
}
Node *balanceInsertionAVL(Node **n, const int k)
{
    Node *x = *n;
    int lh = (x->left == NULL) ? 0 : x->left->height;
    int rh = (x->right == NULL) ? 0 : x->right->height;
    //x->height = 1 + max(lh, rh);

    int b_factor = balanceFactor(*n);
    if (b_factor > 1)
    {
        if (k > (*n)->left->data)
        {
            leftRotate(&(*n)->left, k);
            rightRotate(n, k);
        }
        else if (k < (*n)->left->data)
        {
            rightRotate(n, k);
        }
    }
    else if (b_factor < -1)
    {
        if (k > (*n)->right->data)
        {
            leftRotate(n, k);
        }
        else if (k < (*n)->right->data)
        {
            rightRotate(&(*n)->right, k);
            leftRotate(n, k);
        }
    }
    x = *n;
    if (x != NULL)
    {
        lh = (x->left == NULL) ? 0 : x->left->height;
        rh = (x->right == NULL) ? 0 : x->right->height;
        x->height = 1 + max(lh, rh);
    }
    return *n;
}
Node *balanceDeletionAVL(Node **n, const int k)
{
    Node *root = *n;
    int b_factor = getBalance(root);
    if (b_factor > 1)
    {
        if (getBalance(root->left) >= 0)
        {
            rightRotate(n, k);
        }
        else
        {
            leftRotate(&((*n)->left), k);
            rightRotate(n, k);
        }
    }
    else if (b_factor < -1)
    {
        if (getBalance(root->right) <= 0)
        {
            leftRotate(n, k);
        }
        else
        {
            rightRotate(&((*n)->right), k);
            leftRotate(n, k);
        }
    }
    if (root != NULL)
    {
        int lh = (root->left == NULL) ? 0 : root->left->height;
        int rh = (root->right == NULL) ? 0 : root->right->height;
        root->height = 1 + max(lh, rh);
    }
    return *n;
}
Node *InsertAVL(Node **n, const int k)
{
    if ((*n) == NULL)
    {
        *n = createNode(k);
        return *n;
    }
    if ((*n)->data > k)
    {
        Node *x = InsertAVL(&((*n)->left), k);
        (*n)->left = x;
        //  x->p = *n;
    }
    else if ((*n)->data < k)
    {
        Node *x = InsertAVL(&((*n)->right), k);
        (*n)->right = x;
        // x->p = *n;
    }
    *n = balanceInsertionAVL(n, k);
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
void deleteNode(Node **n, const int k)
{
    Node *root = *n;
    if (root == NULL)
    {
        printf("FALSE\n");
        return;
    }

    if (k < root->data)
        deleteNode(&((*n)->left), k);

    else if (k > root->data)
        deleteNode(&((*n)->right), k);

    else
    {
        Node *temp = treePredecessor(n, k);
        if (temp == NULL)
        {
            printf("%d\n", root->data);
            free(root);
            *n = NULL;
            return;
        }
        root->data = temp->data;
        deleteNode(&((*n)->right), temp->data);
    }
    *n = balanceDeletionAVL(n, k);
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
    char ch;
    while (EOF != (ch = fgetc(stdin)))
    {
        if (ch == 'i')
        {
            int x;
            scanf("%d", &x);
            tree = InsertAVL(&tree, x);
        }
        if (ch == 'd')
        {
            int x;
            scanf("%d", &x);
            deleteNode(&tree, x);
        }
        if (ch == 's')
        {
            int x;
            scanf("%d", &x);
            Node *s = searchBST(tree, x);
            if (s == NULL)
                printf("FALSE\n");
            else
                printf("TRUE\n");
        }
        if (ch == 'b')
        {
            int x;
            scanf("%d", &x);
            Node *s = searchBST(tree, x);
            if (s == NULL)
                printf("FALSE\n");
            else
                printf("%d\n", getBalance(s));
        }
        if (ch == 'p')
        {
            printTree(tree);
            printf("\n");
        }
        if (ch == 'e')
        {

            break;
        }
    }
    purgeTree(tree);
    return 0;
}