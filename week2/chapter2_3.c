#include<stdio.h>
#define difference_1 'z'+'a'
#define difference_2 'Z'+'A'
int scode(int input);
int main(void){
	int input,c;
	printf("enter the secret code:\n");
	while((input=getchar())!= EOF){
		c=scode(input);
		putchar(c);
	}
	return 0;
} 
int scode(int input){
	if((input>=97&&input<=122)){
		return (difference_1-input);
	}else if((input>=65&&input<=90)){
		return (difference_2-input);
	} else return input;
}
