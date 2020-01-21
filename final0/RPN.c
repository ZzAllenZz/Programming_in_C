#include<stdio.h>
#include<stdlib.h>
#include "nal.h"
#define  MAXSIZE 100
#define FAIL 0
#define SUCCESS 1
typedef struct stack{
    char *data[MAXSIZE];
    int top;
} Stack;


float operation(char ope, float num1,float num2);
int is_operation(char ope);

Stack* init_stack()
{
    Stack *s;
    s = (Stack *)malloc(sizeof(struct stack));
    if(s==NULL){
        ERROR_1("Cannot allocate memory");
    }
    s->top = 0;
    return s;
}

void push_stack(Stack *s,char *data)
{

    if (s->top >= MAXSIZE )
    {
        ERROR_1("Stack size is out of bound");
    }
    s->data[s->top++] = data;

}

void pop_stack(Stack *s,char **data)
{

    if (s->top == 0)
    {
        ERROR_1("Empty stack cannot be popped");
    }

    *data = s->data[--(s->top)];
}


int is_empty(Stack *s)
{
    return (s->top == 0);
}


void compute(Program *p, int start, int finish)
{
    int i;
    Stack *s;
    char *str1, *str2;
    float num1,num2,num3;
    char *str3[MAXSIZE];
    for(i=0;i<MAXSIZE;i++){
        str3[i] = calloc(DEFAULTSIZE*TWO,sizeof(char));
    }
    s = init_stack();
    for(i=start;i<=finish;i++){
        if(is_operation(p->array[i][FIRST])){
            pop_stack(s,&str1);
            pop_stack(s,&str2);
            num1 = atof(str1);
            num2 = atof(str2);
            num3 = operation(p->array[i][FIRST],num1,num2);
            sprintf(str3[s->top],"%f",num3);
            push_stack(s,str3[s->top]);
        }else if (p->array[i][FIRST] == '%'){
            str1 = mvm_search(p->map,p->array[i]);
            push_stack(s,str1);
        }else{
            push_stack(s,p->array[i]);
        }
    }
    insert_map(p,s->data[s->top-OFFSET]);
    free(s);
    for(i=0;i<MAXSIZE;i++){
        free(str3[i]);
    }
}



int is_operation(char ope)
{
    if(ope == '+' || ope == '-'||ope =='*'|| ope == '/'){
        return 1;
    }
    return 0;
}

float operation(char ope, float num1,float num2)
{
    float num3;
    switch(ope){
        case '+':   num3 = num1 + num2; break;
        case '-':   num3 = num2 - num1; break;
        case '*':   num3 = num1 * num2; break;
        case '/':   num3 = num2 / num1; break;
    }
    return num3;
}
