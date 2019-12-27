#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

/*#define MAXNUMTOKENS    100
#define MAXTTOKENSIZE   100*/
#define PROGRAM "test1.txt"
#define strsame(A,B) (strcmp(A,B)==0)
#define ERROR(PHRASE) {fprintf(stderr,"Fatal Error %s occured in %s, line %d\n",PHRASE,__FILE__,__LINE__);exit(2);}

struct program{
    char **array;
    int cw;
};

typedef struct program Program;

void input_in_array(Program *p,char *filename);
void read_print_content(FILE *fp,Program *p,int n);

void Prog(Program *p);
void Instrs(Program *p);
void Instruct(Program *p);

int main(int argc,char **argv)
{
    Program p;
    int i;
    p.cw=0;
    input_in_array(&p,argv[1]);
    for(i=0;i<26;i++){
        printf("%s\n",p.array[i]);
    }

/*    Prog(&p);*/
    printf("Parsed OK!\n");
    return 0;
}

void input_in_array(Program *p,char *filename)
{

    FILE *fp;
    int j=0;
    if( !(fp = fopen(filename,"r"))){
        fprintf(stderr,"Cannot open %s\n",filename);
        exit(2);
    }

  /*  p->cw = 0;*/

    p->array = (char **)malloc(sizeof(char *));
    p->array[j]= (char *)calloc(10, sizeof(char));

    while(fscanf(fp,"%s",p->array[j])==1){

        if(strsame(p->array[j],"PRINT")||strsame(p->array[j],"PRINTN")){
            j++;
            p->array = (char **)realloc(p->array,(j+1)*sizeof(char*));
            if(p->array==NULL){
                ERROR("ERROR");
            }
            read_print_content(fp,p,j);
        }
        j++;
        p->array = (char **)realloc(p->array,(j+1)*sizeof(char*));
        p->array[j] = (char *)calloc(10, sizeof(char));
        if(p->array==NULL){
            ERROR("ERROR");
        }
    }
    fclose(fp);
}

void read_print_content(FILE *fp,Program *p,int n) /*想办法，保证，后"or 后# 的出现*/
{
    int c;
    int i=0;
    char *str = (char *)calloc(1,sizeof(char));
    while((c=getc(fp))!='\"'&& c != '#'){
        if(c != ' '){
            ERROR("Expect \" or # after PRINT or PRINTN ");
        }
    };
    str[i++] =c;
    while((c=getc(fp))!='\"'&& c != '#'&& c!=EOF){
        str = (char *)realloc(str,(strlen(str)+1)* sizeof(char));
        str[i++]=c;
    }
    if(c == EOF){
        ERROR("Expect \" or # after PRINT or PRINTN ");
    }
    str = (char *)realloc(str,(strlen(str)+1)* sizeof(char));
    str[i++]=c;
    str = (char *)realloc(str,(strlen(str)+1)* sizeof(char));
    str[i++]='\0';

    p->array[n] = str;

}

void Prog(Program *p)
{
    if(!strsame(p->array[p->cw],"{")){
        ERROR("Cannot find { in begin...\n");
    }
    p->cw++;
    Instrs(p);
}

void Instrs(Program *p)
{
    if(strsame(p->array[p->cw],"}")){
        return;
    }
    Instruct(p);
    p->cw++;
    Instrs(p);
}

void Instruct(Program *p)
{
    if(strsame(p->array[p->cw],"PRINT")||strsame(p->array[p->cw],"PRINTN")){
        p->cw++;
        return;
    }
    ERROR("Expect content after PRINT");
}
