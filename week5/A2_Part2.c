#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<assert.h>
int isogram(char *s);
void find_longest(char *name); 
int main(void){

	find_longest("eng_370k_shuffle.txt");

	return 0;
} 

int isogram(char *s){
	int len = strlen(s);
	int i,j,result=1;
	for(i=0;i<len;i++){
		for(j=i+1;j<len;j++){
			if(*(s+i)==*(s+j)){
				result= 0;
			}
		}
	}
	return result;
}

void find_longest(char *name){
	
	FILE *fp;
	char longest[50];
	char p[50];
	int round=0;
	fp = fopen(name,"r");
	if(fp==NULL){
		printf("failed to open file\n");
		exit(1);
	}
	
	while(fscanf(fp,"%s",p)==1){

		if(isogram(p)==1){
			if(round==0){
				strcpy(longest,p);
			}else{
				if(strlen(p)>strlen(longest)){
					strcpy(longest,p);
				}
			}
			round++;

		}	
	}

	printf("%s(%d)\n",longest,strlen(longest));
}

