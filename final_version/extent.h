#include<stdio.h>
#include<stdlib.h>

#define  MAXSIZE 100
#define FAIL 0
#define SUCCESS 1
typedef struct stack{
    char *data[MAXSIZE];
    int top;
} Stack;

Stack* init_stack();
void push_stack(Stack *s,char *data);
void pop_stack(Stack *s,char **data);
int is_empty(Stack *s);

float operation(char ope, float num1,float num2);
int is_operator(char ope);
