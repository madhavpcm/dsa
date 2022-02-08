#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct HashNode{
    char* data;
    struct HashNode* next;
};
typedef struct HashNode HashNode;

static int k=1;

int hashFunc(char* str){
    return (strlen(str)* strlen(str) % k);
}
HashNode* createNode(char* word){
    HashNode* n = malloc(sizeof(HashNode));
    n->data = word;
    n->next = NULL;
    return n;
}

int insertToHash(HashNode **node, char *word)
{
    HashNode *ptr = *node;
    HashNode *prev = ptr;
    if (ptr== NULL)
    {
        *node = createNode(word);
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
void printHashTable(HashNode** HT){
    for ( int i=0 ; i < k; i++) {
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
    
    scanf("%d ", &k);
    HashNode** HT = malloc(k* sizeof(HashNode*));

    for(int i=0 ; i< k; i++){
        HT[i] = (NULL);
    }

    char line[505] = {0};
    fgets(line, 505 ,stdin);
    line[strcspn(line, "\n")] =0;
    int j=0;
    for(int i=0 ; i < strlen(line)+1 ; i++)    {
        if(line[i] == ' ' || line[i] == '\0' ){
            int start = i - j;
            int index = (j * j) % k;

            char* word = malloc((j+1) * sizeof(char));
            memcpy(word,line+start,j );
            word[j] =0;

            int status = insertToHash(&HT[index], word );
            if(status)
                free(word);

            j=0;
            //free(word);
        }
        else{
            j++;
        }
    }
    printHashTable(HT);
    for(int i=0; i< k; i++){
        purgeList(&HT[i]);
        HT[i] = NULL;
    }
    free(HT);
    return 0;
}