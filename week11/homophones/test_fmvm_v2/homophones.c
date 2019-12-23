
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fmvm.h"

#define FILENAME  "cmudict.txt"
#define NULL_N -1
#define SHIFTING 10
#define SHIFT_ONE 1
#define SHIFT_THREE 3
#define WORD_MAX 50
#define HOMOPHONES_MAX 150



char **parse_command(int argc, char **argv, int *words_count,int *n_index,int *n);
void get_words_array(char **words_array,char **argv,int words_count,int n_index);
int find_n_index(int argc, char **argv);
int find_n_in_command(char **argv,int n_index);
int find_words_count(int argc,int n);
void find_result(char **words_array,int words_count, int n_from_command);
void print_words(char **words,int words_count);
int get_n_real(char *key);
int find_space_number(char str[]);
void read_in(mvm *map_one, mvm *map_two,int n);
void reinit_array(char str[],int len);
char *find_n_phonemes(char str[],int n);
void read_str(FILE *fp,char str1[],char str2[]);

int main(int argc, char **argv)
{

    char **words_array;
    int words_count = 0;
    int n_from_command = 0;
    int n_index = 0;

    words_array = parse_command(argc,argv,&words_count,&n_index,&n_from_command);

    find_result(words_array,words_count,n_from_command);
    free(words_array);

    return 0;
}


void find_result(char **words_array,int words_count, int n_from_command)
{
    int i;
    char *phonemes;
    char **words;
    int n_real;
    int words_number;
    int time1 = 0;
    int time2 = 0;
    mvm *map_one = mvm_init();
    mvm *map_two = mvm_init();
    if(n_from_command == NULL_N){
        for(i=0;i<words_count;i++){
            n_real = get_n_real(words_array[i]);

            read_in(map_one,map_two,n_real);

            phonemes = mvm_search(map_one,words_array[i],&time1);
            words = mvm_multisearch(map_two,phonemes, &words_number,&time2);
            printf("average search is %d, and average multisearch is %d\n",time1,time2);
            printf("%s(%s): ",words_array[i],phonemes);
            print_words(words,words_number);
            free(words);
            mvm_free(&map_one);
            mvm_free(&map_two);
            map_one = mvm_init();
            map_two = mvm_init();
        }
        mvm_free(&map_one);
        mvm_free(&map_two);
    }else{
        read_in(map_one,map_two,n_from_command);

        for(i=0;i<words_count;i++){
            n_real = get_n_real(words_array[i]);
            if(n_real>= n_from_command){
                phonemes = mvm_search(map_one,words_array[i],&time1);
                words = mvm_multisearch(map_two,phonemes, &words_number,&time2);
                printf("average search is %d, and average multisearch is %d\n",time1,time2);
                printf("%s(%s): ",words_array[i],phonemes);
                print_words(words,words_number);
                free(words);
            }else{
                printf("%s: undefined\n",words_array[i]);
            }

        }
        mvm_free(&map_one);
        mvm_free(&map_two);
    }
    return;
}

char **parse_command(int argc, char **argv, int *words_count,int *n_index,int *n)
{
    char **words_array;
    if(argc<=1){
        fprintf(stderr,"ERROR,TRY:%s <word>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    *n_index = find_n_index(argc,argv);

    *n = find_n_in_command(argv,*n_index);


    *words_count = find_words_count(argc,*n);
    words_array = (char **)malloc(sizeof(char *)*(*words_count));
    get_words_array(words_array,argv,*words_count,*n_index);

    return words_array;
}

void get_words_array(char **words_array,char **argv,int words_count,int n_index)
{
    int i,j;
    if(n_index == NULL_N){
        for(i=0,j=1;i<words_count;i++,j++){
            words_array[i] = argv[j];
        }
    }else{
        for(i=0,j=1;i<words_count;j++){
            if(j!=n_index-SHIFT_ONE && j!= n_index){
                words_array[i] = argv[j];
                i++;
            }
        }
    }
}
int find_n_index(int argc, char **argv)
{
    int i;
    int n_index = NULL_N;
    for(i=0;i<argc;i++){
        if(strcmp(argv[i],"-n")==0){
            n_index = i;
        }
    }
    if(n_index==NULL_N){
        return n_index;
    }else{
        n_index++;
        return n_index;
    }
}

int find_n_in_command(char **argv,int n_index)
{
    int i;
    int n = 0;
    int len;
    if(n_index==NULL_N){
        n = NULL_N;
        return n;
    }
    len = strlen(argv[n_index]);
    for(i=0;i<len;i++){
        if(i!=0){
            n *=SHIFTING;
        }
        n += argv[n_index][i]-'0';
    }
    return n;
}

int find_words_count(int argc,int n)
{
    int words_count;
    if(n==NULL_N){
        words_count = argc - SHIFT_ONE;
    }else{
        words_count = argc - SHIFT_THREE;
    }
    return words_count;
}



void print_words(char **words,int words_number)
{
    int i;
    for(i=0;i<words_number;i++){
        printf(" %s",words[i]);
    }
    printf("\n");
}


int get_n_real(char *key)
{
    int n_real,space_number;
    char str1[WORD_MAX] = {'\0'};
    char str2[HOMOPHONES_MAX] = {'\0'};

    FILE *fp;
    if((fp=fopen(FILENAME,"r"))==NULL){
        fprintf(stderr,"Failed to open file...\n");
        exit(EXIT_FAILURE);
    }
    while(!feof(fp)){
        read_str(fp,str1,str2);
        if(strcmp(key,str1)==0){
            space_number = find_space_number(str2);
            n_real = ++space_number;
            fclose(fp);
            return n_real;
        }
        reinit_array(str1,strlen(str1));
        reinit_array(str2,strlen(str2));
    }
    fclose(fp);
    return NULL_N;
}

void read_str(FILE *fp,char str1[],char str2[])
{
    int j,k,i;
    j = 0;
    while((i= getc(fp))!='#'&& i != EOF){
        str1[j++] = i;
    }
    k = 0;
    while((i = getc(fp))!='\r'&&i != '\n' && i != EOF){
        str2[k++]= i;
    }
    i = getc(fp);
    /*two char in end of line:'\r'and 'n',so we need to destroy one*/
}




int find_space_number(char str[])
{
    int space_number = 0;
    int i;
    int len = strlen(str);
    for(i=0;i<len;i++){
        if(str[i] == ' '){
            space_number++;
        }
    }
    return space_number;
}
void read_in(mvm *map_one, mvm *map_two,int n)
{
    char str1[WORD_MAX] = {'\0'};
    char str2[HOMOPHONES_MAX] = {'\0'};
    char *str3;
    int time1;
    int time2;
    int count1= 0;
    int count2 = 0;
    FILE *fp;

    if((fp=fopen(FILENAME,"r"))==NULL){
        fprintf(stderr,"failed to open file...\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(fp)){
        read_str(fp,str1,str2);

        str3= find_n_phonemes(str2,n);

        mvm_insert(map_one, str1, str3,&time1);
        mvm_insert(map_two, str3, str1,&time2);
        count1 += time1;
        count2 += time2;
        free(str3);
        reinit_array(str1,strlen(str1));
        reinit_array(str2,strlen(str2));
    }
    printf("the count1 is %lf, the count2 is %lf\n",134298.0/count1,134298.0/count2);
    fclose(fp);

}

void reinit_array(char str[],int len)
{
    int i;
    for(i=0;i<len;i++){
        str[i] = '\0';
    }
}


char *find_n_phonemes(char str[],int n)
{
    int i;
    int j = 0;
    int space_number;
    int count;
    int wait;
    int len = strlen(str);
    char *result;

    space_number = find_space_number(str);
    count = ++space_number;
    if(n>count){
        return NULL;
    }
    wait = count - n;
    result = (char *)calloc(50,sizeof(char));
    for(i=0;i<len;i++){
        if(wait<=0){
            result[j++] = str[i];
        }
        if(str[i]==' '){
            wait--;
        }
    }
    return result;
}



