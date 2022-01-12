
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
Node* treeFind(Node* root, const int x){
    if(root == NULL){
        return NULL;
    }
    if(root->data == x){
        return root;
    }
    Node* left = treeFind(root->left , x);
    if(left != NULL)
        return left;

    Node* right = treeFind(root->right , x);
    if(right != NULL)
        return right;
}

void purgeTree(Node* root){
    if(root == NULL){
        return;
    }
    purgeTree(root->left);
    purgeTree(root->right);
    free(root);
}
void checkdown(Node* root, const int k , int* sum){
    if (k < 0 || root == NULL)
        return;
    
    checkdown(root->left,k-1,sum);
    checkdown(root->right,k-1,sum);

    if (k >= 0){
        (*sum) += root->data;
        return;
    }


}
int func(Node* root , Node* res, const int k, int* sum){
    if (root == NULL)
        return -1;
    
    if(root == res){
        checkdown(res, k, sum);
        return 0;
    }

    int left = func(root->left, res, k, sum);

    if(left +1 != 0){
        if(left + 1 <= k){
            (*sum) += root->data;
            checkdown(root->right, k-left-2,sum);
        }
        return left+1; 
    }
    int right = func(root->right, res, k , sum);
    if(right +1 != 0){
        if(right + 1 <= k){
            (*sum) += root->data;
            checkdown(root->left, k-right-2,sum);
        }
        return right+1; 
    }
    return -1;
}
int main(){
    char line[10240];
    int arr[10240];
    int I=0;
    
    fgets(line, 1024, stdin);
    line[strcspn(line,"\n")] = '\0';
    int j=0;
    char inp[1024];
    for(int i=1; i < strlen(line);i++)
        if(line[i] != ' ')
            inp[j++] =line[i];

    int index =0 ;
    inp[strlen(inp)-1] = '\0';
    Node* tree = constructBinaryTree(inp, &index);

    int d,k;
    scanf("%d %d", &d, &k);
    Node* res = treeFind(tree, d);
    int sum=0;
    int p =func(tree,res,k,&sum);
    printf("%d\n", sum);
    purgeTree(tree);
    return 0;

}