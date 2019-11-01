#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    	char *word;
    	struct node *next;
}Node;

int compare(char *a,char *b);
int countdiff(char *a,char *b);
void wordladders(char *start,char *end,Node *head,int lenth);
int notin(char *temp, Node *head);
Node *create(char *start, char *end);
Node *insert(Node *head,char *word);
Node *del(Node *head,char *word);
void printlink(Node *head);
int linkcompare(Node *head);

int main(int argv,char **argc)
{
	char *start="cat",*end="dog";
	
    int diff=countdiff(start,end);
    
    Node *head=create(start,end);
    
	wordladders(start,end,head,diff);


    return 0;
}

Node *create(char *start, char *end)
{
    	Node *head=(Node *)malloc(sizeof(Node));
    	Node *p=(Node *)malloc(sizeof(Node));
    	head->word=(char *)malloc(sizeof(char)*strlen(start));
    	head->word=start;
    	p->word=(char *)malloc(sizeof(char)*strlen(end));
    	p->word=end;
    	head->next=p;
    	p->next=NULL;
    	return head;
}

Node *insert(Node *head,char *word)
{
    	Node *p,*current=head;
    	Node *new=(Node *)malloc(sizeof(Node));
    	new->word=(char *)malloc(sizeof(char)*strlen(word));
    	while (current->next->next!=NULL)
    	{
        	current=current->next;
    	}
    	p=current->next;
    	new->word=word;
    	current->next=new;
    	new->next=p;
    	return head;
}

Node *del(Node *head,char *word)
{
    	Node *p=head,*current=head;
    	while (strcmp(p->word,word))
    	{
        	current=p;
        	p=p->next;
    	}
    	current->next=p->next;
    	free(p);
    	return head;
}

void printlink(Node *head)
{
    	int i;
    	Node *p=head;
    	do
    	{
        	for(i=0;i<strlen(p->word);i++)
        	{
            		printf("%c",p->word[i]);
        	}
        	if(p->next!=NULL)
        	{
            		printf(" -> ");
        	}
        	p=p->next;
    	}while (p!=NULL);
    	printf("\n");
}

int countdiff(char *a,char *b)
{
    	int i,diff=1;
    	for(i=0;i<strlen(a);i++)
    	{
        	if(*(a+i)!=*(b+i))
        	{
            		diff++;
        	}
    	}
    	return diff;
}

void wordladders(char *start,char *end,Node *head,int lenth)
{
    	FILE *fp=fopen("34words.txt","r");
    	char *temp=(char *)malloc(sizeof(char)*strlen(start));
    	if(linkcompare(head))//����string֮���diff������1ʱ 
    	{
        	printlink(head);
    	}
    	while(!(feof(fp))&&lenth>1) //������string��diff>=2; 
    	{
    		fscanf(fp,"%s",temp);
        	if(compare(start,temp) && notin(temp,head)&&lenth>2)//��start��temp��diff==1����temp���������ﲢ��start��end��diffҪ>=3; 
        	{
            		head=insert(head,temp);
            		wordladders(temp,end,head,lenth-1);
            		head=del(head,temp);
        	}
        	
    	}
    	fclose(fp);
}

int linkcompare(Node *head) //�����������ǺϷ��ģ�����1�������������ǲ��Ϸ��ģ�����0�� 
{
    	Node *p=head;
    	int diff=0;
    	if(p->next->next==NULL)//���������ֻ������Ԫ�أ��ǿ϶��ǲ��Ϸ��ģ������塣 
    	{
        	return 0;
    	}
    	while(p->next!=NULL)
    	{
        	if(!compare(p->word,p->next->word))//�Ƚ�p->word��p->next->word�����diff����1���Ǹ�Ҫ����0�� 
        	{
            		return 0;
        	}
        	p=p->next;
    	}
    	return 1;
}

int compare(char *a,char *b) //diff==1ʱ����1�������������0�� 
{
    	int i,diff=0;
    	if(strlen(a)!=strlen(b))
    	{
        	return 0;
    	}
    	for(i=0;i<strlen(a);i++)
    	{
        	if(*(a+i)!=*(b+i))
        	{
            		diff++;
            		if(diff>1)
            		{
                		return 0;
            		}
        	}
    	}
    	return (diff==1)?1:0;
}

int notin(char *temp, Node *head)//�Ƚ�temp�Ƿ��������г��ֹ���������ֹ���return 0��û���ֹ���return 1 �� 
{
    	Node *p=head;
    	while (p!=NULL)
    	{
        	if(!strcmp(p->word,temp))
        	{
            		return 0;
        	}
        	p=p->next;
    	}
    	return 1;
}
