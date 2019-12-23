#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 370120
#define SIZE 50
void sort_one_round(char array[MAX][SIZE],int len,char word[SIZE]);
void read_in(char *name);
int main(int argc, char **argv){
	
    clock_t start,finish;
    double duration;
    start = clock();
    read_in("34words.txt");
    finish = clock();
    duration = (finish -start)/CLOCKS_PER_SEC;
    printf("the running duration is %lf\n",duration);
    
    return 0;
}

/*len means the No of current word should be, in other word, the len of valid array after insert this word */
void sort_one_round(char array[MAX][SIZE],int len,char word[SIZE])
{
    int i,j;

    for(i=0;i<len-1;i++){
        if(strcmp(word,array[i])<0){
            for(j=len-1;j>i;j--){

                strcpy(array[j],array[j-1]);
            }
            strcpy(array[i],word);
            return;
        }
    }
    strcpy(array[len-1],word);
    return ;
}

void read_in(char *name){
    static char array[MAX][SIZE];
    FILE *fp;
    char word[SIZE];
    int len=0,i;
    fp= fopen(name,"r");
    if(fp==NULL){
        printf("cannot open file!\n");
        exit(1);
    }


    while(fscanf(fp,"%s",word)==1){
        len++;
        sort_one_round(array,len,word);
    }
    fclose(fp);
    for(i=0;i<len;i++){
            printf("%s\n",array[i]);
    }



}
