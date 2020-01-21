 
//  main.m
 
//  �沨�����ʽ
 
//
 
//  Created by ����˳ on 2018/5/10������.
 
//  Copyright ? 2018�� ����. All rights reserved.
 
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
 
// ����ջ
 
void initStack()
 
{
 
    s = (Stack *)malloc(sizeof(Stack));
 
    s->count = 0;
 
    s->data = NULL;
 
}
 
// ��ջ��push
 
void push(double data)
 
{
 
    printf("%f  ��������ջ\n",data);
 
    Node * n = malloc(sizeof(Node));
 
    n->data = data;
 
    n->next = s->data;
 
    
 
    s->data = n;
 
    s->count ++;
 
}
 
// ��ջ��pop
 
double pop()
 
{
 
    
 
    if(s->data == NULL)
 
    {
 
        printf("�Ѿ��ǿ�ջ��\n");
 
        return CGFLOAT_MAX;
 
    }
 
    
 
    Node * n = s->data;
 
    double r = n->data;
 
    printf("���� %f  ������ջ\n",n->data);
 
    s->data=n->next;
 
    free(n);
 
    s->count--;
 
    return  r;
 
}
 
// ���ջ
 
void clearStack()
 
{
 
    
 
    while (s->data != NULL)
 
    {
 
        pop();
 
    }
 
    
 
}
 
// ��ȡջ��Ԫ��
 
double topItem()
 
{
 
    if (s->data==NULL)
 
    {
 
        printf("��ջΪ��ջ\n");
 
        return CGFLOAT_MAX;
 
    }
 
    
 
    printf("��ջ��Ԫ������Ϊ %d ��,ջ��Ϊ %f\n",s->count,s->data->data);
 
    return s->data->data;
 
}
 
// ���ַ���ת��double��û���������⣬�����û����� 12.35.5 5abc.64���ͻ����
 
double charToDouble(char * num)
 
{
 
    
 
    double a = 0.0;
 
    // ��һ���ַ���ת�ɸ��������֣���¼С������λ��������С����ת��������
 
    // Ȼ����������� ����С������λ�������ɵõ�������
 
    int havePoint = 0; //��������Ƿ���С����
 
    int j=0; // ��¼С��������м�λ��
 
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
 
    printf("�ַ���%s ת�� ������  %f\n",num,a);
 
    return a;
 
}
 
int main()
 
{
 
    
 
    initStack();
 
    
 
//    char * str = "3*4/2*3";
 
    
 
    char str[100] ;
 
    printf("����һ�����ʽ\n");
 
//     ����Ҫ����Ӣ�����룬��Ȼ�޷����롣��...
 
    gets(str);
 
    // ��¼�沨�����ʽ�Ľ����
 
    // �ṹ�� ��0��1�� ����Ӧֵ�������ڼӼ��˳� ����char���ͣ�char -> int -> double��������double�洢��
 
    // 0 ��ʾ���������ͣ� 1 ��ʾ������Ƿ������� ,
 
    // 40 = (   41 = )  42 = *  43 = +  45 = -  47 = /
 
    //
 
    double niBoLan[100]={0.0};
 
    int niI = 0; // �沨�����ʽ���±�
 
    
 
    char num[100] = "\0"; // ���ַ�����������ʹ�ã�
 
    int j = 0;//��¼�������char�ĳ��ȣ����� 12.3 �ͻ��¼Ϊ4
 
    
 
    for(int i=0; str[i]!='\0'; )
 
    {
 
        // ���ֳ������ֻ��Ƿ���
 
        if ((str[i]<='9'&&str[i]>='0') || str[i]=='.')
 
        {
 
            // ������ת������
 
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
 
                    pop(); // ��Ҫ�� �� ����
 
                    break;
 
                    
 
            }
 
            
 
            i++;
 
        }
 
        
 
    }
 
    
 
    // ջ��ʣ��ķ��ŵ���
 
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
 
    printf("\n�沨��ת����ϣ����һ��\n");
 
    
 
    clearStack();
 
    
 
    printf("\n���ջ�ṹ����ʼ������\n");
 
    
 
    double num1;
 
    double num2;
 
    for(int i = 0;i<niI;i+=2) {
 
        
 
        // �жϱ�־λ�� 0 �����֣� 1 �Ƿ��š�
 
        int isChar = niBoLan[i];
 
        if(isChar == 0 ) {
 
            // ����ֱ����ջ
 
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
 
    
 
    printf("\n������ %f\n",pop());
 
    
 
}
 
/*
 
 
 */
 
