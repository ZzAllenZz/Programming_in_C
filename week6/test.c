#include<stdio.h>
#include<string.h>

int main(void){
    char *str;
    
    int len;
    str="abc";
    len  = strlen(str);
    printf("the len of str is %d",len);
    /*
    int i;
    gets(str);
    if(sscanf(str,"%d",&i)!=1){
        printf("cannot scan string\n");
        return 1 ;
    }else{
        printf("The number was %d\n",i);
    }
    */
    return 0;
}