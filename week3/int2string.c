#include<stdio.h>

#define DIFFERENCE '0'

void int2string(int i,char *s);
int main(void){
	int i;
	char s[256];
	printf("enter a integer:\n");
	scanf("%d",&i);
	int2string(i,s);
	printf("%s\n",s);
	return 0;
	
} 

void int2string(int i, char *s)
{
	int sign,j,count=0,k=0;
	char invert_s[256];
	if(i<0){
		sign = -1;
		i=-i;
	}else {
		sign =1 ;
	}
	if(i==0){
		invert_s[0]=i+DIFFERENCE;
	}
	
	while(i!=0){
		j= i%10;
		invert_s[k]= j+DIFFERENCE ;
		i= i/10;
		k++;
		count++;
	} 
	if (sign==-1){
		s[0]='-';
		for(k=0;k<count;k++){
		s[k+1]=invert_s[count-k-1];
		} 
	}else {
		for(k=0;k<count;k++){
		s[k]=invert_s[count-k-1];
		} 
	}
	

	
}
