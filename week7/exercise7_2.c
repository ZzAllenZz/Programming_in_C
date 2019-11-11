#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


#define NUMBOARDS 362880
#define SIZE 3

typedef struct node{
    char board[SIZE][SIZE];
    int parent ;
} Node;

typedef struct queue{
    Node n[NUMBOARDS];
    int front;
    int back;
} Queue;

/*Initialise the first node*/
void initialise_node(Node *t,char *p);
/*Initialise the queue*/
void initialise_queue(Queue *q);
/*Add one more node into queue*/
void insert(Node *t, Queue *q);
/*Move the front */
void move(Queue *q);
/*Check whether the queue is empty*/
int is_empty_queue(Queue *q);

/*Used to find ' ' in board */
int is_empty(char c);
/*Search whether the new node is existed in queue */
int search_exist(Queue *q, Node new_one);
/*Used to compare new one with target board */
int match_target(Node new_one);
/*Used to find and insert the next several boards from one parent*/
void find_next_board(Queue *q);
/*Used to print board(2D char array)*/
void print_board(Node t);
/*a recursion used to print out route*/
void find_parent(Queue *q, Node t);
/*Used to show the core logic and present the solution  */
void show_solution(char *p);
void test();

int main (void)
{
    test();
    show_solution("51327648 ");
    return 0;
}
void test()
{
    static Queue q;
    Node *t;
    t = (Node *)malloc(sizeof(Node));
    initialise_queue(&q);
    initialise_node(t,"513276 48");

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
void show_solution(char *p){
    static Queue q;
    Node t;

    initialise_node(&t,p);
    initialise_queue(&q);
    insert(&t,&q);

    while(!match_target(q.n[q.back-1])&&!is_empty_queue(&q)){
        find_next_board(&q);

    }

    /*If q is empty, it means cannot find a solution
     * from original board to target board*/
    if(is_empty_queue(&q)){
        printf("cannot find the solution");
        return;
    }
    /*A recursion used to print out the route */
    find_parent(&q,q.n[q.back-1]);
}

void find_next_board(Queue *q)
{
    int i,j,k,l,m;
    /*y[4] and x[4] are used to up, down, left or right swap*/
    int y[4]={-1,1,0,0};
    int x[4]={0,0,-1,1};
    Node new_node;
    /*Initialise new_node*/
    for(i=0;i<SIZE;i++) {
        for(j=0;j<SIZE;j++) {
            new_node.board[i][j]=q->n[q->front].board[i][j];
        }
    }
    /*-1 has no meaning*/
    new_node.parent = -1;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(is_empty(q->n[q->front].board[i][j])){
                for(k=0;k<4;k++){
                    /*Ensure the swap is not out of boundary*/
                    if((i+y[k])<=2&&(i+y[k])>=0&&(j+x[k])<=2&&(j+x[k])>=0){

                        new_node.board[i][j]= q->n[q->front].board[i+y[k]][j+x[k]];
                        new_node.board[i+y[k]][j+x[k]] = q->n[q->front].board[i][j];
                        /*Ensure new_node is not existed in queue*/
                        if(!search_exist(q,new_node)){
                            new_node.parent = q->front+1;
                            insert(&new_node,q);
                        }
                        /*If the new_node's board is target board, return;
                         *Note: the target board is also in the queue;
                         * */
                        if(match_target(new_node)){
                            return;
                        }
                        /* re-initialise new_node's board*/
                        for(l=0;l<SIZE;l++) {
                            for(m=0;m<SIZE;m++) {
                                new_node.board[l][m]=q->n[q->front].board[l][m];
                            }
                        }
                    }
                }
                /*Above code achieves that several new boards,
                 * which from one specific parent, insert queue;
                 * Then we move queue's front by 1 to prepare next time find and insertion;
                 * */
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
    q->back = q->back+1;
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
    /*int 49 means char '1'*/
    int value= 49 ;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            /*only care about first 8 char, no need to care about ' '*/
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
    int i;
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