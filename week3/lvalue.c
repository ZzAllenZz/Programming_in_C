#include<stdio.h>

int main(void){
	char str[3]= {'a','b','c'};
//	scanf("%s",str);
	printf("%s",str);
	printf("%p\n",str);
	printf("%p\n",str++);//����str������ֵ 
	printf("%p\n",&str[1]) ;
	return 0;
} 
