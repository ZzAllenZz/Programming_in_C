#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<stdlib.h>
void find_longest(char longest[50],char *name);
int isogram(char *s);
int main(int argc,char **argv){
    char longest[50];
    int len;
    printf("1111\n");
    assert(isogram("programming")==0);
    assert(isogram("housewarmings")==0);
    assert(isogram("abductions")==1);
    assert(isogram("housewarming")==1);
    assert(isogram("hydromagnetics")==1);
    assert(isogram("uncopyrightable")==1);
    if(argc ==2){
        find_longest(longest,argv[1]);
        len = strlen(longest);
        printf("%s\n",longest);
        printf("the len of it is %d\n",len);
    }else{
        printf("Error,usage e.g. %s eowl_shuffle.txt\n",argv[0]);
    }
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

void find_longest(char *longest,char *name){
    FILE *fp;
    int i;
    int round =0;
    char str[50]={"\0"};
    fp = fopen(name,"r");
    if(fp==NULL){
        printf("Failed to open file\n");
        exit(EXIT_FAILURE);
    }   
    while (!feof(fp))
    {
         fscanf(fp,"%s",str);
         if(isogram(str)){
             if(round==0){
                 longest = strcpy(longest,str);
             }else{
                 if(strlen(str)>strlen(longest)){
                     longest = strcpy(longest,str);
                 }
             }
             round++;
         }

        for(i=0;i<50;i++){
            str[i]='\0';
        }

    }

    
   
}