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
	for(j=0;j<5;j++){
		scanf("%s\n\n",cp->word);
		cp->next = (struct llist *)malloc(sizeof(struct llist));
		cp = cp->next;
		cp->next = NULL;
		strcpy(cp->word,"");
		cnt++;
	}
	printf("%d words:\n",cnt-1);
	cp = &head;
	while(strcmp(cp->word,"")){
		printf("%s\n",cp->word);
		cp = cp->next;
	}
	return 0;
} 
