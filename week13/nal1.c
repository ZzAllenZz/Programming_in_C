#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "mvm.h"

#define DEFAULTSIZE  20
#define REQUIRED 2 /*required arguments in command line*/
#define OFFSET 1
#define TWO 2
#define strsame(A,B) (strcmp((A),(B))==0)
#define ERROR_1(PHRASE) {\
fprintf(stderr,"Fatal Error: %s occured in %s, line %d\n",\
PHRASE,__FILE__,__LINE__);\
exit(1);\
}
#define ERROR_2(EXPLAIN,WORD,NUMBER){\
fprintf(stderr,"%s: %s(WORD %d) in %s, line %d\n",\
EXPLAIN,WORD,NUMBER,__FILE__,__LINE__);\
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
void resize_array(Program *p);

void input_in_array(Program *p,char *filename);
void whether_print(FILE *fp,Program *p); /*要说明 是为了 space才这么复杂的处理*/
void whether_setvar(FILE *fp,Program *p);
void whether_ifcondition(FILE *fp,Program *p);
void read_varcon(FILE *fp,Program *p);
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
        ERROR_1("Cannot allocate memory");
    }
}
void check_argc(int argc)
{
    if(argc<REQUIRED){
        ERROR_1("Too few arguments in command line");
    }
    if(argc>REQUIRED){
        ERROR_1("Too many arguments in command line");
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
        ERROR_1("Cannot open file");
    }

    while(fscanf(fp,"%s",p->array[p->count])==1){
        if(strlen(p->array[p->count])>=19){
            ERROR_2("Instruction's length should be less than 19",p->array[p->count],p->count);
        }
        whether_print(fp,p);
        whether_setvar(fp,p);
        whether_ifcondition(fp,p);
        p->count++;
        resize_array(p);
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        if(p->array[p->count]==NULL){
            ERROR_1("ERROR");
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
    resize_array(p);
    read_varcon(fp,p);

}
void whether_setvar(FILE *fp,Program *p)
{
    if(p->array[p->count][0]!='$'){
        return;
    }

    p->count++;
    resize_array(p);
    p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    if(p->array[p->count]==NULL){
        ERROR_1("Cannot allocate memory");
    }

    if(fscanf(fp,"%s",p->array[p->count])!=1){
        ERROR_1("Need a closing { to finish file");
    }
    if(!strsame(p->array[p->count],"=")){
        return;
    }
    p->count++;
    resize_array(p);
    read_varcon(fp,p);
}
void whether_ifcondition(FILE *fp,Program *p)
{
    int i;
    if(!strsame(p->array[p->count],"IFEQUAL")&&!strsame(p->array[p->count],"IFGREATER")){
        return;
    }
    for(i=0;i<TWO;i++){
        p->count++;
        resize_array(p);
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        if(p->array[p->count]==NULL){
            ERROR_1("Cannot allocate memory");
        }
        if(fscanf(fp,"%s",p->array[p->count])!=1){
            ERROR_1("Need a closing { to finish file");
        }

        p->count++;
        resize_array(p);
        read_varcon(fp,p);
    }
}

void whether_file(FILE *fp, Program *p) /*可以用read_varcon吗*/
{
    if(!strsame(p->array[p->count],"FILE")){
        return;
    }
    p->count++;
    resize_array(p);
    read_varcon(fp,p);
}
void resize_array(Program *p)
{
    p->array = (char **)realloc(p->array,(p->count+OFFSET)*sizeof(char*));
    if(p->array==NULL){
        ERROR_1("Cannot allocate memory");
    }
}

void read_varcon(FILE *fp,Program *p) /*想办法，保证，后"or 后# 的出现,并且要对应*/
{
    int c;
    int i=0;
    char *str = (char *)calloc(TWO,sizeof(char));
    if(str==NULL){
        ERROR_1("Cannot allocate memory");
    }
    while((c=getc(fp)) != '\"'&& c != '#'&& c !='%'&&c!='$' ){
        if(c != ' '){
            ERROR_1("Expect beginning \" or # or % or $ here");
        }
    }
    str[i++] =c;
    if(c == '%' ||c == '$'){
        while((c=getc(fp))!=' '&& c!= '\n'&& c!=EOF){
            str = (char *)realloc(str,(strlen(str)+TWO)* sizeof(char));
            str[i++]=c;
            str[i]='\0';
        }
        p->array[p->count] = str;
        return ;
    }
    while((c=getc(fp))!='\"'&& c != '#'&& c!=EOF){
        str = (char *)realloc(str,(strlen(str)+TWO)* sizeof(char));
        str[i++]=c;
        str[i]='\0';
    }
    if(c == EOF){
        ERROR_1("Expect closing \" or # here ");
    }
    str = (char *)realloc(str,(strlen(str)+TWO)* sizeof(char));
    str[i++]=c;
    str[i]='\0';
    p->array[p->count] = str;
}

void Prog(Program *p,mvm *m)
{
    if(!strsame(p->array[p->cw],"{")){
        ERROR_1("Cannot find { in beginning of file\n");
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
    ERROR_1("Undefined instruction");
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
            ERROR_1("Variable name must be [A-Z]+");
        }
    }
    if(p->array[p->cw][0]=='$'){/*如果是多次声明呢？*/
        mvm_insert(m,"STRVAR",p->array[p->cw++]);
    }else{
        mvm_insert(m,"NUMVAR",p->array[p->cw++]);
    }
    if(!strsame(p->array[p->cw++],"=")){
        ERROR_1("Expect a \"=\" after a variable when setting")
    }
    if(p->array[temp][0]=='$'){
        if(p->array[p->cw][0]!='\"'){
            ERROR_1("Expect a \"" );
        }
        if(p->array[p->cw][strlen(p->array[p->cw])-1] !='\"'){
            ERROR_1("Expect a \"" );
        }
    }else{
        for(i=0;i<(int)strlen(p->array[p->cw]);i++){
            if(p->array[p->cw][i] != '.'&&!(p->array[p->cw][i]>'0'&&p->array[p->cw][i]<'9')){
                ERROR_1("Expect only digit and . ");
            }
            if(p->array[p->cw][i] == '.'){
                number++;
            }
            if(number>1){
                ERROR_1("Only one . should have");
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
        ERROR_1("Expect a \"=\" after a variable when setting")
    }
    if(p->array[p->cw][0]=='$'){
        if(mvm_search(m,"STRVAR")==NULL){
            ERROR_1("Use before declaim");
        }
        p->cw++;
        if(!strsame(p->array[p->cw++],",")){
            ERROR_1("Expect a , here");
        }
        if(p->array[p->cw][0]!='\"'){
            ERROR_1("Expect a \"" );
        }
        if(p->array[p->cw][strlen(p->array[p->cw])-1] !='\"'){
            ERROR_1("Expect a \"" );
        }
    }else if(p->array[p->cw][0]=='%'){
        if(mvm_search(m,"NUMVAR")==NULL){
            ERROR_1("Use before declaim");
        }
        p->cw++;
        if(strsame(p->array[p->cw++],",")){
            ERROR_1("Expect a , here");
        }
        for(i=0;i<(int)strlen(p->array[p->cw]);i++){
            if(p->array[p->cw][i] != '.'&&!(p->array[p->cw][i]>'0'&&p->array[p->cw][i]<'9')){
                ERROR_1("Expect only digit and . ");
            }
            if(p->array[p->cw][i] == '.'){
                number++;
            }
            if(number>1){
                ERROR_1("Only one . should have");
            }
        }

    }else{
        ERROR_1("Wrong variable name");
    }

    p->cw++;
    if(!strsame(p->array[p->cw],")")){
        ERROR_1("Expect a )");
    }


}

void parse_jump(Program *p)
{
    int i;
    p->cw++;
    for(i=0;i<(int)strlen(p->array[p->cw]);i++){
        if(p->array[p->cw][i]<'0'||p->array[p->cw][i]>'9'){
            ERROR_1("Expect only digit after JUMP");
        }
    }
}

void parse_file(Program *p)
{
    p->cw++;
    if(p->array[p->cw][0]!='\"'){
        ERROR_1("Expect a \"" );
    }
    if(p->array[p->cw][strlen(p->array[p->cw])-1] !='\"'){
        ERROR_1("Expect a \"" );
    }
}
void interp_print(Program *p)
{
    printf("%s",p->array[p->cw]);

}





