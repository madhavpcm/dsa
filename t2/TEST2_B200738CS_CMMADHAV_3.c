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
enum
{
    black,
    red
};
struct Node
{
    int data;
    int color; // black = 0; red = 1
    char tid[101];
    struct Node *p;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;
Node **a1root;
Node **a2root;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void leftRotate(Node *x, int id)
{
    Node *y = x->right;

    x->right = y->left;
    if (x->right != NULL)
        x->right->p = x;
    y->p = x->p;
    if (x->p == NULL)
    {
        if (id == 1)
            (*a1root) = y;
        else
            (*a2root) = y;
    }
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}
void rightRotate(Node *x, int id)
{
    Node *y = x->left;
    if (y == NULL)
        return;

    x->left = y->right;
    if (x->left != NULL)
    {
        x->left->p = x;
    }
    y->p = x->p;
    if (x->p == NULL)
    {
        if (id == 1)
            (*a1root) = y;
        else
            (*a2root)= y;
    }
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->right = x;
    x->p = y;
}
Node *createNode(char *buff, const int x)
{
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->p = NULL;
    n->left = NULL;
    n->right = NULL;
    n->color = 0;
    strcpy(n->tid, buff);
    return n;
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
void balanceInsertionRB(Node *tree, const int key, int id)
{
    Node *k = searchBST(tree, key);

    while (k != tree && k->color != black && k->p->color == red)
    {
        Node *pParent = k->p;
        Node *pGrandParent = pParent->p;
        Node *pUncle;
        if (pParent == pGrandParent->left)
        {
            pUncle = pGrandParent->right;

            if (pUncle != NULL && pUncle->color == red)
            {
                // uncle red and parent black
                pUncle->color = black;
                pParent->color = black;
                pGrandParent->color = red;
                k = pGrandParent;
            }
            else
            {
                if (k == pParent->right)
                {
                    leftRotate(pParent, id);
                    k = pParent;
                    pParent = k->p;
                }
                rightRotate(pGrandParent, id);
                swap(&(pGrandParent->color), &(pParent->color));
                k = pParent;
            }
        }
        else
        {
            pUncle = pGrandParent->left;

            if (pUncle != NULL && pUncle->color == red)
            {
                // uncle red and parent
                pUncle->color = black;
                pParent->color = black;
                pGrandParent->color = red;
                k = pGrandParent;
            }
            else
            {
                if (k == pParent->left)
                {
                    rightRotate(pParent, id);
                    k = pParent;
                    pParent = k->p;
                }
                leftRotate(pGrandParent, id);
                swap(&(pParent->color), &(pGrandParent->color));
                k = pParent;
            }
        }
    }
    if (id == 1)
        (*a1root)->color = black;
    else

        (*a2root)->color = black;
}
Node *InsertRBTree(Node *n, char *buff, const int k, int id)
{
    if ((n) == NULL)
    {
        n = createNode(buff, k);
        n->color = 1;
        return n;
    }
    if ((n)->data > k)
    {
        Node *x = InsertRBTree(n->left, buff, k, id);
        x->p = n;
        (n)->left = x;
    }
    else if ((n)->data < k)
    {
        Node *x = InsertRBTree(n->right, buff, k, id);
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
        printf("( NIL B ) ");
        return;
    }
    printf("( %s %d %c ", root->tid, root->data, root->color == black ? 'B' : 'R');
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
int fairnessfactor(Node *tree, Node *root)
{
    if (root == tree)
    {
        if (root == NULL)
            return 0;
        int left = fairnessfactor(tree, root->left);
        int right = fairnessfactor(tree, root->right);
        return left > right ? left : right;
    }
    else
    {
        if (root == NULL)
            return 1;
        int left = fairnessfactor(tree, root->left);
        int right = fairnessfactor(tree, root->right);
        int res = (left > right ? left : right);
        if(root->color == black)
            return res + 1;
        else
            return res;
    }
}
int getapp(Node *a1, Node *a2)
{
    int x = fairnessfactor(a1, a1);
    int y = fairnessfactor(a2, a2);
    if (x > y)
        return 1;
    else
        return 2;
}
void traverse(Node *t, int k, int*flag)
{
    if (t != NULL && *flag)
    {
        traverse(t->left, k,flag);
        if (fairnessfactor(t, t) == k)
        {
            printf("%s\n", t->tid);
            *flag = 0;
            return;
        }
        traverse(t->right, k,flag);
    }
}
void select_task(Node *a1, Node *a2)
{
    int id = getapp(a1, a2);
    int flag = 1;
    if (id == 1)
    {
        int x = fairnessfactor(a2, a2);
        traverse(a1, x, &flag);
    }
    else
    {
        int x = fairnessfactor(a1, a1);
        traverse(a2, x, &flag);
    }
}
int main()
{
    freopen("sample2.ip" ,"r",stdin );
    Node *a1 = NULL;
    Node *a2 = NULL;
    a1root = &a1;
    a2root = &a2;
    char ch;
    while (EOF != (ch = fgetc(stdin)))
    {
        if (ch == 'i')
        {
            int x;
            char buff[101] = {0};
            int id;
            scanf("%s %d %d", buff, &x, &id);
            if (id == 1)
            {
                a1 = InsertRBTree(a1, buff, x, id);
                balanceInsertionRB(a1, x, id);
            }
            else
            {
                a2 = InsertRBTree(a2, buff, x, id);
                balanceInsertionRB(a2, x, id);
            }
        }
        if (ch == 'a')
        {
            int k;
            scanf("%d", &k);
            if (k == 1)
                printf("%d\n", fairnessfactor(a1, a1));
            else
                printf("%d\n", fairnessfactor(a2, a2));
        }
        if (ch == 'g')
        {
            printf("%d\n", getapp(a1, a2));
        }
        if (ch == 's')
        {
            select_task(a1, a2);
        }
        if (ch == 'p')
        {
            int k;
            scanf("%d", &k);
            if (k == 1)
                printTree(a1);
            else
                printTree(a2);
            printf("\n");
        }
        if( ch == 't')
            break;
    }
    purgeTree(a1);
    purgeTree(a2);

    return 0;
}
