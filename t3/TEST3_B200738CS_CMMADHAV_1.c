#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
	char line[10001] = {0};
	fgets(line, 10001, stdin);
	line[strcspn(line,"\n")] = 0;
	char w1[101], w2[101];
	scanf("%s", w1);
	scanf("%s", w2);
	char arr[1001][1001];
	int i=0;
	int j=0;
	int mxlen = strlen(line);
	char word[101];
	while(i<mxlen && sscanf(line+i, "%s", word)){
		strcpy(arr[j], word);		
		j++;
		i+=strlen(word)+1;
	}	
	for(int k=0; k < j; k++){
		if(!strcmp(arr[k], w1)){
			memset(arr[k], 0, sizeof(word));
			strcpy(arr[k], w2);
		}
	}
	for(int k=0; k< j; k++){
		printf("%s ", arr[k]);
	}
	printf("\n");
	return 0;
}
