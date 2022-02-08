#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include<ctype.h>
struct HashNode{
    char data[30];
    struct HashNode* next;
};
typedef struct HashNode HashNode;

static int64_t n=1;
int64_t pwr(int n, int j){
    int64_t res =1; 
    for(int i =0; i <j ; i++){
        res*=n;
    }
    return res;
}
int hashFunc(char* str){
    int index =0;
    for (int i=0; i < strlen(str); i++){
        index+= ((toupper(str[i]) - 'A')+1)*pwr(3,i) ;
    }
    index %= n;
    return index;
}
HashNode* createNode(char* word){
    HashNode* n = malloc(sizeof(HashNode));
    strcpy(n->data, word);
    n->next = NULL;
    return n;
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
int hash_insert(HashNode **node, char *word)
{
    HashNode *ptr = node[hashFunc(word)];
    int hi = hashFunc(word);
    HashNode *prev = ptr;
    if (ptr== NULL)
    {
        node[hashFunc(word)] = createNode(word);
        return 0;
    }
    else
    {
        while (ptr != NULL)
        {
            if (!strcmp(ptr->data, word))
                return 1;
            prev = ptr;
            ptr = ptr->next;
        }
        prev->next = createNode(word);
    }
    return 0;
}
int hash_delete(HashNode **table, char* key){
    HashNode* ptr = table[hashFunc(key)];
    HashNode* prev = ptr;

    if(ptr == NULL)
        return -1;
    
    if(!strcmp(ptr->data, key)){
        free(ptr);
        table[hashFunc(key)] = NULL;
    }
    else{
        while(ptr != NULL){
            if(!strcmp(ptr->data, key)){
                prev->next = ptr->next;
                free(ptr);
                return 0;
            }
            prev = ptr;
            ptr = ptr->next;
        }
    }
    return -1;
}
int hash_11(HashNode** table){
    for(int i=0; i < n; i++){
        int len = list_size(table[i]);
        if(len != 1 && len!=0){
            return 0;
        }
    }
    return 1;
}
void printHashTable(HashNode** HT){
    for ( int i=0 ; i < n; i++) {
        if(HT[i]== NULL){
            printf("%d:null", i);
        }
        else {
            HashNode* ptr = HT[i];
            printf("%d:",i);
            while(ptr!=NULL){
                printf("%s", ptr->data);
                ptr = ptr->next;
                if(ptr!=NULL)
                    printf("-");
            }
        }
            printf("\n");
    }
    printf("---\n");
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
    char ch;
    scanf("%d", &n);
    HashNode** table = malloc(n*sizeof(HashNode*));
    for(int i=0; i< n; i++){
        table[i] = NULL;
    }

    while(EOF != (ch = fgetc(stdin))){
        if (ch == 'i'){
            char str[30];
            scanf(" %s", str);
            hash_insert(table, str);
        }
        if (ch == 'd'){
            char str[30];
            scanf(" %s", str);
            hash_delete(table, str);
        }
        if (ch == 'p'){
            if(hash_11(table)){
                printf("1\n");
            }
            else{
                printf("-1\n");
            }
        }
        if (ch == 't'){
            break;
        }
    }
    free(table);
    return 0;
}