#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 5
#define LENGTH 100
#define WIDTH 100
typedef struct node{
    char number[MAXSIZE];
    int depth;
    struct node *left;
    struct node *right;
}Node;

Node *build_tree(char *input);
void store_tree(Node *head,char array[LENGTH][WIDTH],int i,int j);
void find_depth(Node *tree_head);

int main (void){
    char *input  = "1(2(3(4(*)(*))(5(*)(*)))(6(7(*)(*))(8(*)(*))))(9(10(11(*)(*))(12(*)(*)))(13(14(*)(*))(15(*)(*))))";
    Node * head;
    int i;
    int j;
    char array[LENGTH][WIDTH];
    head = build_tree(input);

    find_depth(head);

//    printf("%d\n",head->depth);

    for(i=0;i<LENGTH;i++){
        for(j=0;j<WIDTH;j++){
            array[i][j] = ' ';
        }
    }
    store_tree(head,array,0,0);
    for(i=0;i<LENGTH;i++){
        for(j=0;j<WIDTH;j++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }
    return 0;
}

Node *build_tree(char *input)
{
    Node *head = (Node *)calloc(1,sizeof(Node));
    Node *left;
    Node *right;
    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;
    int mark  = 0;
    char temp;
    if(input[i] == '*'){
        return NULL;
    }

    while(count ==0){
        head->number[MAXSIZE-1-i] = input[i];
        i++;
        if(input[i] == '(' ){
            count =1;
        }
    }
    k = i;
    for(j=0;j<= i/2;j++,k--){
        temp = head->number[MAXSIZE-1-k];
        head->number[MAXSIZE-1-k] = head->number[MAXSIZE-1-j];
        head->number[MAXSIZE-1-j] = temp;
    }

    count = 1;
    i++;
    mark = i;
    while(count != 0){
        if(input[i] == '(' ){
            count = count + 1;
        }
        if(input[i] == ')'){
            count = count -1;
        }
        i++;
    }
    left = build_tree(input+mark);


    count = 1;
    i++;
    mark = i;
    while(count != 0){
        if(input[i] == '(' ){
            i++;
            count = count + 1;
        }
        if(input[i] == ')'){
            i++;
            count = count -1;
        }
        i++;
    }
    right = build_tree(input+mark);

    head->left = left;
    head->right = right;
    return head;
}


void find_depth(Node *tree_head)
{
    static depth = 1;
    if(tree_head == NULL){
        return;
    }
    tree_head->depth = depth;
    depth++;
    find_depth(tree_head->left);
    find_depth(tree_head->right);
    depth--;
}

void store_tree(Node *head,char array[LENGTH][WIDTH],int i,int j)
{
    int k= 0;
    int m = 0;
    if(head ==NULL){
        return;
    }
    for(k=0;k<MAXSIZE;k++){
        array[i][j+k] = head->number[k];
    }
    if(head->left != NULL){
        for(k=1;k<20/head->depth;k++){
            array[i+k][j] = '|';
        }
    }
    if(head->right != NULL){
        for(k=5;k<10;k++){
            array[i][j+k] = '-';
        }
    }

    store_tree(head->left,array,i+20/head->depth,j);
    store_tree(head->right,array,i,j+10);
}