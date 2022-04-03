#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MX 100000
int main(){
	int x[MX], y[MX];
	int sum[MX+1];
	memset(x,0,MX*sizeof(int));
	memset(y,0,MX*sizeof(int));
	memset(sum,0,MX*sizeof(int));
	int n,m;
	int carry=0;
	scanf("%d %d" , &n, &m);
	for(int i=0; i < n; i++)	{
		scanf("%d", &x[MX-i-1]);
	}
	for(int i=0; i < m; i++)	
		scanf("%d", &y[MX-i-1]);
	int sl = n> m ? n : m;
	for(int i=sl; i < MX+1 ; i++){
		int rawsum = x[i] + y[i] + carry;		
		carry = rawsum / 7;
		sum[i] =  (rawsum % 7);
	}
	int i=0;
	for(i = MX; i >=  0; i--)
		if(sum[i]) break;

	for(; i >= MX-sl ; i--){
		printf("%d ", sum[i]);	
	}
	return 0;
}
