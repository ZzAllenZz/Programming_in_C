#include<stdio.h>
#include<malloc.h>
struct Node{
	int data;// ������
	struct Node *next;// ָ���� 
};
// create a linklist,��һ����ͷ����ʾ�������� 
struct Node* createlist(){
	struct Node* headNode = (struct Node*)\
	                        malloc(sizeof(struct Node));
	//�ڶ�̬�������ڴ��, headNode ���һ���ṹ�����
	//Ҫ�Խṹ��������г�ʼ���� 
	headNode->next =NULL;
	return headNode;
} 
//������㣬 
struct Node* createnode(int data){
	struct Node* newNode = (struct Node *)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
// ��ӡ���
void printlist(struct Node* headNode){
	struct Node* pMove = headNode->next;
	while(pMove){
		printf("%d",pMove->data);
		pMove = pMove->next;
	}
} 
//�����㣻
void insertnodebyhead(struct Node* headNode,int data){
	struct Node* newNode = createnode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
	
}
 
int main(void){
	struct Node* head = createlist();
	insertnodebyhead(head,1);
	insertnodebyhead(head,2);
	insertnodebyhead(head,3);
	printlist(head);
	return; 
} 

