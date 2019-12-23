#include<stdio.h>
#include<string.h>
#define SWAP(A,B){char temp;temp=A;A= B;B= temp;}

void Reverse_String(char *s,int n);

int main(void){
	char str[]="HelloWorld";
	Reverse_String(str,strlen(str));
	printf("%s\n",str);
}

Reverse_String(char *s, int n)
{
	int i,j;
	for(i=0,j=n-1;i<j;i++,j--){
		SWAP(s[i],s[j]);
	}
}
