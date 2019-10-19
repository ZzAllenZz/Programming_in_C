#include<stdio.h>
#include<ctype.h>

void read_in(char *input,int *count);
int compare(char *input,int count);

int main(void){
	char input[500];
	int i=0,*count,result;
	count = &i; 
	printf("enter the content\n");
	read_in(input,count);
	printf("%s\n",input);
	result = compare(input,*count);
	if(result){
		printf("the content is palindromes!");
	}else{
		printf("the content is not palindromes!");
	}
	}

void read_in(char *input,int *count){
	int c,i=0;
	while ((c =getchar())!=EOF && c!='\n'){
		if(isalpha(c)){
			input[i] = tolower(c);
			i++;
		}
	}
	input[i]='\0'; 
	*count = i+1;/* include '\0'*/

	
}
int compare(char *input,int count){
	int i ;
	if(count %2 !=0){
		for(i=0;i<count/2;i++){
			if(input[i] !=input[count-2-i]){
				return 0;
			}
		}
	}else {
		for(i=0;i<count/2-1;i++){
		if(input[i] !=input[count-2-i]){
				return 0;
	}
	}
	}
	return 1;
}

