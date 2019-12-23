#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 20
#define ROUND 50000000
void generate_array(int array[LEN]);
void swap(int array[LEN],int a,int b);
int count(int array[LEN]);
void result();
int main(void){
	result();
	return 0;
}

void result()
{
	int array[LEN];
	int i,total,temp_count;
	int random1,random2;
	
	srand((unsigned)time(NULL));

	generate_array(array);
	total = count(array);
	
	for(i=0;i<ROUND;i++){
		random1 = rand()%LEN;
		random2 = rand()%LEN;
		swap(array,random1,random2);
		temp_count=count(array);
		if(temp_count<total){
			total=temp_count;
		}
	}
	printf("%d:\n",total);
	for(i=0;i<LEN;i++){
		printf("%d ",array[i]);
	}
}

void generate_array(int array[LEN]){
	int i;
	for(i=0;i<LEN;i++){
		array[i]=i+1;
	}
	
}

void swap(int array[LEN],int a,int b){

	int temp;

	temp=array[a];
	array[a] = array[b];
	array[b]=temp;	
}

int count(int array[LEN])
{
	int i;
	int count=0;
	for(i=0;i<LEN;i++){
		if(i<=LEN-3){
			count += pow(array[i]+array[i+1]+array[i+2],2);
		}else if(i==LEN-2){
			count += pow(array[i]+array[i+1]+array[0],2);
			
		}else if(i==LEN-1){
			count += pow(array[i]+array[0]+array[1],2);
			
		}
		
	}
}







