#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<ctype.h>
struct HashNode{
    char data[105];
    struct HashNode* next;
};
typedef struct HashNode HashNode;
HashNode* createNode(char* word){
    HashNode* n = malloc(sizeof(HashNode));
    memset(n->data,0,105*sizeof(char));
    strcpy(n->data, word);
    n->next = NULL;
    return n;
}
int hash_func1(int n, char*word){
    int l = strlen(word);
    if(l == 1)
        return (2*word[0]) % n;
    else{
        int end = l -1;
        int index =  (word[0] + word[1] + word[end] + word[end-1]) ;
        if(index % l == 0)
            index /= l;
        else{
            index = index/l;
            index++;

        }
        index %= n;
        return index;
    }
}
int hash_func2(int n, char* word){
    int index =0;
    for(int i=0; i < strlen(word) ; i++){
        index += word[i];
    }
    index /= strlen(word);
    index %= n;
    return index;
}
int list_size(HashNode* node){
    if(node == NULL)
        return 0;
    int i=0;
    while(node != NULL ){
        node = node->next;
        i++;
    }
    return i;
}
int list_insert(HashNode **node, char *word, const int index)
{
    HashNode *ptr = node[index];
    int hi = strlen(word);
    if (ptr== NULL)
    {
        node[index] = createNode(word);
        return 0;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = createNode(word);
    }
    return 0;
}
void store_word(HashNode** H , const int n, char* word){
    int x1= hash_func1(n,word)    ;
    int x2 = hash_func2(n,word);
    int h1 = list_size(H[x1]);
    int h2 = list_size(H[x2]);
    

    if( h1<= h2)
        list_insert(H,word,x1);
    else
        list_insert(H,word,x2);
    
    return;
}
void printHashTable(HashNode** HT,int n){
    for ( int i=0 ; i < n; i++) {
        if(HT[i]== NULL){
            printf("NULL");
        }
        else {
            HashNode* ptr = HT[i];
            while(ptr!=NULL){
                printf("%s ", ptr->data);
                ptr = ptr->next;
            }
        }
            printf("\n");
    }
}
void purgeList(HashNode** list){
    HashNode* ptr = *list;
    HashNode* tmp;
    while(ptr != NULL){
        tmp = ptr->next;
        free(ptr->data);
        free(ptr);
        ptr = tmp;
    }
}

int main(){
    int n;
    char line[100010] = {0};
    scanf("%d ", &n);
    fgets(line,100010,stdin);
    line[strcspn(line, "\n")] = ' ';

    HashNode** H = malloc(n*sizeof(HashNode*));
    for(int i=0; i < n; i++)
        H[i] = NULL;
    
    int j=0;
    char buffer[101]={0};
    for(int i=0; i < 100010 && line[i] != 0; i++){
        if(line[i] == ' ' ){
            j=0;
            store_word(H,n,buffer);
            memset(buffer,0,105*sizeof(char));
        }
        else{
            buffer[j++] = line[i];
        }
    }
    printHashTable(H,n);

    free(H);
    return 0;
}