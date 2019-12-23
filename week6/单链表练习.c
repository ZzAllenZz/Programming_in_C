#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
/*
用户不断输入数字
程序将输入的数字从小到大排序,并且能够删除
体现单链表的优势
*/
struct Node{
	int value;
	struct Node *next;
};
void addNode(struct Node **head,int value);
void deleteNode(struct Node **head,int value); 
void printNode(struct Node *head);
int main(void)
{
	struct Node *head = NULL;
	int input;
	printf("-----this is for insert integer-----\n");
	while(1){
		printf("please enter a integer(-1 for exit):");
		scanf("%d",&input);
		if(input==-1){
			break;
		}
		addNode(&head,input);
		printNode(head);
	}
	printf("-----this is for delete integer-----\n");
	while(1){
		printf("please enter a integer you want to delete(-1 for exit):");
		scanf("%d",&input);
		if(input==-1){
			break;
		}
		deleteNode(&head,input);
		printNode(head);
	}
	return 0; 
} 
void addNode(struct Node **head, int value){
	struct Node *current;
	struct Node *previous;
	struct Node *newOne;

	current = *head;
	previous= NULL;

/*
��current��ָ��null&&current�е�valueС��input��valueʱ�������
ֱ��1.currentָ��null �����һ��Ԫ���ˣ�
or	2.current �е�value����input�е�value�ˡ� 
*/ 
	while(current != NULL&&current->value<value){
		previous = current;
		current = current->next;
	} 
	newOne = (struct Node *)malloc(sizeof(struct Node)); 
	if(newOne == NULL){
		printf("Allocation Failed....\n");
		exit(1);
	}
	newOne->value = value;
	newOne->next=current;
	if(previous == NULL){
		*head = newOne;
	}else {
		previous->next=newOne;

	}

}
void deleteNode(struct Node **head,int value){

	struct Node *current = *head;
	if(current->value==value){
		*head = current->next;
		return;
	}
	while(current->next != NULL && current->next->value!=value){
		current=current->next;
	}
	if(current==NULL||current->next==NULL){
		printf("it cannot be find\n");
		return;
	} else {

		current->next =current->next->next;
		return;
	}
}


void printNode(struct Node *head){
	struct Node *current=head;
	while(current !=NULL){
		printf("%d ",current->value);
		current = current->next;
	}
	putchar('\n');
}
