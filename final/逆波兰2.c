/* sqstack.h*/
#ifndef SQSTACK_H_
#define SQSTACK_H_

#define MAXSIZE 32
//ջ�ṹ��
typedef struct
{
    int data[MAXSIZE];

    int top;
}sqstack;

sqstack *sqstack_create();  //����ջ
int sqstack_push(sqstack *, int ); //��ջ
int sqstack_pop(sqstack *, int *); //��ջ
int sqstack_top(sqstack *, int *); //�鿴ջ��ֵ
int sqstack_is_empty(sqstack *); //�ж�ջ�Ƿ�Ϊ��
void sqstack_display(sqstack *); //��ʾջ���ݣ������õ�

#endif

/* sqstack.c */
#include <stdio.h>
#include <stdlib.h>



/* ����ջ */
sqstack *sqstack_create()
{
    sqstack *L;

    L = (sqstack *)malloc(sizeof(*L));

    L->top = -1;

    return L;
}

/* ��ջ */
int sqstack_push(sqstack *L,int x)
{
    //�����ջ����ջ�ռ�
    if (L->top == MAXSIZE - 1)
    {
    return -1;
    }
    //ѹջ
    L->data[++L->top] = x;
    return 0;
}

/* ��ջ */
int sqstack_pop(sqstack *L,int *x)
{
    //�����ջ����ջ�ռ�
    if (L->top == -1)
    {
    return -1;
    }
    //���ô�����������ջ��Ԫ��
    *x = L->data[L->top--];
    return 0;
}

/* ���ջ��ֵ */
int sqstack_top(sqstack *L,int *x)
{
    if (L->top == -1)
    {
    return -1;
    }

    *x = L->data[L->top];
    return 0;
}
/* �ж�ջ�Ƿ�Ϊ�� */
int sqstack_is_empty(sqstack *L)
{
    return (L->top == -1);
}

/* ��ӡ���ջ��Ԫ�� */
void sqstack_display(sqstack *L)
{
    int i;
    if (L->top == -1)
    {
    return ;
    }

    for (i = 0 ; i <= L->top; i++)
    {
    printf("%d ",L->data[i]);
    }
    printf("\n");
}
/******************************************************
  ��     ��: 2015.4.7
  ��     ��: ��������ʵ��:ʵ�ּӡ������ˡ�������������
  ��     ��: siriuszxn(��Ϫ�)
*******************************************************/

#include <stdio.h>

#define  MAX 255

//���ȼ��жϺ���
int get_pri(int ope)
{
    switch(ope)
    {
    case '(':   return 0;
    case '+':
    case '-':   return 1;
    case '*':
    case '/':   return 2;
    default :   return -1;
    }
}

/* ����������ջ������ope���ż��㣬Ȼ���ٴ���ջ */
void compute(sqstack *snum,int ope)
{
    int n,n1,n2;
    //���λ����ֵջ��ջ��������
    sqstack_pop(snum,&n1);
    sqstack_pop(snum,&n2);
    //����
    switch(ope)
    {
        case '+':   n = n1 + n2; break;
        case '-':   n = n2 - n1; break;
        case '*':   n = n1 * n2; break;
        case '/':   n = n2 / n1; break;
    }
    //��������ٴ���ջ
    sqstack_push(snum,n);
}
/* ֻ�з��ŲŻ����ú��� */
void deal_ope(sqstack *snum,sqstack *sope,int ope)
{
    int old_ope;
    //���sope����ջ�ǿ�ջ���߷���Ϊ��(��
    if (sqstack_is_empty(sope) || ope == '(')
    {
        //������(��ջ
        sqstack_push(sope,ope);
        return ;
    }
    //��õ�ǰ�ķ���ջ��ջ��
    sqstack_top(sope,&old_ope);

    //����ǰ�ķ���ջ��ջ�������봫��ķ��Ž������ȼ��Ƚ�
    if (get_pri(ope) > get_pri(old_ope))
    {   
        //������Ŵ��ڵ�ǰջ�����򽫴��������ջ
        sqstack_push(sope,ope);
        return ;    
    }
    //�������ķ������ȼ�С�ڵ�ǰջ������
    while (get_pri(ope) <= get_pri(old_ope))
    {
        //����ǰջ���ķ���ȡ��������ջ�ж��˵��������ֽ��м���
        sqstack_pop(sope,&old_ope);
        compute(snum,old_ope);
        //����������֮�����ջΪ����break;
        if (sqstack_is_empty(sope))
        {
            break;
        }
        //�ٴ�ȡ��һ����ǰջ�����봫����űȽ�
        sqstack_top(sope,&old_ope);
    }
    //����������ȼ�����֮���ٽ��´���ķ�����ջ
    sqstack_push(sope,ope);
}
/*�����⵽����ʱ')',��ִ�иú���������Ϊ����ջ�ͷ���ջ*/
void deal_bracket(sqstack *snum,sqstack *sope)
{
    int old_ope;
    //��õ�ǰ�ķ���ջ��ջ������
    sqstack_top(sope,&old_ope);
    //ֱ���ҵ�Ԥ����Ե������š���Ϊ��ȷ����ʽ����������һ������Ե�
    while (old_ope != '(')
    {
        //��ǰ���ų�ջȻ�����ֳ�ջ�������м���,�����������ȼ���ߣ�
        sqstack_pop(sope,&old_ope);
        compute(snum,old_ope);
        //Ȼ���ٴ�ȡ����ǰ����ջջ�����ţ��������֡�(��
        sqstack_top(sope,&old_ope);
    }
    //��󽫳��ֵ������ų�ջ����
    sqstack_pop(sope,&old_ope);
}


int main()
{
    /*strΪ���ʽ����*/
    char str[MAX];
    printf("��������Ҫ����ı��ʽ:\n");
    gets(str);

    int i = 0;
    int value = 0;   //���ֵ�ֵ
    int flag = 0;    
    int old_ope;

    sqstack *snum,*sope;      // ��������ָ��ջ�ṹ���ָ��

    snum = sqstack_create();  // ����������ֵ�ջ

    sope = sqstack_create();  // �������������ŵ�ջ

    /* ���ʽ�ַ�����������,Ȼ�󽫸����ȼ��ķ���/(*)���м���������ջ
       �˳�while��ҵ����ȼ���һ��+-*/
    while (str[i] != '\0')
    {
        //��ȡ���������
        if (str[i] >= '0' && str[i] <= '9')//num
        {
            value = value * 10 + str[i] - '0';
            flag = 1;
        }
        else//ope
        {
            if (flag)
            {
                //flag = 1˵��value����洢�����֣�������ջ
                sqstack_push (snum, value);
                //num��־���㣬value������ֵı�������
                flag = 0;
                value = 0;
            }
            if(str[i] == ')')
            {
                //����������ţ���
                deal_bracket(snum,sope);
            }
            else//+-*/(����� 
            {
                deal_ope(snum,sope,str[i]);
            }   
        }   
        i++;
    }
    //���flag = 1.˵��value���滹����ֵ,������ջ 
    if (flag)
    {
        sqstack_push(snum,value);
    }
    //Ȼ�󽫷������������γ�ջ���㡣���ֳ�ջ�������֮����ٴ���compute����ջ
    while (!sqstack_is_empty(sope))
    {
        sqstack_pop(sope,&old_ope);
        compute(snum,old_ope);
    }
    //ȡ������ջ���ʣ�µ����֣��������Ĵ�
    sqstack_pop(snum,&value);
    //��ӡ���
    printf("%s = %d\n",str,value);

    return 0;
}


