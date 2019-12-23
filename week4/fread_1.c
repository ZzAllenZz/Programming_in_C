#include<stdio.h>
int main(void){
	FILE *fp;
	int i;
	char arr[6];
	if((fp=fopen("doof.txt","rb"))==NULL){
		printf("Cannot open file\n");
		return 1;
	}
	fread(arr,sizeof(char),5,fp);
	for(i=0;i<5;i++){
		printf("character %d is %c\n",i,arr[i]);
	}
	fclose(fp);
	return 0;
}
