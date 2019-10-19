#include<stdio.h>
void f(void);
int main(void){
//	int *p,a=5;
//	p=&a;
//	p= (int *) 10;
//	printf("%p\n",p);
	
	f();
	f();
	
	
	
	return 0;
}
void f(void){
	static int cnt = 0;
	cnt++;
	printf("%d\n",cnt);
}
