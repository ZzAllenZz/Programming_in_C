#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>

int isogram(char *s);

int main(void){
	assert(isogram("programming")==0);
	assert(isogram("housewarmings")==0);
	assert(isogram("abductions")==1);
	assert(isogram("housewarming")==1);
	assert(isogram("hydromagnetics")==1);
	assert(isogram("uncopyrightable")==1);
	return 0;
} 

int isogram(char *s){
	int len = strlen(s);
	int i,j,result=1;
	for(i=0;i<len;i++){
		for(j=i+1;j<len;j++){
			if(*(s+i)==*(s+j)){
				result= 0;
			}
		}
	}
	return result;
}


