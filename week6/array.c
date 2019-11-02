#include<stdio.h>

int main(void)
{
	int c;
	while((c=getchar())!=EOF&&c!='\n'){
		putchar(c);
		putchar(c);
	}
	return 0;
	
}
