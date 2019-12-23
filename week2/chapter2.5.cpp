#include<stdio.h>

struct box{
	int number;
	int length;
	int largest;
};
typedef struct box    box;
void find(box x[]);
void compare(box x[]);
int main(void){
	box x[50000];
	box *p ;
    p = x;
	find(p);
    compare(p);

	return 0;
	
}
void find(box x[]){
	int i;
	for(i=0;i<50000;i++){
		x[i].number =i+1;
		
	    int count = 1,value = x[i].number,max=x[i].number;
		while(value !=1){
		if(value%2==0){
		value = value/2;
		}else{
		value = 3*value+1;
		if(max<value){
			max = value;
		}

		}
		count++;
		}
		
		x[i].length = count;
		x[i].largest = max;
		}
	
	}	


void compare(box x[]){
	int i = 0, max_value = x[i].largest,max_value_number=x[i].number;
	int max_length = x[i].length,max_length_number = x[i].number;
	for(i=0;i<49999;i++){
		if(max_value<x[i+1].largest){
			max_value = x[i+1].largest;
			max_value_number = x[i+1].number;
		}
		if(max_length<x[i+1].length){
			max_length = x[i+1].length;
			max_length_number = x[i+1].number;
		}
	}
	printf("type\t\tinitial number\t\t max\n ");
	printf("largest\t %d\t\t\t %d\n ",max_value_number,max_value);
	printf("longest\t %d\t\t\t %d\n ",max_length_number,max_length);
}
	
	
	
	
	
	

