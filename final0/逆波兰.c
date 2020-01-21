 
//  main.m
 
//  逆波兰表达式
 
//
 
//  Created by 郭朝顺 on 2018/5/10星期四.
 
//  Copyright ? 2018年 乐乐. All rights reserved.
 
//
 
#import <Foundation/Foundation.h>
 
#include <stdio.h>
 
#include <stdlib.h>
 
typedef struct Node
 
{
 
    double data;
 
    struct Stack * next;
 
} Node;
 
typedef struct Stack
 
{
 
    Node * data;
 
    int count;
 
} Stack;
 
Stack * s ;
 
// 生成栈
 
void initStack()
 
{
 
    s = (Stack *)malloc(sizeof(Stack));
 
    s->count = 0;
 
    s->data = NULL;
 
}
 
// 入栈，push
 
void push(double data)
 
{
 
    printf("%f  即将被入栈\n",data);
 
    Node * n = malloc(sizeof(Node));
 
    n->data = data;
 
    n->next = s->data;
 
    
 
    s->data = n;
 
    s->count ++;
 
}
 
// 出栈，pop
 
double pop()
 
{
 
    
 
    if(s->data == NULL)
 
    {
 
        printf("已经是空栈了\n");
 
        return CGFLOAT_MAX;
 
    }
 
    
 
    Node * n = s->data;
 
    double r = n->data;
 
    printf("数据 %f  即将出栈\n",n->data);
 
    s->data=n->next;
 
    free(n);
 
    s->count--;
 
    return  r;
 
}
 
// 清空栈
 
void clearStack()
 
{
 
    
 
    while (s->data != NULL)
 
    {
 
        pop();
 
    }
 
    
 
}
 
// 获取栈顶元素
 
double topItem()
 
{
 
    if (s->data==NULL)
 
    {
 
        printf("此栈为空栈\n");
 
        return CGFLOAT_MAX;
 
    }
 
    
 
    printf("此栈中元素数量为 %d 个,栈顶为 %f\n",s->count,s->data->data);
 
    return s->data->data;
 
}
 
// 把字符串转成double，没有做错误检测，比如用户输入 12.35.5 5abc.64，就会出错。
 
double charToDouble(char * num)
 
{
 
    
 
    double a = 0.0;
 
    // 把一个字符串转成浮点型数字，记录小数点后的位数，忽略小数点转成整数，
 
    // 然后用这个整数 除以小数点后的位数，即可得到浮点数
 
    int havePoint = 0; //这个数中是否有小数点
 
    int j=0; // 记录小数点后面有几位的
 
    for(int i=0; num[i]!='\0'; i++)
 
    {
 
        
 
        if(num[i]=='.')
 
        {
 
            havePoint = 1;
 
            continue;
 
        }
 
        if(havePoint==1)
 
        {
 
            j++;
 
        }
 
        
 
        a = a * 10 + num[i] - '0';
 
        
 
    }
 
    while(j>0)
 
    {
 
        a = a/10;
 
        j--;
 
    }
 
    printf("字符串%s 转成 浮点数  %f\n",num,a);
 
    return a;
 
}
 
int main()
 
{
 
    
 
    initStack();
 
    
 
//    char * str = "3*4/2*3";
 
    
 
    char str[100] ;
 
    printf("输入一串表达式\n");
 
//     键盘要换成英文输入，不然无法输入。哭...
 
    gets(str);
 
    // 记录逆波兰表达式的结果，
 
    // 结构是 【0或1】 【对应值】，由于加减乘除 都是char类型，char -> int -> double，所以用double存储。
 
    // 0 表示是数字类型， 1 表示后面的是符号类型 ,
 
    // 40 = (   41 = )  42 = *  43 = +  45 = -  47 = /
 
    //
 
    double niBoLan[100]={0.0};
 
    int niI = 0; // 逆波兰表达式的下标
 
    
 
    char num[100] = "\0"; // 把字符串导出数字使用，
 
    int j = 0;//记录这个数字char的长度，比如 12.3 就会记录为4
 
    
 
    for(int i=0; str[i]!='\0'; )
 
    {
 
        // 区分出是数字还是符号
 
        if ((str[i]<='9'&&str[i]>='0') || str[i]=='.')
 
        {
 
            // 把数字转换出来
 
            while ((str[i]<='9'&&str[i]>='0') || str[i]=='.')
 
            {
 
                char a = str[i];
 
                num[j]=a;
 
                j++;
 
                num[j]='\0';
 
                i++;
 
            }
 
            double b = charToDouble(num);
 
            num[99] ="\0";
 
            j=0;
 
            niBoLan[niI] = 0;
 
            niI ++;
 
            niBoLan[niI] = b;
 
            niI ++;
 
        } else {
 
            char a = str[i];
 
            
 
            switch (a) {
 
                case '+':
 
                case '-':
 
                    while(topItem()=='*'||topItem()=='/'||topItem()=='+'||topItem()=='-'){
 
                        niBoLan[niI] = 1;
 
                        niI ++;
 
                        niBoLan[niI] = pop();
 
                        niI++;
 
                    }
 
                    push(a);
 
                    break;
 
                    
 
                case '*':
 
                case '/':
 
                    while(topItem()=='*'||topItem()=='/'){
 
                        niBoLan[niI] = 1;
 
                        niI ++;
 
                        niBoLan[niI] = pop();
 
                        niI++;
 
                    }
 
                    push(a);
 
                    break;
 
                    
 
                case '(':
 
                    push(a);
 
                    break;
 
                    
 
                case ')':
 
                    
 
                    while(topItem()!='('){
 
                        niBoLan[niI] = 1;
 
                        niI ++;
 
                        niBoLan[niI] = pop();
 
                        niI++;
 
                    }
 
                    pop(); // 需要把 （ 弹出
 
                    break;
 
                    
 
            }
 
            
 
            i++;
 
        }
 
        
 
    }
 
    
 
    // 栈中剩余的符号弹出
 
    while (s->data != NULL)
 
    {
 
        niBoLan[niI] = 1;
 
        niI ++;
 
        niBoLan[niI] = pop();
 
        niI++;
 
    }
 
    
 
    for(int i = 0;i<niI;i++) {
 
        printf("%f  ",niBoLan[i]);
 
    }
 
    printf("\n逆波兰转换完毕，检查一下\n");
 
    
 
    clearStack();
 
    
 
    printf("\n清空栈结构，开始计算结果\n");
 
    
 
    double num1;
 
    double num2;
 
    for(int i = 0;i<niI;i+=2) {
 
        
 
        // 判断标志位， 0 是数字， 1 是符号。
 
        int isChar = niBoLan[i];
 
        if(isChar == 0 ) {
 
            // 数字直接入栈
 
            push(niBoLan[i+1]);
 
            
 
        } else {
 
            
 
            char a = niBoLan[i+1];
 
            switch  (a) {
 
                    
 
                case '+':
 
                    push( pop() + pop() );
 
                    break;
 
                    
 
                case '-':
 
                    num1 = pop();
 
                    num2 = pop();
 
                    push( num2 - num1 );
 
                    
 
                    break;
 
                    
 
                case '*':
 
                    push( pop() * pop() );
 
                    
 
                    break;
 
                    
 
                case '/':
 
                    num1 = pop();
 
                    num2 = pop();
 
                    push( num2 / num1 );
 
                    break;
 
                    
 
            }
 
        }
 
        
 
    }
 
    
 
    printf("\n计算结果 %f\n",pop());
 
    
 
}
 
/*
 
 
 */
 
