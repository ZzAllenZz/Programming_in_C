#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<malloc.h>
#define NUMBER 3
#define DIFFERENCE 48
//int *matching_number(char *name);
//char *generate_result(char *name,int *number);
int *matching_number(char *name_0);
char *generate_result(char *name_0,int *number);
int main(void)
{
    int i,len,*number;
    char* name ="jackson",*result;
    printf("the name is %s\n",name);
    
    
    number = (int *)malloc(sizeof(int)*strlen(name));
    result = (char *)malloc(sizeof(char)*strlen(name));
    
    len = strlen(name);
    printf("the len is %d\n",len);
    number = matching_number(name);
    for(i=0;i<9;i++){
    	printf("the number [%d]is %d\n",i,number[i]);
	}
	result = (char *)malloc(sizeof(char)*strlen(name));
	result = generate_result(name,number);
	printf("the name is %s\n",result);
    

    
    
    
//    number = (int *)malloc(sizeof(int)*strlen(name)-1);
//    result = (char *)malloc(sizeof(char)*strlen(name));
//    
//    number = matching_number(name);
//    printf("the number is %d\n",number[1]);
//    result = generate_result(name,number);
//    printf("the result is %s\n",result);
//    printf("the soundex coding of %s is %s\n",name,result);

    return 0;
}

int *matching_number(char *name_0)
{
	int *number = (int *)malloc(sizeof(int)*strlen(name_0)),i;
	char *name = (char *)malloc(sizeof(char)*strlen(name_0));
	for(i=0;i<strlen(name_0);i++){
    name[i]= tolower(name_0[i]);

		if(name[i]=='b'||
		   name[i]=='f'||
		   name[i]=='p'||
		   name[i]=='v'
		){
			number[i]=1;
		}else if(
		   name[i]=='c'||
		   name[i]=='g'||
		   name[i]=='j'||
		   name[i]=='k'||
		   name[i]=='q'||
		   name[i]=='s'||
		   name[i]=='x'||
		   name[i]=='z'
		){
			number[i]=2;
		}else if(
		   name[i]=='d'||
		   name[i]=='t'
		){
			number[i]=3;
		}else if(
		   name[i]=='l'
		){
			number[i]=4;
		}else if(
		   name[i]=='m'||
		   name[i]=='n'
		){
			number[i]=5;
		}else if(
		   name[i]=='r'
		){
			number[i]=6;
		}else if(
			name[i]=='h'||
		   name[i]=='w'
		){
			number[i] = 7;
		}else{
			number[i] = 0;
		}
	}
	return number;
}
char *generate_result(char *name_0, int *number)
{
	int i,j;
	char *result = (char *)malloc(sizeof(char)*NUMBER+1);

	for(i=0,j=0;j<NUMBER+1;i++){
		if(number[i]==0 ||number[i]==7){
			if(i==0){
				result[j]=number[i]+1;
				j++;
			}
		}else if(number[i+1]==7 && number[i+2]==number[i]){
			result[j]=number[i]+DIFFERENCE;
			j++;
			i = i+2;
		}else if(number[i+1]==7 && number[i+2]!=number[i]){
			result[j]=number[i]+DIFFERENCE;
			j++;
			i = i+1;
		}else if(number[i]==number[i+1]){
			i = i+1;
		}else if(
			number[i]==1||
			number[i]==2||
			number[i]==3||
			number[i]==4||
			number[i]==5||
			number[i]==6
		){
			result[j]=number[i]+DIFFERENCE;
			j++;
		}else{
			result[j]=0+DIFFERENCE;
			j++;
		}
	}
	result[0]=toupper(name_0[0]);
	return result;
}
