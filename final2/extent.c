#include "extent.h"
#define ERROR_1(PHRASE) {\
fprintf(stderr,"Fatal Error: %s occured in %s, line %d\n",\
PHRASE,__FILE__,__LINE__);\
exit(1);\
}
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




int is_operator(char ope)
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
