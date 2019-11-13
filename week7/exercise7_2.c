#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NDEBUG
#include<assert.h>

#define NUMBOARDS 362880
#define SIZE 3
#define TRUE 1
#define FALSE 0

typedef int bool;

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
bool is_empty_queue(Queue *q);
/*Used to find ' ' in board */
bool is_empty(char c);
/*Search whether the new node is existed in queue */
bool search_exist(Queue *q, Node new_one);
/*Used to compare new one with target board */
bool match_target(Node new_one);

/*Used to copy board from origin's node to destination's node*/
void copy_board(Node *destination, Node origin);
/*Used to print board(2D char array)*/
void print_board(Node t);
/*a recursion used to print out route*/
void find_parent(Queue *q, Node t);
/*Used to find and insert the next several boards from one parent*/
void find_next_board(Queue *q);

/*Used to show the core logic and present the solution  */
void show_solution(char *p);
void test();

int main (int argc, char **argv)
{
    if(argc != 2 || strlen(argv[1])!=9 ){
        printf("ERROR: Incorrect usage, try e.g. %s \"513276 48\"\n",argv[0]);
        exit(EXIT_FAILURE);
    }else{
        test();
        show_solution(argv[1]);
    }

    return 0;
}
void test()
{
    static Queue q;
    Node *t;
    t = (Node *)malloc(sizeof(Node));

    initialise_queue(&q);
    assert(is_empty_queue(&q)==1);

    initialise_node(t,"513276 48");
    insert(t,&q);
    
    assert(q.n[0].board[1][1]=='7');
    assert(q.n[0].board[2][2]=='8');
    assert(q.n[0].board[2][0]==' ');

    find_next_board(&q);
    assert(q.n[1].board[1][0]==' ');
    assert(q.n[1].board[2][0]=='2');
    assert(q.n[2].board[2][1]==' ');
    assert(q.n[2].board[2][0]=='4');
    assert(is_empty(q.n[1].board[1][0])==1);
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

    /*jump out loop when find target or have no solution*/
    while(!match_target(q.n[q.back-1])&&!is_empty_queue(&q)){
        find_next_board(&q);
    }

    /*If q is empty, it means cannot find a solution
     * from original board to target board*/
    if(is_empty_queue(&q)){
        printf("Cannot find the solution...\n");
        return;
    }
    /*A recursion used to print out the route */
    find_parent(&q,q.n[q.back-1]);
}

void find_next_board(Queue *q)
{
    int i,j,k;
    /*y[4] and x[4] are used to up, down, left or right swap*/
    int y[4]={-1,1,0,0};
    int x[4]={0,0,-1,1};
    Node new_node;
    /*Initialise new_node*/
    copy_board(&new_node, q->n[q->front]);
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
                        copy_board(&new_node, q->n[q->front]);
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

void copy_board(Node *destination, Node origin)
{
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            destination->board[i][j]= origin.board[i][j];
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
    /*back always 'points' to a void node */
    q->back = q->back+1;
}

void move(Queue *q) {
    q->front=(q->front+1);
}



bool is_empty_queue(Queue *q){
    if(q->front ==q->back){
        return TRUE;
    }else{
        return FALSE;
    }

}
bool is_empty(char c){
    if(c==' '){
        return TRUE;
    }else{
        return FALSE;
    }
}


bool search_exist(Queue *q, Node new_one)
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
            return TRUE;
        }
        count = 0;
    }

    return FALSE;

}

bool match_target(Node new_one){
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
        return TRUE;
    }else{
        return FALSE;
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