#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#include<assert.h>
int anagram(char s1[],char s2[]);
int main(void){
    assert(anagram("elvis","lives")==1);
    assert(anagram("dreads","sadder")==1);
    assert(anagram("replays","parsley")==1);
    assert(anagram("listen","silent")==1);
    assert(anagram("orchestra","carthorse")==1);

    assert(anagram("elvis","elvis")==0);
    assert(anagram("elvis","neil")==0);
    assert(anagram("neil","neill")==0);
    assert(anagram("horse","short")==0);


}

int anagram(char s1[],char s2[]){
    int len1,len2;
    int *p;
    int i,j,count=0;
    len1=strlen(s1);
    len2=strlen(s2);
    p=(int *)malloc(sizeof(int)*len2);

    if(len1!=len2){
        return 0;
    }
    if(strcmp(s1,s2)==0){
        return 0;
    }
    for(i=0;i<len2;i++){
        *(p+i) =0;
    }
    for(i=0;i<len1;i++){
        for(j=0;j<len2;j++){
            if((s1[i]==s2[j])&&(p[j]!=1)){
                count++;
                p[j]=1;
            }
        }
    }
    if(count==len1){
        return 1;
    }

    return 0;




}
