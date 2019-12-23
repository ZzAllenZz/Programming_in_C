#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#include<assert.h>

#define NUMBER 370120
#define WIDTH 46 
int anagram(char s1[],char s2[]);
char **readin();
void show(char *name);
int main(void){
	show("sternaig");

	
} 

char **readin()
{
	FILE *fp;
	char **p;
	int i;
	fp=fopen("eng_370k_shuffle.txt","r");
	if(fp==NULL){
		printf("error");
		exit(1);
	}
	p = (char **)malloc(sizeof(char *)*NUMBER);
	for(i=0;i<NUMBER;i++){
		*(p+i)= (char *)malloc(sizeof(char)*WIDTH);
		fscanf(fp,"%s",*(p+i));
	}
	
	return p;
}

void show(char *name){
	char **p;
	int i;
	int len1;
	p=readin();
	for(i=0;i<NUMBER;i++){
		if(anagram(*(p+i),name)==1){
			printf("%s\n",*(p+i));
		}
	}


}

int anagram(char s1[],char s2[]){
	int len1,len2;
	int *p;
	int i,j,count=0;
	len1=strlen(s1);
	len2=strlen(s2);
	p=(int *)malloc(sizeof(int)*len2);
	
	if(len1!=len2){
		return 0;
	}
	if(strcmp(s1,s2)==0){
		return 0;
	}
	for(i=0;i<len2;i++){
		*(p+i) =0;
	}
	for(i=0;i<len1;i++){
		for(j=0;j<len2;j++){
			if((s1[i]==s2[j])&&(p[j]!=1)){
				count++;
				p[j]=1;
			}
		}
	}
	if(count==len1){
		return 1;
	}
	
	return 0;




}
