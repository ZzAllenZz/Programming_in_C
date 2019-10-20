#include<stdio.h>
#include<stdlib.h>
#define MAXFILENAME 128
int main(void){
	FILE *ifp,*ofp;
	char inpname[MAXFILENAME];
	char opname[MAXFILENAME];
	int i;
	printf("Enter two filenames:");
	if(scanf("%s %s",inpname,opname) !=2){
		printf("failed to scan two filenames.");
		exit(1);
	}
	ifp = fopen(inpname,"rb");
	ofp = fopen(opname,"wb");
	if(ifp==NULL|ofp==NULL){
		printf("failed to open two files.");
		exit(1);
	}
	while((i=getc(ifp))!=EOF){
		putc(i,ofp);
	}
	fclose(ifp);
	fclose(ofp);
	return 0; 
}
