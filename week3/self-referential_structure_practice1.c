#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
struct llist {
	char word[50];
	struct llist *next;
};


int main(void){
	int j,cnt =0;
	struct llist head ={"",NULL},*cp;
	printf("enter a list of words.\n");
	cp= &head;
	do{

		j = scanf("%s",cp->word);
		cp->next = (struct llist *)malloc(sizeof(struct llist));
		cp = cp->next;
		cp->next = NULL;
		strcpy(cp->word,"");
		cnt++;
	}while(cnt!=5);
	printf("%d words:\n",cnt);
	cp = &head;
	while(strcmp(cp->word,"")){
		printf("%s\n",cp->word);
		cp = cp->next;
	}
	return 0;
} 
