#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
    int key;
    struct node* next;
};
typedef struct node node;
node* create_node(const int key){
    node* n= (node*)malloc(sizeof(node));
    n->key = key;
    n->next = NULL;
    return n;
}
node* list_search(node** L,const int key){
    node* curr = *L;
    while(curr != NULL){
        if(curr->key == key){
            return curr;
        }
        curr= curr->next;
    }
    return NULL;
}
void list_insert_front(node**L ,const int x){
    node* new_front = create_node(x); 
    new_front->next = *L;
    *L = new_front;
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
void list_purge(node**L){
    node* l = *L;
    while(l!= NULL){
        node* n = l->next;
        free(l);
        l= n;
    }
}
int main(){
    node* L=NULL;
    char line[10000];
    int n=0;
    int d;
    char temp;
    int i=0;
    
    memset(line,0,10000*sizeof(char));
    fgets(line, 10000, stdin);
    do{
        if(sscanf(line+i,"%d%c",&d, &temp)){
            list_insert_front(&L,d);
            i+= count(d);
            i+=1;
            n++;
        }
        else
            break;
    } while (temp != '\n');
    int k;
    scanf("%d",&k);
    i=1;
    node* ptr = L;
    if(k<=n){
        while(ptr!= NULL && i!=k){
            ptr=ptr->next;
            i++;
        }
        printf("%d\n",ptr->key);
    }
    else{
        printf("-1\n");
    }
    list_purge(&L);
    return 0;
}