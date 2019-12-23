#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int number;
    struct node *left;
    struct node *right;
}Node;
Node *build_tree(char *input);
int main (void){
    char *input  = "521(123(350(*)(*))(470(*)(*)))(798(*)(*))";
    Node * head;

    printf("%c\n",input[1]);
    printf("111");
    head = build_tree(input);
    printf("222");
    printf("left: %d , right:%d",head->left->left->number,head->left->right->number);
}

Node *build_tree(char *input)
{
    Node *head = (Node *)calloc(1,sizeof(Node));
    Node *left;
    Node *right;
    int i = 0;
    int count = 0;
    int mark  = 0;
    if(input[i] == '*'){
        return NULL;
    }

    head->number = 0;
    while(count ==0){
        head->number *= 10;
        head->number += input[i]-48;
        i++;
        if(input[i] == '(' ){
            count =1;
        }
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