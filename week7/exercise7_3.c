/*Note: 
*1.The code is based on 74.c, so it is a BFS Algorithm achieved by Linked-list Queue;
*2.The font filename must be "Mode7.fnt", 
*  otherwise we need to change fname in function:Neill_SDL_ReadFont;
*3.After the SDL Window draw all the pattern, it will close automatically;
*  But you cannot close it during displaying(not suggest to do that!);
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "neillsdl2.h"

#define MILLISECONDDELAY 1000
#define SIZE 3
#define TRUE 1
#define FALSE 0

typedef int bool;

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
bool is_empty_queue(Queue *q);
/*Used to find ' ' in board */
bool is_empty(char c);
/*Search whether the new node is existed in linked queue */
bool search_exist(Node *const_ptr, Node new_one);
/*Used to compare new one with target board */
bool match_target(Node new_one);

/*Used to copy board from origin's node to destination's node*/
void copy_board(Node *destination, Node origin);
/*Used to find and insert the next several boards from one parent*/
void find_next_board(Queue *q,Node *const_ptr);
/*Used to show the core logic and present the solution  */
void show_solution(char *p);
/*The core function to display solution on SDL Window */

void sdl_display(Queue q);
/*Used to draw board on SDL Simple_Window*/
void draw_board(Node t,SDL_Simplewin *sw);
/*a recursion used to draw out route*/
void find_parent(Queue q, Node t, SDL_Simplewin *sw);

int main (int argc, char **argv)
{
    if(argc != 2 || strlen(argv[1])!=9 ){
        printf("ERROR: Incorrect usage, try e.g. %s \"513276 48\"\n",argv[0]);
        exit(EXIT_FAILURE);
    }else{
        show_solution(argv[1]);
    }

    return 0;
}

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
    /*Display route on SDL Window */
    sdl_display(q);
    
}

void sdl_display(Queue q)
{

    SDL_Simplewin sw;

    /*initialise SDL Window*/
    Neill_SDL_Init(&sw);

    /*A recursion used to draw out route*/
    find_parent(q,*(q.back),&sw);
    
    /*After showing the route, we close Window*/
    SDL_Quit();
    atexit(SDL_Quit);
}

void find_parent(Queue q, Node t,SDL_Simplewin *sw)
{

    if(t.parent==NULL){
        draw_board(t,sw);
        return;
    }

    find_parent(q, *(t.parent),sw);
    draw_board(t,sw);
    return;
}

void draw_board(Node t,SDL_Simplewin *sw)
{
    int i,j;
    int ox = WWIDTH/2;
    int oy = WHEIGHT/2;
    fntrow fontdata[FNTCHARS][FNTHEIGHT];
    
    Neill_SDL_ReadFont(fontdata, "mode7.fnt");


    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            Neill_SDL_DrawChar(sw,fontdata,t.board[i][j], ox+j*FNTWIDTH, oy+i*FNTHEIGHT);
        }
        
    }
    Neill_SDL_Events(sw);
    if(sw->finished){
        SDL_Quit();
        atexit(SDL_Quit);
        exit(EXIT_SUCCESS);
    }

    Neill_SDL_UpdateScreen(sw);
    SDL_Delay(MILLISECONDDELAY);
   
}



void find_next_board(Queue *q,Node *const_ptr)
{
    int i,j,k;
    /*y[4] and x[4] are used to up, down, left or right swap*/
    int y[4]={-1,1,0,0};
    int x[4]={0,0,-1,1};
    Node new_node;

    /*Initialise new_node*/
    copy_board(&new_node, *(q->front->next));

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
                        copy_board(&new_node, *(q->front->next));
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

bool search_exist(Node *const_ptr, Node new_one)
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
            return TRUE;
        }
        count = 0;
        p = p->next;
    }
    return FALSE;

}


void copy_board(Node *destination, Node origin){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            destination->board[i][j]= origin.board[i][j];
        }
    }
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

bool is_empty_queue(Queue *q)
{
    if(q->front ==q->back){
        return TRUE;
    }else{
        return FALSE;
    }

}
bool is_empty(char c)
{
    if(c==' '){
        return TRUE;
    }else{
        return FALSE;
    }
}



bool match_target(Node new_one)
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
        return TRUE;
    }else{
        return FALSE;
    }

}
