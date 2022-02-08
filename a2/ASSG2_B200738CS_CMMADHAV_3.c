#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    char fname[30];
    char lname[30];
    int age;
    struct Node* p;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;
Node* createNode(char* fname, char* lname, const int age){
    Node* n = malloc(sizeof(Node));

    strcpy((n->fname), fname);
    strcpy((n->lname), lname);
    n->age= age; 
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
Node* Insert(Node** n,char*fname ,char* lname, const int age){
    if((*n) == NULL) {
        return createNode(fname,lname,age);
    }
    if((*n)->age > age){
        Node* x = Insert(&((*n)->left),fname,lname,age ) ;
        (*n)->left =x;
        x->p = *n;
    }
    else if( (*n)->age < age){
        Node* x = Insert(&((*n)->right),fname,lname,age) ;
        (*n)->right=x;
        x->p = *n;
    }
    return *n;

}
//4,5
void Delete(Node** n,Node* z){
    Node* y = NULL;
    Node* x = NULL;
    if(z == NULL){
        printf("-1\n");
        return;
    }
    int res = z->age;
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
        z->age = y->age;
        strcpy(z->fname,y->fname);
        strcpy(z->lname,y->lname);
    }
    //printf("%d\n",res);
    free(y);

}
Node* Search(Node* n,const int age){
    if(n == NULL){
        return NULL;
    }
    if(n->age == age){
        return n;
    }
    else if( n->age > age){
        return Search(n->left,age);
    }
    else if( n->age < age){
        return Search(n->right,age);
    }

}
int StrSearch(Node* n, char* fname){
    if(n == NULL)
        return 0;
    
    if(!strcmp(fname, n->fname)){
        return n->age;
    }
    return StrSearch(n->left,fname) | StrSearch(n->right,fname);
}
void Inorder(Node*n ){
    if(n!=NULL){
        Inorder(n->left);
        printf("%d ",n->age);
        Inorder(n->right);
    }
}
void Preorder(Node*n ){
    if(n!=NULL){
        printf("%d ",n->age);
        Preorder(n->left);
        Preorder(n->right);
    }
}
void Postorder(Node*n ){
    if(n!=NULL){
        Postorder(n->left);
        Postorder(n->right);
        printf("%d ",n->age);
    }
}
void QPrint(Node* n, char* fname, int age){
    if(n == NULL){
        return;
    }
    printf("%s %s %d\n", n->fname, n->lname, n->age);
    if(n->age > age){
        QPrint(n->left, fname, age);
    }
    else if(n->age < age){
        QPrint(n->right, fname, age);
    }
    return;
}
void PurgeTree(Node*root){
    if(root == NULL)
        return;
    PurgeTree(root->left);
    PurgeTree(root->right);
    free(root);
}
int main(){
    Node** HT = malloc(128*sizeof(Node*));
    for(int i=0; i< 128; i++)
        HT[i] = NULL;
    

    char ch;
    while(EOF!= (ch = fgetc(stdin))){
        if(ch == 'i'){
            char fname[30]={0},lname[30]={0};
            int age;
            scanf(" %s %s %d", fname, lname,&age);
            int index=0;
            for(int i=0; i< strlen(lname); i++){
                index+=lname[i];
            }
            index %= 128;
            HT[index] = Insert(&HT[index],fname,lname,age);
            HT[index] = Insert(&HT[index],fname,lname,age);
        }
        if(ch == 'p'){
            char fname[30]={0},lname[30]={0};
            int index =0;
            scanf(" %s %s", fname, lname);

            for(int i=0; i < strlen(lname); i++)
                index+=lname[i];
            
            index %= 128;
            int age = StrSearch(HT[index],fname );
            if(!age){
                printf("-1\n");
            }
            else{
                QPrint(HT[index], fname, age );
            }

        }

    }
    for(int i=0; i< 128; i++){
        PurgeTree(HT[i]);
    }
    free(HT);
    return 0;
}