#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#define NUMBER 3
int *matching_number(char *name);
char *generate_result(char *name,int *number);
int main(void)
{
    int i,len;
	int *number;
    char *result,*name ="WashingtoN";
    len = strlen(name);
    printf("the len is %d",len);

    printf("the name is %s\n",name);
    number = (int *)malloc(sizeof(int)*strlen(name)-1);
    result = (char *)malloc(sizeof(char)*strlen(name));
    
    number = matching_number(name);
        for(i=0;i<5;i++){
    	printf("the number [%d]is %d\n",i,number[i]);
	}
    printf("the number is %d\n",number[1]);
    result = generate_result(name,number);
    printf("the result is %s\n",result);
    printf("the soundex coding of %s is %s\n",name,result);

    return 0;
}

int *matching_number(char *name)
{
	int *number = (int *)malloc(sizeof(int)*strlen(name)-1),i;
	for(i=1;i<strlen(name);i++){
		name[i]= tolower(name[i]);
		if(name[i]=='b'||
		   name[i]=='f'||
		   name[i]=='p'||
		   name[i]=='v'
		){
			number[i-1]=1;
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
			number[i-1]=2;
		}else if(
		   name[i]=='d'||
		   name[i]=='t'
		){
			number[i-1]=3;
		}else if(
		   name[i]=='l'
		){
			number[i-1]=4;
		}else if(
		   name[i]=='m'||
		   name[i]=='n'
		){
			number[i-1]=5;
		}else if(
		   name[i]=='r'
		){
			number[i-1]=6;
		}else{
			number[i-1] = 0;
		}
	}
	return number;
}
char *generate_result(char *name, int *number)
{
	int i,j;
	char *result = (char *)malloc(sizeof(char)*NUMBER+1);
	result[0]=name[0];
	for(i=0,j=0;j<NUMBER;i++){
		if(number[i+1]==0 && number[i+2]==number[i]){
			result[j]=number[i];
			j++;
			i = i+2;
		}else if(number[i+1]==0 && number[i+2]!=number[i]){
			result[j]=number[i];
			j++;
			i = i+1;
		}else if(number[i]==number[i+1]){
			result[j]=number[i];
			j++;
			i = i+1;
		}else{
			result[j]=number[i];
			j++;
		}
	}
	return result;
	
	
}
