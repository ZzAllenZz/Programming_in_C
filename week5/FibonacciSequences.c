#include<stdio.h>
#include<assert.h>
int fibon(int n);
void test();
int main(void){
	int i;
	for (i=1;i<20;i++)
	{
		printf("No %d = %d\n",i,fibon(i));
	}
	return 0;
} 

int fibon(int n)
{
	if(n==1) return 1;
	if(n==2) return 1;
	return (fibon(n-1)+fibon(n-2));	
} 

void test(){
	assert(fibon(3)==2);
	assert(fibon(6)==8);
}
