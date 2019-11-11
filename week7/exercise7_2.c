#include<stdio.h>
#include<assert.h>
#include<malloc.h>

#define MAXSIZE 362880
#define SIZE 3

typedef struct node{
    char board[SIZE][SIZE];
    int parent ;
} Node;

typedef struct queue{
    Node n[MAXSIZE];
    int front;
    int back;
} Queue;

void initialise_node(Node *t,char *p);
void initialise_queue(Queue *q);
void insert(Node *t, Queue *q);
void move(Queue *q);
int is_empty_queue(Queue *q);
int is_empty(char c);
int search_exist(Queue *q, Node new_one);
int match_target(Node new_one);
void find_next_board(Queue *q);
void print_board(Node t);
void show_result(char *p);
void test();
void find_parent(Queue *q, Node t);

int main (void)
{
    test();
    show_result("513276 48");
    return 0;
}
void test()
{
    static Queue q;
    Node *t;
    int i,j;
    t = (Node *)malloc(sizeof(Node));
    initialise_queue(&q);
    initialise_node(t,"513276 48");
//    for(i=0;i<SIZE;i++){
//        for(j=0;j<SIZE;j++){
//            printf("%c",t->board[i][j]);
//        }
//        printf("\n");
//    }
    insert(t,&q);
    assert(q.n[0].board[1][1]=='7');
    assert(q.n[0].board[2][2]=='8');
    assert(q.n[0].board[0][1]=='1');
    t->board[0][0]='1';
    t->board[0][1]='2';
    t->board[0][2]='3';
    t->board[1][0]='4';
    t->board[1][1]='5';
    t->board[1][2]='6';
    t->board[2][0]='7';
    t->board[2][1]='8';
    t->board[2][2]=' ';
    assert(match_target(*t)==1);

}
void show_result(char *p){
    static Queue q;
    Node *t;
    int i,j;
    t = (Node *)malloc(sizeof(Node));
    initialise_queue(&q);
    initialise_node(t,p);
    insert(t,&q);

    while(!match_target(q.n[q.back-1])&&!is_empty_queue(&q)){
        find_next_board(&q);

    }
    if(is_empty_queue(&q)){
        printf("cannot find the solution");
        return;
    }
//    print_board(q.n[q.back-1]);

    find_parent(&q,q.n[q.back-1]);

}
void find_next_board(Queue *q)
{
    int i,j;
    int k,l,m;
    int y[4]={-1,1,0,0};
    int x[4]={0,0,-1,1};

    Node new_node;
    for(i=0;i<SIZE;i++) {
        for(j=0;j<SIZE;j++) {
            new_node.board[i][j]=q->n[q->front].board[i][j];
        }
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(is_empty(q->n[q->front].board[i][j])){
                for(k=0;k<4;k++){
                    if((i+y[k])<=2&&(i+y[k])>=0&&(j+x[k])<=2&&(j+x[k])>=0){

                        new_node.board[i][j]= q->n[q->front].board[i+y[k]][j+x[k]];
                        new_node.board[i+y[k]][j+x[k]] = q->n[q->front].board[i][j];
                        if(!search_exist(q,new_node)){
                            new_node.parent = q->front+1;
                            insert(&new_node,q);
                        }
                        if(match_target(new_node)){
                            return;
                        }
                        for(l=0;l<SIZE;l++) {
                            for(m=0;m<SIZE;m++) {
                                new_node.board[l][m]=q->n[q->front].board[l][m];
                            }
                        }
                    }
                }
                move(q);
                return ;
            }
        }
    }

}



void initialise_node(Node *t,char *p)
{
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            t->board[i][j]= *p;
            p++;
        }
    }

    t->parent =0;
}
void initialise_queue(Queue *q)
{
    q->front = 0;
    q->back = 0;
}
void insert(Node *t, Queue *q)
{
    q->n[q->back]= *t;
    q->back = (q->back+1)%MAXSIZE;
}

void move(Queue *q) {
    q->front=(q->front+1);
}





int is_empty_queue(Queue *q){
    if(q->front ==q->back){
        return 1;
    }else{
        return 0;
    }

}
int is_empty(char c){
    if(c==' '){
        return 1;
    }else{
        return 0;
    }
}




int search_exist(Queue *q, Node new_one)
{
    int i,j,k;
    int count=0;
    for(k=0;k<q->back;k++){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(new_one.board[i][j]==q->n[k].board[i][j]){
                    count++;
                }
            }
        }
        if(count==SIZE*SIZE){
            return 1;
        }
        count = 0;
    }

    return 0;

}

int match_target(Node new_one){
    int i,j;
    int count=0;
    int value=49;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){

            if(new_one.board[i][j]== value&&!(i==3&&j==3)){
                count++;
            }
            value++;
        }
    }
    if(count==8){
        return 1;
    }else{
        return 0;
    }

}
void find_parent(Queue *q, Node t)
{
    int i,j;
    if(t.parent==0){
        print_board(t);
        return;
    }

    for(i=q->back-1;i>=0;i--){
        if(t.parent==i+1){
            find_parent(q,q->n[i]);
            print_board(t);
            return;
        }
    }

}

void print_board(Node t)
{
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%c",t.board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}