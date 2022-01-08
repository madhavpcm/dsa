
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Node{
    int data;
    struct Node* p;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;
Node* createNode(const int k){
    Node* n = malloc(sizeof(Node));

    n->data = k; 
    n->left = NULL;
    n->right = NULL;
    n->p = NULL;
}
Node* minBst(Node* n){
    if(n == NULL){
        return NULL;
    }
    Node* curr = n;
    while(curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}
Node* maxBst(Node* n){
    if(n == NULL){
        return NULL;
    }
    Node* curr = n;
    while(curr->right!= NULL){
        curr = curr->right;
    }
    return curr;
}
Node* Successor(Node* n, Node* x){
    if(x->right !=NULL) {
        return minBst(x->right);
    }
    Node* p = x->p;
    while(p!= NULL && p->right == x){
        x = p;
        p = p->p;
    }
    return p;
}
Node* Predecessor(Node*n , Node* x){
    if(x->left != NULL){
        return maxBst(x->left);
    }
    Node* p = x->p;
    while(p!=NULL && p->left == x){
        x = p;
        p = p->p;
    }
    return p;
}
Node* Insert(Node** n,const int k){
    if((*n) == NULL) {
        return createNode(k);
    }
    if((*n)->data > k){
        Node* x = Insert(&((*n)->left),k) ;
        (*n)->left =x;
        x->p = *n;
    }
    else if( (*n)->data < k){
        Node* x = Insert(&((*n)->right),k) ;
        (*n)->right=x;
        x->p = *n;
    }
    return *n;

}
void Delete(Node** n,Node* z){
    Node* y = NULL;
    Node* x = NULL;
    if(z == NULL){
        printf("-1\n");
        return;
    }
    int res = z->data;
    if(z->left == NULL || z->right == NULL)
        y = z;
    else
        y = Successor(*n,z);

    if(y->left != NULL)
        x = y->left;
    else
        x = y->right;
    if(x!=NULL){
        x->p = y->p;
    }
    

    if(y->p == NULL)
        *n = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    if(y != z){
        z->data = y->data;
    }
    printf("%d\n",res);
    free(y);

}
Node* Search(Node* n,const int x){
    if(n == NULL){
        return NULL;
    }
    if(n->data == x){
        return n;
    }
    else if( n->data > x){
        return Search(n->left,x);
    }
    else if( n->data < x){
        return Search(n->right,x);
    }

}
void Inorder(Node*n ){
    if(n!=NULL){
        Inorder(n->left);
        printf("%d ",n->data);
        Inorder(n->right);
    }
}
void Preorder(Node*n ){
    if(n!=NULL){
        printf("%d ",n->data);
        Preorder(n->left);
        Preorder(n->right);
    }
}
void Postorder(Node*n ){
    if(n!=NULL){
        Postorder(n->left);
        Postorder(n->right);
        printf("%d ",n->data);
    }
}
void PurgeTree(Node*root){
    if(root == NULL)
        return;
    PurgeTree(root->left);
    PurgeTree(root->right);
    free(root);
}
void Level(Node* root, const int k){
    Node* ptr = Search(root, k);
    if(ptr == NULL){
        printf("-1\n");
        return;
    }
    int c =0;
    while(ptr!=NULL){
        ptr = ptr->p;
        c++;
    }
    printf("%d\n",c);

}
int main(){
    char ch;
    Node* root = NULL;
    //freopen("1.txt", "r", stdin);
    while (EOF != (ch = fgetc(stdin)))
    {
        if (ch == 'a')
        {
            int x;
            scanf(" %d", &x);
            root = Insert(&root, x);
        }
        if (ch == 'd')
        {
            int x;
            scanf(" %d", &x);
             Delete(&root,Search(root,x));
            if(root == NULL){
                printf("-1\n");
            }
        }
        if (ch == 's')
        {
            int x;
            scanf(" %d", &x);
            Node* res = Search(root,x);
            if(res == NULL){
                printf("-1\n");
            }
            else{
                printf("1\n");
            }
        }
        if (ch == 'u')
        {
            int x;
            scanf("%d", &x);
            Node* ser = Search(root,x);
            if(ser == NULL){
                printf("-1\n");
            }
            else{
                Node* res = Successor(root,ser);
                if(res!=NULL)
                    printf("%d\n",res->data);
                else
                    printf("-1\n");
            }
        }
        if (ch == 'r')
        {
            int x;
            scanf("%d", &x);
            Node* ser = Search(root,x);
            if(ser == NULL){
                printf("-1\n");
            }
            else{
                Node* res = Predecessor(root,ser);
                if(res!=NULL)
                    printf("%d\n",res->data);
                else
                    printf("-1\n");
            }
        }
        if (ch == 'i')
        {
            Inorder(root);
            printf("\n");
        }
        if (ch == 'p')
        {
            Preorder(root);
            printf("\n");
        }
        if (ch == 't')
        {
            Postorder(root);
            printf("\n");
        }
        if (ch == 'e')
        {
            break;
        }
        if( ch =='l'){
            int x;
            scanf(" %d", &x);
            Level(root,x);
        }
        if(ch == 'm'){
            Node* mn = minBst(root);
            if(mn == NULL){
                printf("-1\n");
            }
            else{
                printf("%d\n",mn->data );
            }
        }
        if(ch == 'x'){
            Node* mx = maxBst(root);
            if(mx == NULL){
                printf("-1\n");
            }
            else{
                printf("%d\n",mx->data );
            }

        }
    }
    PurgeTree(root);
    return 0;
}