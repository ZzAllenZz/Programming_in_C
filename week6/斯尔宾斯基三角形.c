#include <stdio.h>
#include <stdlib.h>

#define LEN 70	//数组宽/高

int SIZE=5;	//递归次数

char arr[LEN][LEN];	//定义二维数组

void chu(){	//初始化
	int j;
	int j_=SIZE-1;
	int p=3;
	for(j=0;j<j_;j++){
		p*=2;
	}
	SIZE=p;
	int i;
	for(i=0;i<LEN;i++){
		int j;
		for(j=0;j<LEN;j++){
			arr[i][j]=' ';
		}
	}
}
void hua(){	//打印
	int i;
	for(i=0;i<LEN;i++){
		int j;
		for(j=0;j<LEN;j++){
			printf("%c",arr[i][j]);
		}
		printf("\n");
	}
}

//递归 每次将大三角形分成三个小三角形，将小三角形继续分,直到变为最小为止
void digui(int i_1,int j_1,int i_2,int j_2,int i_3,int j_3){	
	if(i_2-i_1==3){
		arr[i_1][j_1]='*';
		arr[i_1+1][j_1-1]='*'; arr[i_1+1][j_1+1]='*';
		arr[i_2-1][j_2+1]='*'; arr[i_2-1][j_2+3]='*'; arr[i_3-1][j_3-1]='*';
	}else{
		digui(i_1,j_1,i_1+(i_2-i_1)/2,j_2+(j_1-j_2)/2,i_1+(i_3-i_1)/2,j_3-(j_3-j_1)/2);
		digui(i_2-(i_2-i_1)/2,j_2+(j_3-j_1)/2,i_2,j_2,i_3,j_2+(j_3-j_2)/2);
		digui(i_1+(i_3-i_1)/2,j_1+(j_3-j_1)/2,i_3,j_2+(j_3-j_2)/2,i_3,j_3);
	}
}
void xing_a(int i,int j){	//小三角形
	arr[i][j]='*';
	arr[i+1][j-1]='*';
	arr[i+1][j+1]='*';
	arr[i+2][j-2]='*';
	arr[i+2][j]='*';
	arr[i+2][j+2]='*';
}
int main(int argc, char *argv[]) {
	chu();
	digui(0,SIZE,SIZE,0,SIZE,SIZE*2);
	hua();
	return 0;
}
