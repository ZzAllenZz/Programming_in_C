#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


#define SIZE 3

typedef struct node{
    char board[SIZE][SIZE];
    struct node *parent ;
    struct node *next;
} Node;

typedef struct queue{
    Node *front;
    Node *back;
} Queue;

void initialise_queue(Queue *q);
void initialise_node(Node *t,char *p);
void insert(Node *t, Queue *q);
void move(Queue *q);
int is_empty_queue(Queue *q);
int is_empty(char c);
void show_solution(char *p);
void find_next_board(Queue *q);
int search_exist(Queue q, Node new_one);
int match_target(Node new_one);
void find_parent(Queue q, Node t);
void print_board(Node t);

int main (void)
{
    test();
    show_solution("51327648 ");
    return 0;
}


void initialise_queue(Queue *q)
{
    /*front and back point to head node;
     * head node has no meaning, but just for convenient operation;
     */
    q->front = q->back = (Node *)malloc(sizeof(Node));
    if(!q->front){
        printf("Failed to allocation...\n");
        exit(EXIT_FAILURE);
    }
    q->front->next = NULL;
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
    t->parent =NULL;
    t->next = NULL;
}

void show_solution(char *p)
{
    Queue q;
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
            new_node.board[i][j]=q->front->board[i][j];
        }
    }
    /*-1 has no meaning*/
    new_node.parent = -1;
    new_node.next= NULL;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(is_empty(q->front->board[i][j])){
                for(k=0;k<4;k++){
                    /*Ensure the swap is not out of boundary*/
                    if((i+y[k])<=2&&(i+y[k])>=0&&(j+x[k])<=2&&(j+x[k])>=0){

                        new_node.board[i][j]= q->front->board[i+y[k]][j+x[k]];
                        new_node.board[i+y[k]][j+x[k]] = q->front->board[i][j];
                        /*Ensure new_node is not existed in queue*/
                        if(!search_exist(*q,new_node)){
                            new_node.parent = q->front;
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

void insert(Node *t, Queue *q)
{
    q->back->next = t;
    q->back = t;
}

void move(Queue *q)
{
    if(q->front==q->back){
        return;
    }
    if(q->front->next->next ==NULL){
        q->front->next = NULL;
        q->back = q->front;
    }else{
        q->front->next = q->front->next->next;
    }


}

int is_empty_queue(Queue *q)
{
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


int search_exist(Queue q, Node new_one)
{
    int i,j,k;
    int count=0;

    while(q.front->next !=NULL){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(new_one.board[i][j]==q.front->next->board[i][j]){
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

int match_target(Node new_one)
{
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

void find_parent(Queue q, Node t)
{
    int i;
    if(t.parent==0){
        print_board(t);
        return;
    }
    wihle(q.front !=NULL){
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