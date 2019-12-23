
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mvm.h"
int parse_command(int argc, char **argv);

void read_in(char *filename, mvm *map_one, mvm *map_two,char *key, int flag);
char *find_n_phonemes(char str[],int n);
void reinit_array(char str[],int len);
mvm *mvm_init(void);
void mvm_insert(mvm* m, char* key, char* data);
char *search_map_one(mvm *m,char *key);
char *search_map_two(mvm* m, char* key);
void search(char *key,int flag);
void mvm_free(mvm** p);
void free_linked_list(mvmcell **head);
int find_n(char *key,int flag);

int main(int argc, char **argv)
{
    int flag;
    int i;
    if(argc<=1){
        fprintf(stderr,"ERROR,TRY:%s <word>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    flag = parse_command(argc,argv);

    if(flag == 0){
        for(i=1;i<argc;i++){
            search(argv[i],flag);
        }
    }else{
        for(i=1;i<argc;i++){
            if(i!=flag &&i!= flag +1){
                search(argv[i],argv[flag+1][0]-48);
            }

        }
    }

    return 0;
}

int parse_command(int argc, char **argv)
{
    int i;
    int flag = 0;
    for(i=0;i<argc;i++){
        if(strcmp(argv[i],"-n")==0){
            flag = i;
        }
    }

    return flag;

}

void search(char *key,int flag)
{
    char *phonemes;
    char *words;

    mvm *map_one = mvm_init();
    mvm *map_two = mvm_init();
    read_in("cmudict.txt",map_one,map_two,key,flag);
    phonemes = search_map_one(map_one,key);
    words = search_map_two(map_two,phonemes);
    printf("%s(%s):\n",key,phonemes);
    printf("%s\n",words);
    mvm_free(&map_one);
    mvm_free(&map_two);
}
void read_in(char *filename, mvm *map_one, mvm *map_two,char *key, int flag)
{
    char str1[50] = {'\0'};
    char str2[100] = {'\0'};
    char *str3;
    FILE *fp;
    int i,j,k;
    int n;

    if((fp=fopen(filename,"r"))==NULL){
        fprintf(stderr,"failed to open file...\n");
        exit(EXIT_FAILURE);
    }

    n = find_n(key,flag);
    while(!feof(fp)){

        j = 0;
        while((i= getc(fp))!='#'&& i != EOF){
            str1[j++] = i;
        }
        k = 0;
        while((i = getc(fp))!='\r'&&i != '\n' && i != EOF){
            str2[k++]= i;
        }
        i = getc(fp);


        str3= find_n_phonemes(str2,n);
        mvm_insert(map_one, str1, str3);
        mvm_insert(map_two, str3, str1);

        reinit_array(str1,strlen(str1));
        reinit_array(str2,strlen(str2));
    }

    fclose(fp);

}

void reinit_array(char str[],int len)
{
    int i;
    for(i=0;i<len;i++){
        str[i] = '\0';
    }
}

int find_n(char *key,int flag)
{



    if(flag != 0){
        return flag;
    }
    return 0;
}
char *find_n_phonemes(char str[],int n)
{
    int i;
    int j = 0;
    int space_number = 0;
    int count;
    int wait;
    int len = strlen(str);
    char *result;
    for(i=0;i<len;i++){
        if(str[i]== ' '){
            space_number++;
        }
    }
    count = space_number+1;
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

mvm *mvm_init(void)
{
    mvm *m = (mvm *)calloc(1,sizeof(mvm));
    m->head = NULL; /*important!*/
    m->numkeys = 0;
    return m;
}

void mvm_insert(mvm* m, char* key, char* data)
{
    mvmcell *cell;
    if(m==NULL||key == NULL||data ==NULL){
        return;
    }
    cell = (mvmcell *)malloc(sizeof(mvmcell));
    cell->data = (char *)malloc(sizeof(char)*strlen(data)+sizeof(char));
    cell->key = (char *)malloc(sizeof(char)*strlen(key)+sizeof(char));
    strcpy(cell->key,key);
    strcpy(cell->data,data);
    cell->next = m->head;
    m->head = cell;
    m->numkeys++;
}




char *search_map_one(mvm *m,char *key)
{
    if(m!=NULL&&key!=NULL){
        mvmcell *temp = m->head;

        while(temp != NULL && strcmp(temp->key,key)!=0 ){/*why???*/
            temp = temp ->next;

        }

        if(temp == NULL){

            return NULL;
        }
        return temp->data;
    }
    return NULL;
}


char* search_map_two(mvm* m, char* key)
{
    if(m !=NULL&& key!=NULL){
        char *a;
        int offset = 0;
        mvmcell *temp = m->head;
        a = (char *)calloc(1, sizeof(char));

        while(temp!=NULL){
            if(strcmp(temp->key,key)==0){
                a = (char *)realloc(a,(strlen(a)+strlen(temp->data)\
                +strlen(", "))* sizeof(char)+sizeof(char));
                offset += sprintf(a+offset,"%s, ",temp->data);
                temp = temp->next;
            }
            temp = temp ->next;
        }
        return  a;
    }
    return NULL;
}

