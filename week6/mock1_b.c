#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<stdlib.h>

int derange(char s1[],char s2[]);

int main(void){
    assert(derange("elvis","lives")==0);
    assert(derange("dreads","sadder")==1);
    assert(derange("replays","parsley")==1);
    assert(derange("listen","silent")==0);
    assert(derange("orchestra","carthorse")==1);

    return 0;
}

int derange(char s1[],char s2[])
{
    int len1=strlen(s1),len2=strlen(s2);
    int *p;
    int i,j,count=0;
    p = (int *)malloc(sizeof(int)*len1);
    for(i=0;i<len2;i++){
        p[i]=0;
    }
    if(len1 != len2){
        return 0;
    }
    if(!strcmp(s1,s2)){
        return 0;
    }
    for(i=0;i<len1;i++){
        for(j=0;j<len2;j++){
            if(s1[i]==s2[j]&&p[j]==0&&i!=j){
                count++;
                p[j]=1;
            }
        }
    }
    if (count==len1)
    {
        return 1 ;
    }else{
        return 0;
    }
    



}