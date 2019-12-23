#include<stdio.h>
void check_money(int);

int main(void){
	int input;
	printf("how many money would you like?   ");
	scanf("%d",&input);
	check_money(input);
	return 0;	
} 
void check_money(int input){
	int number,higher,lower;
	while(input%20 != 0){
		number = input/20;
		lower = number*20;
		higher= lower+20;
		printf("I can give you %d or %d, try again\n",lower,higher);
		printf("how many money would you like?   ");
		scanf("%d",&input);	
	}

		printf("OK, dispensing ....");
	}
	

