#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Node{
    int data;
    char eid[101];
    struct Node*left;
    struct Node*right;
};
typedef struct Node Node;
Node* createTreeNode(char* str, const int k){
    Node* n = malloc(sizeof(Node));
    n->data = k;
    memset(n->eid, 0, 101*sizeof(char));
    if(str != NULL)
        strcpy(n->eid, str);

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
char* getString(char* input, int* offset){
    char* str = malloc(101*sizeof(char));
    memset(str, 0, sizeof(char)*101);
    int j=0;
    
    while(*offset < strlen(input) && input[*offset] != '(' && input[*offset] != ')' && input[*offset] != ' ' && j < 101){
        str[j++] = input[*offset];
        (*offset)++;
    }
    (*offset)++;
    if(strlen(str) == 0){
        free(str);
        str = NULL;
    }
    return str;
}
int getNumber(char* input, int* offset){
    int res =0;
    while(*offset < strlen(input) && input[*offset] != '(' && input[*offset] != ')' && input[*offset] != ' '){
        int temp = input[*offset] - '0';
        res*=10;
        res+=temp;
        (*offset)++;
    }
    (*offset)++;
    return res == 0 ? -1 : res;
}
Node* constructBinaryTree(char* input, int* offset){    
    if(!strlen(input) ||* offset >= strlen(input)){
        return NULL;
    }
    if(input[*offset] == ' ' || input[*offset] == ')'){
        return NULL;
    }
    char* str = getString(input, offset) ;
    int n=getNumber(input, offset);
    if (n == -1)
        return NULL;
    Node* tree = createTreeNode(str, n);
    char ch = input[*offset];
    if(*offset >= strlen(input))
        return tree;
    if(*offset < strlen(input) && input[*offset] == '('){
        (*offset)+=2;
        tree->left = constructBinaryTree(input, offset);
    }
    if(*offset < strlen(input) && input[*offset] == ')')
        (*offset)+=2;

    if(*offset < strlen(input) && input[*offset] == '('){
        (*offset)+=2;
        tree->right= constructBinaryTree(input, offset);
    }
    if(*offset < strlen(input) && input[*offset] == ')')
        (*offset)+=2;
    
    return tree;
}
void purgeTree(Node* root){
    if(root == NULL){
        return;
    }
    purgeTree(root->left);
    purgeTree(root->right);
    free(root);
}
void print_employees(Node* root){
    if(root != NULL){
        print_employees(root->left);
        printf("%s ", root->eid);
        print_employees(root->right);
    }
}
int find_emp(Node* root){
    if(root == NULL){
        return 0;
    }
    int left = find_emp(root->left);
    int right= find_emp(root->right);
    if(left == 0 && right == 0){
        return root->data;
    }
    if(root->data > left + right){
        printf("%s ", root->eid);
    
    }
    return root->data + left + right;


}
int main(){
    char line[10010] = {0};
    int arr[1024];
    int I=0;
    
    fgets(line, 10010, stdin);
    line[strcspn(line,"\n")] = '\0';
    int k=0;
    for(int i=0;i < 10010; i++){
        
    }
    int index =2 ;

    Node* tree = constructBinaryTree(line, &index);
    print_employees(tree);
    printf("\n");
    find_emp(tree);
    purgeTree(tree);
    return 0;
}