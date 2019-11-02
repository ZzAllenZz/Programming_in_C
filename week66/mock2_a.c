#include<stdio.h>
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
    int i,j;
    int count=0;
    int len;
    len =strlen(s);
    for(i=0;i<len;i++){
        for(j=i+1;j<len;j++){
            if(s[i]==s[j]){
                count++;
            }
        }
    }
    if(count==0){
        return 1 ;
    }else{
        return 0;
    }
}