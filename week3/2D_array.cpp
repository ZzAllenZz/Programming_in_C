#include<stdio.h>
int main(void){
	int array[3][5]={
		{1,2,3,4,5},
		{6,7,8,9,10},
		{11,12,13,14,15}
		};
	printf("sizeof int :%d\n",sizeof(int)); 
	printf("array: %p\n",array);
	printf("array+1: %p\n",array+1);
	printf("*(array+1):%p\n",*(array+1));
	printf("array[1]:%p\n",array[1]);
	printf("&array[1][0]:%p\n",&array[1][0]);
	
	}
	
