#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>


#define DEFAULTSIZE  20
#define OFFSET 1

#define strsame(A,B) \
(strcmp((A),(B))==0)
#define ERROR(PHRASE) {\
fprintf(stderr,"Fatal Error: %s occured in %s, line %d\n",\
PHRASE,__FILE__,__LINE__);\
exit(2);\
}

struct program{
    char **array;
    int count;
    int cw;
};

typedef struct program Program;


void init_program(Program *p);
void free_program(Program *p);

void input_in_array(Program *p,char *filename);
void read_print_content(FILE *fp,Program *p);
void interp_print(Program *p);

void Prog(Program *p);
void Instrs(Program *p);
void Instruct(Program *p);

int main(int argc,char **argv)
{

    Program p;
    if(argc != 2 ){
        ERROR("Required one and only one file name in command line")
    }

    init_program(&p);
    input_in_array(&p,argv[OFFSET]);
/*
    printf("p.count = %d\n",p.count);
    for(i=0;i<p.count;i++){
        printf("%s\n",p.array[i]);
    }
*/


    Prog(&p);
    printf("Parsed OK!\n");

    free_program(&p);

    return 0;
}

void init_program(Program *p)
{
    p->cw=0;
    p->count=0;
    p->array = (char **)malloc(sizeof(char *));
    p->array[p->count]= (char *)calloc(DEFAULTSIZE, sizeof(char));
}

void free_program(Program *p)
{
    int i;
    for(i=0;i<p->count+OFFSET;i++){
        free(p->array[i]);
    }
    free(p->array);
}

void input_in_array(Program *p,char *filename)
{

    FILE *fp;
    if( !(fp = fopen(filename,"r"))){
        ERROR("Cannot open file");
    }

    while(fscanf(fp,"%s",p->array[p->count])==1){

        if(strsame(p->array[p->count],"PRINT")||strsame(p->array[p->count],"PRINTN")){
            p->count++;
            p->array = (char **)realloc(p->array,(p->count+1)*sizeof(char*));
            if(p->array==NULL){
                ERROR("ERROR");
            }
            read_print_content(fp,p);
        }
        p->count++;
        p->array = (char **)realloc(p->array,(p->count+1)*sizeof(char*));
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        if(p->array==NULL){
            ERROR("ERROR");
        }
    }
    fclose(fp);
}

void read_print_content(FILE *fp,Program *p) /*想办法，保证，后"or 后# 的出现*/
{
    int c=1;
    int i=0;
    char *str = (char *)calloc(2,sizeof(char));

    while((c=getc(fp)) != '\"'&& c != '#'&& c !='%'&&c!='$' ){
        if(c != ' '){
            ERROR("Expect \" or # or % or $ after PRINT or PRINTN ");
        }
    };

    if(c== '%' ||c== '$'){
        free(str);
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        fscanf(fp,"%s",p->array[p->count]);
        return ;
    }
    str[i++] =c;
    while((c=getc(fp))!='\"'&& c != '#'&& c!=EOF){
        str = (char *)realloc(str,(strlen(str)+2)* sizeof(char));
        str[i++]=c;
        str[i]='\0';
    }
    if(c == EOF){
        ERROR("Expect \" or # after PRINT or PRINTN ");
    }
    str = (char *)realloc(str,(strlen(str)+2)* sizeof(char));
    str[i++]=c;
    str[i]='\0';


    p->array[p->count] = str;

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
        #ifdef INTERP
        interp_print(p);
        #endif
        return;
    }
    ERROR("Expect content after PRINT");
}

/*void check_print()
{

}*/

void interp_print(Program *p)
{
    printf("%s",p->array[p->cw]);
}





