#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node{
    int data;
    struct Node*left;
    struct Node*right;
};
typedef struct Node Node;
Node* createTreeNode(const int k){
    Node* n = malloc(sizeof(Node));
    n->data = k;
    n->left = NULL;
    n->right = NULL;
    return n;
}
int count(int n)
{
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}
void readnums(){
    char line[1024];
    int arr[1024];
    int I=0;
    fgets(line, 1024, stdin);
    line[strcspn(line,"\n")] = '\0';
    int i=0,d;
    char temp;
    do{
        if(sscanf(line+i,"%d",&d )){
            arr[I++]=d;
            i+= count(d);
            i+=1;
        }
        else
            i++;
    } while (temp != '\n' && i < strlen(line));
}
int getNumber(char* input, int* offset){
    int res =0;
    while(*offset < strlen(input) && input[*offset] != '(' && input[*offset] != ')'){
        int temp = input[*offset] - '0';
        res*=10;
        res+=temp;
        (*offset)++;
    }
    return res == 0 ? -1 : res;
}
Node* constructBinaryTree(char* input, int* offset){    
    if(!strlen(input) ||* offset >= strlen(input)){
        return NULL;
    }
    int n=getNumber(input, offset);
    if (n == -1 )
        return NULL;
    Node* tree = createTreeNode(n);
    if(*offset >= strlen(input))
        return tree;
    if(*offset < strlen(input) && input[*offset] == '('){
        (*offset)++;
        tree->left = constructBinaryTree(input, offset);
    }
    if(*offset < strlen(input) && input[*offset] == ')')
        (*offset)++;

    if(*offset < strlen(input) && input[*offset] == '('){
        (*offset)++;
        tree->right= constructBinaryTree(input, offset);
    }
    if(*offset < strlen(input) && input[*offset] == ')')
        (*offset)++;
    
    return tree;
}
Node* searchTree(Node* root, const int x){
    if(root == NULL){
        return NULL;
    }
    if(root->data == x){
        return root;
    }
    Node* left = searchTree(root->left , x);
    if(left != NULL)
        return left;

    Node* right = searchTree(root->right , x);
    if(right != NULL)
        return right;
}
int countBad(Node* root){
    if(root==NULL || root->left == NULL && root->right == NULL){
        return 0;
    }
    int count =0;
    if(root->left != NULL && root->left->data >= root->data){
       count++; 
    }
    else{
        count+= countBad(root->left);
    }
    if(root->right!= NULL && root->right->data <= root->data){
       count++; 
    }
    else{
        count+= countBad(root->right);
    }
    return count;
}
Node* LCA(Node* root,const int u, const int v){
    if(root == NULL)
        return NULL;
    
    if(root->data == u || root->data == v)
        return root;
    
    Node* left = LCA(root->left, u,v);
    Node* right= LCA(root->right, u,v);

    if(left!= NULL && right!= NULL)
        return root;

    return left == NULL ? right : left;
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
    char line[1024];
    int arr[1024];
    int I=0;
    
    fgets(line, 1024, stdin);
    line[strcspn(line,"\n")] = '\0';
    int k=0;
    char inp[1024];
    for(int i=1; i < strlen(line);i++)
        if(line[i] != ' ')
            inp[k++] =line[i];

    int index =0 ;
    inp[strlen(inp)-1] = '\0';
    Node* tree = constructBinaryTree(inp, &index);

    int u,v;
    scanf("%d %d", &u, &v);
    if(!(searchTree(tree,u) && searchTree(tree,v))){
        printf("-1\n");
        purgeTree(tree);
        return 0;
    }
    Node* lca = LCA(tree,u,v);
    printf("%d", lca->data);
    purgeTree(tree);
    return 0;

}