#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "mvm.h"

#define DEFAULTSIZE  20
#define REQUIRED 2 /*required arguments in command line*/
#define OFFSET 1

#define strsame(A,B) (strcmp((A),(B))==0)
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

void check_argc(int argc);
void init_program(Program *p);
void free_program(Program *p);

void input_in_array(Program *p,char *filename);
void whether_print(FILE *fp,Program *p);
void read_print_content(FILE *fp,Program *p);
void interp_print(Program *p);

void parse_set_variable(Program *p,mvm *m);
void parse_ifcondition(Program *p,mvm *m);
void parse_jump(Program *p);
void parse_file(Program *p);

void Prog(Program *p,mvm *m);
void Instrs(Program *p,mvm *m);
void Instruct(Program *p,mvm *m);

int main(int argc,char **argv)
{

    Program p;
    int i;
    mvm *m;

    check_argc(argc);
    m = mvm_init();
    init_program(&p);
    
    input_in_array(&p,argv[OFFSET]);

    printf("p.count = %d\n",p.count);
    for(i=0;i<p.count;i++){
        printf("%s\n",p.array[i]);
    }

    Prog(&p,m);
    printf("Parsed OK!\n");

    free_program(&p);
    mvm_free(&m);

    return 0;
}

void init_program(Program *p)
{
    p->cw=0;
    p->count=0;
    p->array = (char **)malloc(sizeof(char *));
    p->array[p->count]= (char *)calloc(DEFAULTSIZE, sizeof(char));
    if(p->array==NULL ||p->array[p->count]==NULL){
        ERROR("Cannot allocate memory");
    }
}
void check_argc(int argc)
{
    if(argc<REQUIRED){
        ERROR("Too few arguments in command line");
    }
    if(argc>REQUIRED){
        ERROR("Too many arguments in command line");
    }
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
        if(strlen(p->array[p->count])>=19){
            ERROR("");
        }
        whether_print(fp,p);
        p->count++;
        p->array = (char **)realloc(p->array,(p->count+OFFSET)*sizeof(char*));
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        if(p->array==NULL){
            ERROR("ERROR");
        }
    }
    fclose(fp);
}
void whether_print(FILE *fp,Program *p)
{
    if(!strsame(p->array[p->count],"PRINT")&&!strsame(p->array[p->count],"PRINTN")){
        return;
    }
    p->count++;
    p->array = (char **)realloc(p->array,(p->count+OFFSET)*sizeof(char*));
    if(p->array==NULL){
        ERROR("Cannot allocate memory");
    }
    read_print_content(fp,p);

}
void read_print_content(FILE *fp,Program *p) /*想办法，保证，后"or 后# 的出现*/
{
    int c;
    int i=0;
    char *str = (char *)calloc(2,sizeof(char));

    while((c=getc(fp)) != '\"'&& c != '#'&& c !='%'&&c!='$' ){
        if(c != ' '){
            ERROR("Expect \" or # or % or $ after PRINT or PRINTN ");
        }
    };

    str[i++] =c;
    if(c == '%' ||c == '$'){
        while((c=getc(fp))!=' '&& c!= '\n'&& c!=EOF){
            str = (char *)realloc(str,(strlen(str)+2)* sizeof(char));
            str[i++]=c;
            str[i]='\0';
        }
        p->array[p->count] = str;
        return ;
    }
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

void Prog(Program *p,mvm *m)
{
    if(!strsame(p->array[p->cw],"{")){
        ERROR("Cannot find { in beginning of file\n");
    }
    p->cw++;
    Instrs(p,m);
}

void Instrs(Program *p,mvm *m)
{
    if(strsame(p->array[p->cw],"}")){
        return;
    }
    Instruct(p,m);
    p->cw++;
    Instrs(p,m);
}

void Instruct(Program *p,mvm *m)
{
    if(strsame(p->array[p->cw],"PRINT")||strsame(p->array[p->cw],"PRINTN")){
        p->cw++;
        #ifdef INTERP
        interp_print(p);
        #endif
        return;
    }
    if(p->array[p->cw][0]=='%' || p->array[p->cw][0] == '$'){
        parse_set_variable(p,m);
        return;
    }
    if(strsame(p->array[p->cw],"IFEQUAL")||strsame(p->array[p->cw],"IFGREATER")){
        parse_ifcondition(p,m);
        p->cw++;
        Prog(p,m);
        return;
    }
    if(strsame(p->array[p->cw],"JUMP")){
        parse_jump(p);
        return;
    }
    if(strsame(p->array[p->cw],"FILE")){

    }
    ERROR("Undefined instruction");
}

/*void check_print()
{

}*/


void parse_set_variable(Program *p,mvm *m)
{
    int i;
    int temp;
    int number=0;
    temp = p->cw;
    for(i=1;i<(int)strlen(p->array[p->cw]);i++){
        if(p->array[p->cw][i]<'A'|| p->array[p->cw][i]>'Z'){
            ERROR("Variable name must be [A-Z]+");
        }
    }
    if(p->array[p->cw][0]=='$'){/*如果是多次声明呢？*/
        mvm_insert(m,"STRVAR",p->array[p->cw++]);
    }else{
        mvm_insert(m,"NUMVAR",p->array[p->cw++]);
    }
    if(!strsame(p->array[p->cw++],"=")){
        ERROR("Expect a \"=\" after a variable when setting")
    }
    if(p->array[temp][0]=='$'){
        if(p->array[p->cw][0]!='\"'){
            ERROR("Expect a \"" );
        }
        if(p->array[p->cw][strlen(p->array[p->cw])-1] !='\"'){
            ERROR("Expect a \"" );
        }
    }else{
        for(i=0;i<(int)strlen(p->array[p->cw]);i++){
            if(p->array[p->cw][i] != '.'&&!(p->array[p->cw][i]>'0'&&p->array[p->cw][i]<'9')){
                ERROR("Expect only digit and . ");
            }
            if(p->array[p->cw][i] == '.'){
                number++;
            }
            if(number>1){
                ERROR("Only one . should have");
            }
        }
    }
}

void parse_ifcondition(Program *p,mvm *m)
{
    int i;
    int number = 0;
    p->cw++;
    if(!strsame(p->array[p->cw++],"(")){
        ERROR("Expect a \"=\" after a variable when setting")
    }
    if(p->array[p->cw][0]=='$'){
        if(mvm_search(m,"STRVAR")==NULL){
            ERROR("Use before declaim");
        }
        p->cw++;
        if(!strsame(p->array[p->cw++],",")){
            ERROR("Expect a , here");
        }
        if(p->array[p->cw][0]!='\"'){
            ERROR("Expect a \"" );
        }
        if(p->array[p->cw][strlen(p->array[p->cw])-1] !='\"'){
            ERROR("Expect a \"" );
        }
    }else if(p->array[p->cw][0]=='%'){
        if(mvm_search(m,"NUMVAR")==NULL){
            ERROR("Use before declaim");
        }
        p->cw++;
        if(strsame(p->array[p->cw++],",")){
            ERROR("Expect a , here");
        }
        for(i=0;i<(int)strlen(p->array[p->cw]);i++){
            if(p->array[p->cw][i] != '.'&&!(p->array[p->cw][i]>'0'&&p->array[p->cw][i]<'9')){
                ERROR("Expect only digit and . ");
            }
            if(p->array[p->cw][i] == '.'){
                number++;
            }
            if(number>1){
                ERROR("Only one . should have");
            }
        }

    }else{
        ERROR("Wrong variable name");
    }

    p->cw++;
    if(!strsame(p->array[p->cw],")")){
        ERROR("Expect a )");
    }


}

void parse_jump(Program *p)
{
    int i;
    p->cw++;
    for(i=0;i<(int)strlen(p->array[p->cw]);i++){
        if(p->array[p->cw][i]<'0'||p->array[p->cw][i]>'9'){
            ERROR("Expect only digit after JUMP");
        }
    }
}

void parse_file(Program *p)
{
    p->cw++;
    if(p->array[p->cw][0]!='\"'){
        ERROR("Expect a \"" );
    }
    if(p->array[p->cw][strlen(p->array[p->cw])-1] !='\"'){
        ERROR("Expect a \"" );
    }
}
void interp_print(Program *p)
{
    printf("%s",p->array[p->cw]);

}





