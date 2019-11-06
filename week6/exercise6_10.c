#include<stdio.h>
#define SIZE 100

typedef struct coordinate{
	int y;
	int x;
} Co;
void initialize_array(int array[SIZE][SIZE]); 
void print_array(int array[SIZE][SIZE]);
void fulfill(int array[SIZE][SIZE],Co lo,int size); 

int main(void){
	int array[SIZE][SIZE]; 
	int i,j;
	Co lo;

	lo.y=SIZE-1;
	lo.x=1;
	for(i=0;i<1;i++){
		for(j=0;j<1;j++){
			a
		}
	}
	initialize_array(array);
	printf("initial pattern:\n");
	print_array(array);
	printf("Sierpinski Carpet Pattern:\n");
	fulfill(array,lo,SIZE);
	print_array(array);
	
} 

void initialize_array(int array[SIZE][SIZE]){
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			array[i][j] = '#';
		}
	}
	return ;
}

void print_array(int array[SIZE][SIZE]){
	int i,j,k;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			printf("%c",array[i][j]);
		}
		printf("\n");
	}
	return ;
}


void fulfill(int array[SIZE][SIZE],Co lo, int size){

	int i,j,k;
	Co newlo;


	if(size>SIZE){
		return;
	}

	for(i=0;i<9;i++){
		if(i==4){
			for(j=0;j<(size)/3;j++){
				for(k=0;k<(size)/3;k++){
					array[lo.x+j][lo.y+k] = ' ';
					continue;
				}
			}
		}
		newlo.y=lo.y+Y[i]*size/3+size/9;  
		newlo.x=lo.x+X[i]*size/3+size/9;
		fulfill(array,newlo,size/3);
	}	

	
}
