
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define N 21
void generate_square(char array[N][N]);
void center(char array[N][N]);
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
	center(array);
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

void center(char array[N][N])
{
	int x1,y1,x2,y2,a,temp,i,distance1,distance2;
	int x0=(N)/2;/*???*/
	int y0=(N)/2;/*???*/
	
	for(i=0;i<N*N*N*N;i++){
		x1= rand()%N;
		y1= rand()%N;
		x2= rand()%N;
		y2= rand()%N;
		distance1 = (int)sqrt(pow(abs((x1-x0)),2)+pow(abs(y1-y0),2));
		distance2 = (int)sqrt(pow(abs(x2-x0),2)+pow(abs(y2-y0),2));
		if(distance1<distance2){
			if(array[y1][x1]>array[y2][x2]){
			temp = array[y1][x1];
			array[y1][x1]=array[y2][x2];
			array[y2][x2] = temp;
			}
		}
		if(distance1>distance2){
			if(array[y1][x1]<array[y2][x2]){
			temp = array[y1][x1];
			array[y1][x1]=array[y2][x2];
			array[y2][x2] = temp;
			}
		}
}
}
