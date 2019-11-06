#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define LEN 4
int edit_distance(char *s,char *t);
char *one_round(char *s,char *t);
void show(char *s,char *t);
int main(void)
{
	char *s="cold";
	char *t="warm";
	show(s,t);
	return 0;
 } 
 
int edit_distance(char *s,char *t)
{
	int i;;
	int counter=0;
	for(i=0;i<LEN;i++){
		if(s[i]!=t[i]){
			counter++;
		}
	}
	return counter;
 } 
 
 char *one_round(char *s,char *t)
 {
 	FILE *fp;
 	char *word;
	int distance;
	word=(char *)malloc(sizeof(char)*LEN);
 	distance = edit_distance(s,t);
 	fp=fopen("34words.txt","r");
 	if(fp==NULL){
 		printf("Failed to open file\n");
 		exit(1);
	}
	do{
		fscanf(fp,"%s",word);
	}while(edit_distance(s,word)!=1||edit_distance(word,t)!=(distance-1));
	
	return word;
}
 
 void show(char *s,char *t){
 	int distance;
 	char *temp;
 	int i;
	temp=(char *)malloc(sizeof(char)*LEN);
	
	distance=edit_distance(s,t);
	printf("%s\n",s);
	
	temp=one_round(s,t);
	printf("%s\n",temp);

	for(i=0;i<LEN-2;i++){
		temp=one_round(temp,t);
		printf("%s\n",temp);
	}
 	printf("%s\n",t);
 	
 };
 
 
 
 
 
 
 
