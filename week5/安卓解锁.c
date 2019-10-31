#include<stdio.h>
#define LEN 8 //LEN means 线段，所以3*3 grid 中最多有八个 
#define SIZE 3

struct coordinate{
	int x;
	int y;
};
int find_patterns(struct coordinate a,int p[SIZE][SIZE],int len);
int main (void)
{
	int sum=0;
	int len=8;
	int p[SIZE][SIZE]={0};
	int i,j;
	struct coordinate origin;
	origin.x=0;
	origin.y=0;
	sum = find_patterns(origin,p,len);
	printf("the sum is %d\n",sum);

	
	
 } 
 
int find_patterns(struct coordinate a,int p[SIZE][SIZE],int len){
	struct coordinate b;
	int i,j,k,m,sum;
	if(len==0){
		return 1;
	}
	if(p[a.y][a.x]!=0){
		return 0;
	}	

	sum=0;
    for(i=-1;i<2;i++){
    	for(j=-1;j<2;j++){
    		p[a.y][a.x]=LEN-len+1;
    		b.y=a.y+i;
			b.x=a.x+j; 
    		if((i+j==1||i+j==-1)&&(p[b.y][b.x] ==0)&&b.y>=0 && b.y<SIZE&& b.x>=0 && b.x<SIZE){
					
    			sum += find_patterns(b,p,len-1);
				p[b.y][b.x]=LEN-len+2;
				for(k=0;k<SIZE;k++){
					for(m=0;m<SIZE;m++){
						printf("%d",p[k][m]);
					}
				printf("\n");
				}
				printf("\n");
    			p[b.y][b.x]=0;
			}
		}
	}
	return sum;
}

