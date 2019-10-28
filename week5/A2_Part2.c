#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<assert.h>
#define NUMBER 300
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
	char *p[NUMBER];
	int i,j,n=0,longest=0,flag=0;
	fp = fopen(name,"r");
	if(fp==NULL){
		printf("failed to open file\n");
		exit(1);
	}
	
	for(i=0;i<NUMBER;i++){
		p[i]= (char *)malloc(sizeof(char)*45);
		for(j=0;j<45;j++){
			*(p[i]+j)=EOF;
		}
		fscanf(fp,"%s",p[i]);
		if(isogram(p[i])==1){
			while(p[i][n]!=EOF){
				n++;
			}
			if(n>longest){
				longest=n;
				flag=i;
			}
			n=0;
		}
	}
	printf("%s(%d)\n",p[flag],longest);
}

