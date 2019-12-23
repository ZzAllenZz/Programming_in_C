#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define SIZE 50
struct Node{
	char word[SIZE];
	struct Node *next;
};

struct Node *create_list();
void add_node(struct Node **head,char word[SIZE]);
void print_list(struct Node *head);
int main(void){
	struct Node *head = NULL;
	clock_t start, finish;
	double duration;
	start = clock();
	
	head = create_list();
	print_list(head);
	
	finish = clock();
	duration = (finish - start)/CLOCKS_PER_SEC;
	
	printf("the running duration is %lf\n",duration); 
	
	return 0;
	
}

struct Node *create_list(){
	struct Node *head =NULL;
	FILE *fp;
	char word[SIZE];
	fp=fopen("34words.txt","r");
	if(fp==NULL){
		printf("failed to open file!\n");
		exit(1);
	}
	while(fscanf(fp,"%s",word)==1){
		add_node(&head,word);

	}
	
	return head;
}

void add_node(struct Node **head,char word[SIZE]){
	struct Node *current;
	struct Node *previous;
	struct Node *newOne;
	current = *head;
	previous =NULL;
	newOne = (struct Node*)malloc(sizeof(struct Node));
	if(newOne ==NULL){
		printf("failed to allocate!\n");
		exit(1); 
	}
	while(current !=NULL&&strcmp(word,current->word)>0){
		previous = current;
		current = current->next;
	}
	strcpy(newOne->word,word);
	newOne->next = current;
	if(previous==NULL){
		*head = newOne;
	}else{
		previous->next = newOne;
	}
}

void print_list(struct Node *head){
	struct Node *current;
	current = head;
	while(current!=NULL){
		printf("%s\n",current->word);
		current= current->next;
	}
}

