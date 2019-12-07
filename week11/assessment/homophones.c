
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct mvmcell{
    char* key;
    char* data;
    struct mvmcell* next;
};
typedef struct mvmcell mvmcell;
struct mvm{
    mvmcell* head;
    int numkeys;
};
typedef struct mvm mvm;

void reinit_array(char str[],int len);
void read_in(char *filename, int n);
char *find_n_phonemes(char str[],int n);
mvm *mvm_init(void);
void mvm_insert(mvm* m, char* key, char* data);
char *search_map_one(mvm *m,char *key);
char *search_map_two(mvm* m, char* key, int* n);
void search(mvm *map_one, mvm *map_two,char *key);

int main(void)
{
    read_in("cmudict.txt",4);
    return 0;
}


void read_in(char *filename, int n)
{
    char str1[50] = {'\0'};
    char str2[100] = {'\0'};
    char *str3;
    FILE *fp;
    int i,j,k;
    mvm *map_one = mvm_init();
    mvm *map_two = mvm_init();
    if((fp=fopen(filename,"r"))==NULL){
        fprintf(stderr,"failed to open file...\n");
        exit(EXIT_FAILURE);
    }
    while(!feof(fp)){

        j = 0;
        while((i= getc(fp))!='#'&& i != EOF){
            str1[j++] = i;
        }
        k = 0;
        while((i = getc(fp))!='\n'&& i != EOF){
            str2[k++]= i;
        }
        str3= find_n_phonemes(str2,n);

        mvm_insert(map_one, str1, str3);
        mvm_insert(map_two, str3, str1);

        reinit_array(str1,strlen(str1));
        reinit_array(str2,strlen(str2));
    }

    search(map_one,map_two,"PASSING");

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
    mvmcell *cell = (mvmcell *)calloc(1,sizeof(mvmcell));
    if(m==NULL||key == NULL||data ==NULL){
        return;
    }
    /*before strcpy, we must malloc or calloc to cell->data etc!*/
    cell->data = calloc(50, sizeof(char));
    cell->key = calloc(50, sizeof(char));
    strcpy(cell->key,key);
    strcpy(cell->data,data);
    cell->next = m->head;
    m->head = cell;
    m->numkeys++;
}

void search(mvm *map_one, mvm *map_two,char *key)
{
    char *phonemes;
    char *words;
    int n;
    phonemes = search_map_one(map_one,key);
    words = search_map_two(map_two,phonemes,&n);
    printf("%s\n",words);
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


char* search_map_two(mvm* m, char* key, int* n)
{
    if(m !=NULL&& key!=NULL&&n != NULL){
        char *a;
        int offset = 0;
        mvmcell *temp = m->head;
        *n = 0;
        a = (char *)calloc(2000, sizeof(char));

        while(temp!=NULL){
            if(strcmp(temp->key,key)==0){
                offset += sprintf(a+offset,"%s, ",temp->data);
                temp = temp->next;
            }
            temp = temp ->next;
        }
        return  a;
    }
    return NULL;
}