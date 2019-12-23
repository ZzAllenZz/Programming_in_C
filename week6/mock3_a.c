#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20
void initial_board(int board[N][N]);
void mutate_board(int board[N][N]);
int main(void){
    int board[N][N];
    int i,j;
    initial_board(board);
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    mutate_board(board);
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d",board[i][j]);
        }
        printf("\n");
    }
    return 0;

}

void initial_board(int board[N][N]){
    int i,j;
    srand((unsigned)time(NULL));
    
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            board[i][j]=rand()%10;
        }
    }
}

void mutate_board(int (*board)[N]){
    int i;
    int random1,random2;
    int temp=0;
    srand((unsigned)time(NULL));
    for(i=0;i<N*N*N;i++){
        random1=rand()%(N);
        random2=rand()%(N-1);
        if(board[random1][random2]>board[random1][random2+1]){
            temp = board[random1][random2];
            board[random1][random2]=board[random1][random2+1];
            board[random1][random2+1] =temp;
        }
        random1=rand()%(N-1);
        random2=rand()%(N);
        if(board[random1][random2]>board[random1+1][random2]){
            temp=board[random1][random2];
            board[random1][random2]=board[random1+1][random2];
            board[random1+1][random2] =temp;
        }

    }

}