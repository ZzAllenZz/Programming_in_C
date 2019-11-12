#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


#define SIZE 3

typedef struct node{
    char board[SIZE][SIZE];
    int parent ;
    struct node *next;
} Node;

typedef struct queue{
    Node *front;
    Node *back;
} Queue;

void initialise_queue(Queue *q);
void initialise_node(Node *t,char *p);
void insert(Node *t, Queue *q)

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
    t->parent =0;
    t->next = NULL;
}

void show_solution(char *p){
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

void insert(Node *t, Queue *q)
{
    q->back->next = t;
    q->back = t;
}

void move(Queue *q) {
    if(q->front==q->back){
        return;
    }
    q->front->next = q->front->next->next;

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


int search_exist(Queue q, Node new_one)
{
    int i,j,k;
    int count=0;
    Node
    while(){
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