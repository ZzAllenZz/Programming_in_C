#include<stdio.h>

int main(void){
	char str[3]= {'a','b','c'};
//	scanf("%s",str);
	printf("%s",str);
	printf("%p\n",str);
	printf("%p\n",str++);//报错，str不是左值 
	printf("%p\n",&str[1]) ;
	return 0;
} 
