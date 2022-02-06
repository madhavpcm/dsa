#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char* hashFunc(char* name){
    char* res = malloc(sizeof(char)*4);
    res[0] = name[0];
    if(strlen(name) < 3){
        int dig1 = name[0] + name[1]  ;
        dig1 %= 26;
        dig1 %= 10;

        int dig2 = name[0]; 
        dig2 %= 26;
        dig2 %= 10;

        int dig3 = name[0]; 
        dig3 %= 26;
        dig3 %= 10;
        res[1] = dig1 + 0x30;
        res[2] = dig2 + 0x30;
        res[3] = dig3 + 0x30;
    }
    else if( strlen(name) < 5){

        int dig1 = name[0] + name[1] + name[2]  ;
        dig1 %= 26;
        dig1 %= 10;

        int dig2 = name[0] + name[2]; 
        dig2 %= 26;
        dig2 %= 10;

        int dig3 = name[0]; 
        dig3 %= 26;
        dig3 %= 10;

        res[1] = dig1 + 0x30;
        res[2] = dig2 + 0x30;
        res[3] = dig3 + 0x30;

    }
    else if(strlen(name) < 9){


        int dig1 = name[0] + name[1] + name[2]  ;
        dig1 %= 26;
        dig1 %= 10;

        int dig2 = name[0] + name[2]+ name[4]; 
        dig2 %= 26;
        dig2 %= 10;

        int dig3 = name[0] + name[4]; 
        dig3 %= 26;
        dig3 %= 10;

        res[1] = dig1 + 0x30;
        res[2] = dig2 + 0x30;
        res[3] = dig3 + 0x30;

    }
    else{

        int dig1 = name[0] + name[1] + name[2]  ;
        dig1 %= 26;
        dig1 %= 10;

        int dig2 = name[0] + name[2]+ name[4]; 
        dig2 %= 26;
        dig2 %= 10;

        int dig3 = name[0] + name[4] + name[8]; 
        dig3 %= 26;
        dig3 %= 10;

        res[1] = dig1 + 0x30;
        res[2] = dig2 + 0x30;
        res[3] = dig3 + 0x30;
    }
    return res;
}

int main(){
    char** HT = malloc(1000*sizeof(char*));
    for(int i=0; i < 1000; i++)
        HT[i] = NULL;
    
    char ch;
    while(EOF != ( ch = fgetc(stdin))){
        if(ch == 'i'){
            char name[30];
            scanf(" %s", name);
            char* roll= hashFunc(name);
            int index =atoi(roll+1);
            HT[index] = calloc(0,30*sizeof(char));
            strcpy(HT[index], name);
            free(roll);
        }
        if(ch == 's'){
            char roll[4];
            scanf(" %s", roll);
            if(HT[atoi(roll+1)] == NULL){
                printf("NOT FOUND\n");
            }
            else{
                printf("%s\n", HT[atoi(roll+1)]);
            }
        }
        if (ch == 'd'){
            char roll[4];
            scanf(" %s", roll);
            if(HT[atoi(roll+1)] != NULL)
                free(HT[atoi(roll+1)]);
            HT[atoi(roll+1)] = NULL;
        }
    }
    return 0;
}