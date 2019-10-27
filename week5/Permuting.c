#include<stdio.h>
#include<string.h>
#define SWAP(A,B){char temp;temp=A;A= B;B= temp;}
void permute(char *a,int i,int r);

int main(void){
	char str[]= "ABC";
	int n = strlen(str);
	permute(str,0,n-1);
	return 0;
}

void permute(char *a, int l,int r)
{
	int i;
	if(l==r){
		printf("%s\n",a);
	}
	for(i=1;i<=r;i++){
		printf("round \n");
		SWAP(a[l],a[i]);
		printf("%s\n",a);
		permute(a,l+1,r);
		printf("%s\n",a);
		SWAP(a[l],a[i]);
		printf("%s\n",a);
	}
}
