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
/*Initialise the first node*/
void initialise_node(Node *t,char *p);
/*Initialise the queue*/
void initialise_queue(Queue *q);
/*Add one more node into queue*/
void insert(Node *t, Queue *q);
/*Move the front */
void move(Queue *q);
/*Check whether the queue has node*/
int is_empty_queue(Queue *q);

/*Used to find ' ' in board */
int is_empty(char c);
/*Search whether the new node is existed in linked queue */
int search_exist(Node *const_ptr, Node new_one);
/*Used to compare new one with target board */
int match_target(Node new_one);
/*a recursion used to print out route*/
void find_parent(Queue q, Node t);
/*Used to print board(2D char array)*/
void print_board(Node t);
/*Used to find and insert the next several boards from one parent*/
void find_next_board(Queue *q,Node *const_ptr);
/*Used to show the core logic and present the solution  */
void show_solution(char *p);
//void test(void);

int main (void)
{
//    test();
    show_solution("513276 48");
    return 0;
}

//void test(void){
//    Queue q;
//    Node t;
//    Node t2;
//    Queue q_copy;
//
//    initialise_node(&t,"513276 48");
//    initialise_queue(&q);
//    q_copy.front=q.front;
//    q_copy.back=q.back;
//    insert(&t,&q);
//
//    initialise_node(&t2,"51327648 ");
//    insert(&t2,&q);
//    Queue q;
//    q.front=(Node *)malloc(sizeof(Node));
//    q.back = (Node *)malloc(sizeof(Node));
//    q.front->next=(Node *)malloc(sizeof(Node));
//    try(q);
//    printf("front = %p\n",q.front);
//    printf("back = %p\n",q.back);
//
//}

void show_solution(char *p)
{
    Queue q;
    Node t;
    Node *const_ptr;
    /*const_ptr points to the first meaningful node,
     * and never changes;
     * const_ptr is used to find out the whole linked list,
     * no matter how the queue is changed;
     * */

    initialise_node(&t,p);
    initialise_queue(&q);
    insert(&t,&q);

    const_ptr = q.front->next;

    while(!match_target(*(q.back))&&!is_empty_queue(&q)){
        find_next_board(&q,const_ptr);

    }

    /*If q is empty, it means cannot find a solution
     * from original board to target board*/
    if(is_empty_queue(&q)){
        printf("Cannot find the solution");
        return;
    }
    /*A recursion used to print out the route */
    find_parent(q,*(q.back));
}

void find_next_board(Queue *q,Node *const_ptr)
{
    int i,j,k,l,m;
    /*y[4] and x[4] are used to up, down, left or right swap*/
    int y[4]={-1,1,0,0};
    int x[4]={0,0,-1,1};
    Node new_node;

    /*Initialise new_node*/
    for(i=0;i<SIZE;i++) {
        for(j=0;j<SIZE;j++) {
            new_node.board[i][j]=q->front->next->board[i][j];
        }
    }

    new_node.parent = NULL;
    new_node.next= NULL;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            /*find out ' ' in board*/
            if(is_empty(q->front->next->board[i][j])){
                for(k=0;k<4;k++){
                    /*Ensure the swap is not out of boundary*/
                    if((i+y[k])<=2 && (i+y[k])>=0 && (j+x[k])<=2 && (j+x[k])>=0){

                        new_node.board[i][j]= q->front->next->board[i+y[k]][j+x[k]];
                        new_node.board[i+y[k]][j+x[k]] = q->front->next->board[i][j];

                        /*Ensure new_node is not existed in queue*/
                        if(!search_exist(const_ptr,new_node)){
                            new_node.parent = q->front->next;
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
                                new_node.board[l][m]=q->front->next->board[l][m];
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

int search_exist(Node *const_ptr, Node new_one)
{
    int i,j;
    int count=0;
    Node *p = const_ptr;
    /* p points to the first meaningful node;
     * it can help to find out the whole linked list;
     * */
    while(p !=NULL){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(new_one.board[i][j]==p->board[i][j]){
                    count++;
                }
            }
        }
        if(count==SIZE*SIZE){
            return 1;
        }
        count = 0;
        p = p->next;
    }
    return 0;

}

void find_parent(Queue q, Node t)
{
    int i;
    if(t.parent==NULL){
        print_board(t);
        return;
    }

    find_parent(q, *(t.parent));
    print_board(t);
    return;


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

void initialise_queue(Queue *q)
{
    /*Both front and back, point to a head node;
     * Head node has no meaning, and just for convenient operation;
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



void insert(Node *t, Queue *q)
{
    int i ,j;
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            temp->board[i][j] = t->board[i][j];
        }
    }
    temp->parent = t->parent;
    temp->next =NULL;

    q->back->next = temp;
    q->back = temp;
}

void move(Queue *q)
{
    if(q->front==q->back){
        return;
    }
    if(q->front->next==q->back){
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
int is_empty(char c)
{
    if(c==' '){
        return 1;
    }else{
        return 0;
    }
}



int match_target(Node new_one)
{
    int i,j;
    int count=0;
    /*int 49 matches char '1'*/
    int value= 49 ;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            /*Only care about first 8 char, no need to care about ' '*/
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

