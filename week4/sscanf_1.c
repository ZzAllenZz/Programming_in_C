#include <stdio.h>
int main(void){
	char str[500];
	int i;
	gets(str);
	if(sscanf(str,"%d",&i) !=1){
		printf("Cannot scan string !\n");
		return 1;
	}
	else {
		printf("The number was %d\n",i);
	}
	return 0; 
} 
