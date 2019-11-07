#include<stdio.h>
#define SIZE 128

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

    lo.y=0;
    lo.x=0;

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
            array[i][j] = '*';
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
    Co newlo_1;
    Co newlo_2;
    Co newlo_3;
    if(size<=4){
        return;
    }

    for(i=0;i<size/2;i++){
        for(j=0;j<size/4;j++){
            array[lo.y+i][lo.x+j] = ' ';
        }
    }
    for(i=0;i<size/2;i++){
        for(j=3*size/4;j<size;j++){
            array[lo.y+i][lo.x+j] = ' ';
        }
    }
    newlo_1.y = lo.y;
    newlo_1.x = lo.x+size/4;
    newlo_2.y=lo.y+size/2;
    newlo_2.x=lo.x;
    newlo_3.y=lo.y+size/2;
    newlo_3.x=lo.x+size/2;
    fulfill(array,newlo_1,size/2);
    fulfill(array,newlo_2,size/2);
    fulfill(array,newlo_3,size/2);






}
