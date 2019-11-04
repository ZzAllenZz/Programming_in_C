#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 5000
#define SIZE 50
void sort_one_round(char array[MAX][SIZE],int len,char word[SIZE]);
int read_in(char array[MAX][SIZE],char *name);
int binary_search(char *name,char *input);


int main(void){
	int result;
	clock_t start,finish;
	double duration;
	start = clock();
	
    result = binary_search("34words.txt","love");
    if(result==1){
    	printf("find it!\n");
	} else{
		printf("cannot find it!\n");
	}
	finish = clock();
	duration = (finish-start)/CLOCKS_PER_SEC;
	printf("the running duration is %lf\n",duration);
    return 0;
}

int binary_search(char *name,char *input){
    static char array[MAX][SIZE];
    int l=0,r,m,len;

    len = read_in(array,name);
    printf("the len of dictionary is %d\n",len);  

    r = len -1 ;
    m=(l+r)/2;

    while(strcmp(input,array[m])!=0 &&len!=0){
    	if(strcmp(input,array[m])<0){
    		r=m+1;
		}else{
			l=m+1;
		}
		m=(l+r)/2;
		len--;
	}

	if(len==0){
		return 0;
	}else{
		return 1;
	}
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

int read_in(char array[MAX][SIZE],char *name){
	
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
    return len;
    /*返回有效array的长度*/ 
}


