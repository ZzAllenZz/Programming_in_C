#include<stdio.h>
#define SIZE 81
/*
 require: log3(SIZE) must be a integer!; 
*/
typedef struct coordinate{
	int y;
	int x;
} Co;
void initialize_array(int array[SIZE][SIZE]); 
void print_array(int array[SIZE][SIZE]);
void fulfill(int array[SIZE][SIZE],Co lo,int size); 

int main(void){
	int array[SIZE][SIZE]; 
	Co lo;
	int size =4;
	/*
	use top-left corner to present the center of squares
	*/
	lo.y=SIZE/3;//: 81/3 = 27;
	lo.x=SIZE/3;//: 81/3 = 27;
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
	/*!!!
	Y[9] and X[9] need to be matched, and used in loop.
	|
	|
	|
	---->
	*/
	int Y[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int X[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};

	if(size==1){
		return;
	}

	
	/*when i = 4, X[4],Y[4] = 0,
	so it present the center of current squares.
	so we need to asign ' ' to matched array. 
	*/
	
	for(i=0;i<9;i++){
		if(i==4){
			for(j=0;j<(size)/3;j++){
				for(k=0;k<(size)/3;k++){
					array[lo.x+j][lo.y+k] = ' ';
					continue;/*not necessray~*/
				}
			}
		}
		/*find the center of subsquares and use the top-left one to represent it. */
		newlo.y=lo.y+Y[i]*size/3+size/9;  
		newlo.x=lo.x+X[i]*size/3+size/9;
		fulfill(array,newlo,size/3);
	}	
	/*
	recursion is useful because:
	everytime, when we find a new subsquare(call the fulfill function), we repeated the same step:
	divided into 9 parts, and print the centred one;
	*/
	
}
