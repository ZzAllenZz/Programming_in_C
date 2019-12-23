#include <stdio.h>
#include<stdlib.h>
int main(void){
	int sum =0,val;
	FILE *ifp,*ofp;
	/*read a file*/
	ifp = fopen("my_file","r");
	if(ifp==NULL){
		exit(1);
	}
	/*write to a file*/
	ofp = fopen("outfile","w");
	if(ofp==NULL){
		exit(1);
	}
	fclose(ifp);
	fclose(ofp);
	 
}
