#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int generate_result(int A,int B,int C); 
void present(int *first_array,int *next_array,int kind,int column,int row,int location);
int main(void){
    int *first_array,*next_array,kind,column,row,location;
    printf("how many columns in first row:\n");
    scanf("%d",&column);
    printf("how many rows:\n");
    scanf("%d",&row);
    printf("which kinds:(1 for randomized, 2 for a central 1£¬3 for a certain location of 1)\n");
    scanf("%d",&kind); 
    if(kind ==3){
    	printf("the location of 1:\n");
    	scanf("%d",&location);
	}
    first_array = (int *)malloc(column*sizeof(int));
    next_array = (int *)malloc(column*sizeof(int));
    present(first_array,next_array,kind,column,row,location);

	return 0 ;
}

int generate_result(int A,int B,int C){
	int result;
	result = !((A&B&C)||(A&!B&!C)||(!A&!B&!C));
	return result; 
}

void present(int *first_array,int *next_array,int kind,int column,int row,int location){
	int i,j;
	srand((unsigned)time(NULL));
	if(kind ==1){
		for(i =0;i<column;i++){
			first_array [i]= rand()%2;
			printf("%d ",first_array [i]);
		}
	}else if (kind == 2){
		for(i =0;i<column;i++){
			if(column%2==0 && i==column/2-1){
				first_array [i]= 1;
				printf("%d ",first_array [i]);
			}else if(column%2 !=0 && i==(column+1)/2-1){
				first_array [i]= 1;
				printf("%d ",first_array [i]);
			}else{
				first_array [i]= 0; 
				printf("%d ",first_array [i]);
			}
		}
	}else if (kind ==3){
		for(i =0;i<column;i++){
		if(i ==location-1){
			first_array[i] = 1;
			printf("%d ",first_array [i]);

		}else {
			first_array[i] =0;
			printf("%d ",first_array [i]);
		}
		}
	}
	printf("\n");
	for(i=1;i<row;i++){
		next_array[0]=0;
		printf("%d ",next_array[0]);
		for(j=1;j<column-1;j++){
		next_array[j]= generate_result(first_array[j-1],first_array[j],first_array[j+1]);
		printf("%d ",next_array[j]);
		}
		next_array[column-1]=0;
		printf("%d ",next_array[column-1]);
		printf("\n");
		for(j=0;j<column;j++){
			first_array[j]= next_array[j]; 
			}
	}

}
