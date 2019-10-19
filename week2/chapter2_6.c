#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(void){
	srand((unsigned)time(NULL));
	int i, times = 10000,count=0;
	double x,y,result,pi;
	
	for(i =0;i<times;i++){
		x = rand()/(double)(RAND_MAX/5.0);
		y = rand()/(double)(RAND_MAX/5.0);

		result=pow(x,2)+pow(y,2);
		if(result<=25.0){
			count++;
		}
	}
	printf("count: %d",count);
	pi = 4.0*count/times;
	
	printf("pi: %.10lf",pi);
	
	return 0;
}
