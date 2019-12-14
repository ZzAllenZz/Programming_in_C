
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fmvm.h"
/*#include <assert.h>*/

/*This programme can be divided into three main parts
 *1.Parse the command line;
 *2.Read strings from dictionary and insert key/value into two maps;
 *3.Search the words by using two maps;
 * */

/*Explanation for result:
 *1.if there is no -n in command, for each word, its total actual
 * number of phonemes will be used. e.g.BOY->B OY1, CHRISTMAS->K R IH1 S M AH0 S
 *2.if there is a -n, n's value will be used, and in the case of n's value
 * > number of phonemes, result is undefined.
 * */

#define FILENAME  "cmudict.txt"
#define NULL_N -1 /*Means no n in command*/
#define MULTI_TEN 10 /*Used in the case n's value >=10 */
#define ZERO '0'
#define SHIFT_ONE 1 /*Used when calculate number of words in command line*/
#define SHIFT_THREE 3/*Used when calculate number of words in command line*/
#define WORD_MAX 50 /*the max number of one word*/
#define HOMOPHONES_MAX 150 /*the max number of one word's phonemes*/

/*PART1:*/
char **parse_command(int argc, char **argv, int *words_count,int *n_index,int *n);
int find_n_index(int argc, char **argv);
int find_n_in_command(char **argv,int n_index);
int find_words_count(int argc,int n);
void get_words_array(char **words_array,char **argv,int words_count,int n_index);

/*PART2:*/
void read_in(mvm *map_one, mvm *map_two,int n);
void read_str(FILE *fp,char str1[],char str2[]);
void reinit_array(char str[],int len);
char *find_n_phonemes(char str[],int n);
int find_space_number(char str[]);

/*PART3:*/
void find_result(char **words_array,int words_count, int n_from_command);
int get_n_real(char *key);
void find_result_without_n(int words_count,char **words_array);
void find_result_with_n(int words_count,char **words_array,int n_from_command);
void print_words(char **words_from_search,int words_count);

/*void test();*/

int main(int argc, char **argv)
{

    char **words_array;/*Used to store words from command line*/
    int words_count = 0;/*Used to count how many words in command line*/
    int n_index = 0; /*the location of number in command line*/
    int n_from_command = 0;/*the value of number in command line*/

/*    test();*/

    words_array = parse_command(argc,argv,&words_count,&n_index,&n_from_command);

    find_result(words_array,words_count,n_from_command);
    free(words_array);

    return 0;
}

/*PART1:*/
/*Parse the command line,includes:
 * 1.whether it has -n and n's value;
 * 2.store n's value and its index;
 * 3.how many words we need to deal with in next step;
 * 4.store these words into words_array;
 * */
char **parse_command(int argc, char **argv, int *words_count,int *n_index,int *n)
{
    char **words_array;
    if(argc<=1){
        fprintf(stderr,"ERROR,TRY:%s <word>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    /*NULL_N(-1) represents no -n and n's value in command */
    *n_index = find_n_index(argc,argv);
    *n = find_n_in_command(argv,*n_index);

    *words_count = find_words_count(argc,*n);
    words_array = (char **)malloc(sizeof(char *)*(*words_count));
    get_words_array(words_array,argv,*words_count,*n_index);
    return words_array;
}

int find_n_index(int argc, char **argv)
{
    int i;
    int n_index = NULL_N;
    for(i=0;i<argc;i++){
        if(strcmp(argv[i],"-n") == 0){
            n_index = i;
        }
    }
    if(n_index==NULL_N){
        /*No -n in command*/
        return n_index;
    }else{
        n_index++;
        /*n_index is the index of value of n, not "-n"*/
        return n_index;
    }
}

int find_n_in_command(char **argv,int n_index)
{
    int i;
    int n = 0;
    int len;
    if(n_index==NULL_N){
        /*NULL_N means that no -n in command*/
        n = NULL_N;
        return n;
    }
    /*Consider the case that n's value >=10*/
    len = strlen(argv[n_index]);
    for(i=0;i<len;i++){
        n *= MULTI_TEN;
        n += argv[n_index][i]-ZERO;
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

/*store the words from command into words_array */
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


/*PART3:*/
void find_result(char **words_array,int words_count, int n_from_command)
{

    if(n_from_command == NULL_N){
        find_result_without_n(words_count,words_array);
    }else{
        find_result_with_n(words_count,words_array,n_from_command);
    }
}

/*find_result_without_n and find_result_with_n are different, and cannot put them into one function
 * because:
 * 1.without n: for each words from command, we need to re-read file, again and again,
 * since they have different number of phonemes;
 * 2.with n: we just need read file once,
 * since we fixed the n phonemes;
 * */
void find_result_without_n(int words_count,char **words_array)
{
    int i, n_real,words_number;
    char *phonemes;
    char **words_from_search;

    mvm *map_one = mvm_init();
    mvm *map_two = mvm_init();

    for(i=0;i<words_count;i++){
        /*n real means the word's actual number of phonemes*/
        n_real = get_n_real(words_array[i]);
        read_in(map_one,map_two,n_real);
        phonemes = mvm_search(map_one,words_array[i]);
        words_from_search = mvm_multisearch(map_two,phonemes, &words_number);
        printf("%s(%s): ",words_array[i],phonemes);
        print_words(words_from_search,words_number);
        free(words_from_search);
        mvm_free(&map_one);
        mvm_free(&map_two);
        map_one = mvm_init();
        map_two = mvm_init();
    }
    mvm_free(&map_one);
    mvm_free(&map_two);
}

void find_result_with_n(int words_count,char **words_array,int n_from_command)
{
    int i, n_real,words_number;
    char *phonemes;
    char **words_from_search;

    mvm *map_one = mvm_init();
    mvm *map_two = mvm_init();

    read_in(map_one,map_two,n_from_command);

    for(i=0;i<words_count;i++){
        /*n real means the word's actual number of phonemes*/
        n_real = get_n_real(words_array[i]);
        if(n_real>= n_from_command){
            phonemes = mvm_search(map_one,words_array[i]);
            words_from_search = mvm_multisearch(map_two,phonemes, &words_number);

            printf("%s(%s): ",words_array[i],phonemes);
            print_words(words_from_search,words_number);
            free(words_from_search);
        }else{
            printf("%s: undefined\n",words_array[i]);
        }
    }
    mvm_free(&map_one);
    mvm_free(&map_two);
}

void print_words(char **words_from_search,int words_number)
{
    int i;
    for(i=0;i<words_number;i++){
        printf(" %s",words_from_search[i]);
    }
    printf("\n");
}
/*n real means the word's actual number of phonemes*/
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

/*PART2:*/
void read_in(mvm *map_one, mvm *map_two,int n)
{
    char str1[WORD_MAX] = {'\0'};
    char str2[HOMOPHONES_MAX] = {'\0'};
    char *str3;
    FILE *fp;
    if((fp=fopen(FILENAME,"r"))==NULL){
        fprintf(stderr,"Failed to open file...\n");
        exit(EXIT_FAILURE);
    }
    while(!feof(fp)){
        /*str1 gets words, and str2 gets its total phonemes*/
        read_str(fp,str1,str2);
        /*str3 gets required-number phonemes*/
        str3= find_n_phonemes(str2,n);

        mvm_insert(map_one, str1, str3);
        mvm_insert(map_two, str3, str1);

        free(str3);
        reinit_array(str1,strlen(str1));
        reinit_array(str2,strlen(str2));
    }
    fclose(fp);
}


/*Split one line in dictionary into two strings by '#' */
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
    /*Two char in the end of line:'\r'and 'n',so we need to eat one*/
}

/*Filter the string into what we want(specified n phonemes) */
char *find_n_phonemes(char str[],int n)
{
    int i,j;
    int space_number,count,wait;
    int len = strlen(str);
    char *result;

    space_number = find_space_number(str);
    count = ++space_number; /*space_number + 1 == number of words*/
    if(n>count){
        return NULL;
    }
    /*n is the number of phonemes we need*/
    /*wait is the number of space we need to wait before we read in*/
    wait = count - n;
    result = (char *)calloc(HOMOPHONES_MAX,sizeof(char));
    for(i=0,j=0;i<len;i++){
        if(wait<=0){
            result[j++] = str[i];
        }
        if(str[i]==' '){
            wait--;
        }
    }
    return result;
}

/*Calculate total number of space in one str*/
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

void reinit_array(char str[],int len)
{
    int i;
    for(i=0;i<len;i++){
        str[i] = '\0';
    }
}

/*
void test()
{
    int argc = 6;
    char **words_array;
    int words_count = 0;
    int n_index = 0;
    int n_from_command = 0;
    char **argv = (char **)malloc(sizeof(char *)*6);
    char str0[] = "ab cd ef gh yz";
    char *str;
    int number;
    int n_real;
    argv[0] = "./a.out";
    argv[1] = "abc";
    argv[2] = "def";
    argv[3] = "-n";
    argv[4] = "3";
    argv[5] = "xyz";

    words_array = parse_command(argc,argv,&words_count,&n_index,&n_from_command);
    assert(words_count == 3);
    assert(n_index == 4);
    assert(n_from_command == 3);
    assert(strcmp(words_array[0],"abc")==0);
    assert(strcmp(words_array[1],"def")==0);
    assert(strcmp(words_array[2],"xyz")==0);
    free(words_array);
    free(argv);


    number = find_space_number(str0);
    assert(number == 4);

    str = find_n_phonemes(str0,3);
    assert(strcmp(str,"ef gh yz")==0);
    free(str);

    n_real =  get_n_real("RHYME");
    assert(n_real==3);

}
*/

