#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//void generate_random_array(int *p,int input);
int main(void){
	int input,*p,i;

	printf("how many songs required:\n");
	scanf("%d",&input);
	p = (int *)malloc(input*sizeof(int));
	if(p==NULL){
		printf("Allocation Failed...\n");
		return 1;
	}
//	generate_random_array(p,input);
	for(i =0;i<input;i++){
		p[i] =i+1;
		printf("%d  ",p[i]);
}
	
	return 0 ;
	
	
	
}

//void generate_random_array(int *p,int input){
//	srand((unsigned)time(NULL));
//	int i;
//	const int number = input;
//	int a[number]={0};
//	for(i=0;i<input;i++){
//		do{
//			*p = rand()%input +1;
//
//			
//		}while(a[*p-1] == 1);
//		a[*p-1] =1;
//		p++;	
//	}
//	
//}
