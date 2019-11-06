#include<stdio.h>
#include<math.h>
#define maxn 800
char matrix[maxn][maxn];
//坐标 
int X[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int Y[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
 
void fill(int n, int x, int y){
	int i;
	int newX; 
	int newY;
	if(n == 1){
		return;
	}else if(n == 2){
		matrix[x][y] = '#';
		return;
	}
	//画四周图形 
	for( i = 0; i < 9; i++){
		newX = x + X[i] * pow(3, n - 2);
		newY = y + Y[i] * pow(3, n - 2);
		fill(n - 1, newX, newY);
	}
	//画中央图形
	for(i = 0; i < 9; i++){
		newX = x + X[i] * pow(3, n - 3);
		newY = y + Y[i] * pow(3, n - 3);
		fill(n - 1, newX, newY);
	} 
} 
 
int main(){
	int n;
	int i,j;
	scanf("%d", &n);
	fill(n, 400, 400);
	int scale = pow(3, n - 1);
	for( i = 400 - scale / 2 - 1; i <= 400 + scale/2 + 1; i++){
		for(j = 400 - scale / 2 - 1; j <= 400 + scale / 2 + 1; j++){
			//打印四周的' ' 
			if(j == 400 - scale / 2 - 1 || j == 400 + scale / 2 + 1 || i == 400 - scale / 2 - 1 || i == 400 + scale / 2 + 1){
				printf(" ");
			}else if(matrix[i][j] == '#'){
				printf(" ");
			}else{
				printf("#");
			}
		}
		printf("\n");
	}
	return 0;
}
