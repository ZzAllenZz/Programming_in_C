#include<stdio.h>
#include<malloc.h>
struct Node{
	int data;// 数据域
	struct Node *next;// 指针域 
};
// create a linklist,用一个表头来表示整个链表 
struct Node* createlist(){
	struct Node* headNode = (struct Node*)\
	                        malloc(sizeof(struct Node));
	//在动态分配完内存后, headNode 变成一个结构体变量
	//要对结构体变量进行初始化； 
	headNode->next =NULL;
	return headNode;
} 
//创建结点， 
struct Node* createnode(int data){
	struct Node* newNode = (struct Node *)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
// 打印结点
void printlist(struct Node* headNode){
	struct Node* pMove = headNode->next;
	while(pMove){
		printf("%d",pMove->data);
		pMove = pMove->next;
	}
} 
//插入结点；
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

