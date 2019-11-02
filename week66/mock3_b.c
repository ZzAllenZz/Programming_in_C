#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#define N 21
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
    int random1,random2,random3,random4;
    double centre_x,centre_y;
    int temp=0;
    double distance1 =0,distance2 =0;
    srand((unsigned)time(NULL));

    centre_x=N/2-0.5;
    centre_y=N/2-0.5;
    for(i=0;i<N*N*N*N;i++){
        random1=rand()%(N);
        random2=rand()%(N);
        random3=rand()%(N);
        random4=rand()%(N);
        distance1 = pow(abs(random1-centre_y),2)+pow(abs(random2-centre_x),2);
        distance2 = pow(abs(random3-centre_y),2)+pow(abs(random4-centre_x),2);
        if(distance1>distance2&&board[random1][random2]<=board[random3][random4])
        {
            temp = board[random1][random2];
            board[random1][random2]=board[random3][random4];
            board[random3][random4] =temp;
        }
    }

}