#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generate_random_array(int *p,int input);
int main(void){
	int input,*p,i;

	printf("how many songs required:\n");
	scanf("%d",&input);
	p = (int *)malloc(input*sizeof(int));
	if(p==NULL){
		printf("Allocation Failed...\n");
		return 1;
	}
	generate_random_array(p,input);
	for(i=0;i<input;i++){
		printf("%d\t",p[i]);
	}

	return 0 ;	
}
void generate_random_array(int *p,int input){
	srand((unsigned)time(NULL));
	int i,*a;
	a = (int *)malloc(input*sizeof(int));
	for(i=0;i<input;i++){
		a[i]=0;
	}
	for(i=0;i<input;i++){
		do{
			*p = rand()%input +1;
			
		}while(a[*p-1] == 1);
		/*printf("%d\t",*p);*/
		a[*p-1] =1;
		p++;	
	}	
}
