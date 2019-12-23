#include<stdio.h>
#include<stdlib.h>
#define N 20
void generate_square(char array[N][N]);
void mutate(char array[N][N]);
int main (void)
{
	char array[N][N];
	int i,j;

	generate_square(array);
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d",array[i][j]);	
		}
		printf("\n");
	} 
	printf("\n");
	printf("\n");
	mutate(array);
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d",array[i][j]);	
		}
		printf("\n");
	} 
	
}

void generate_square(char array[N][N]){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
		array[i][j] = rand()%10;	
		}
	} 
}

void mutate(char array[N][N])
{
	int x1,y1,x2,y2,a,temp,i;
	
	for(i=0;i<N*N*N;i++){
		do{
			x1= rand()%N;
			y1= rand()%N;
			x2=x1+1;
			
		}while(x1==N-1);
		if(array[y1][x1]>array[y1][x2]){
			temp = array[y1][x1];
			array[y1][x1]=array[y1][x2];
			array[y1][x2] = temp;
			
		}
		do{
			x1= rand()%N;
			y1= rand()%N;
			y2=y1+1;
			
		}while(y1==N-1);
		if(array[y1][x1]>array[y2][x1]){
			temp = array[y1][x1];
			array[y1][x1]=array[y2][x1];
			array[y2][x1] = temp;
			
		}
	}
}
