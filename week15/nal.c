#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#include <math.h>
#include "mvm.h"

#define DEFAULTSIZE  20
#define REQUIRED 2 /*required arguments in command line*/
#define OFFSET 1
#define FIRST 0
#define SECOND 1
#define TWO 2
#define RNDBASE 100
#define ROT13 13
#define ROT5 5
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

typedef struct program{
    char **array;
    mvm *map;
    int count;
    int cw;
} Program;

void init_program(Program *p);
void free_program(Program *p);
void check_argc(int argc);
void check_allocate(char *str);
void resize_array(Program *p);


void input_in_array(Program *p,char *filename);
void whether_print(FILE *fp,Program *p); /*要说明 是为了 space才这么复杂的处理*/
void whether_setvar(FILE *fp,Program *p);
void whether_ifcondition(FILE *fp,Program *p);
void whether_file(FILE *fp, Program *p);
void read_varcon(FILE *fp,Program *p);
void read_var_or_numcon(FILE *fp,char *str,Program *p,int i);
void read_strcon(FILE *fp,char *str,Program *p,int i,char flag);

void interp_print(Program *p);

void parse_file(Program *p);
void parse_in2str(Program *p);
void parse_innum(Program *p);
void parse_jump(Program *p);
void parse_print(Program *p);
void parse_rnd(Program *p);
void parse_ifcondition(Program *p);
void parse_inc(Program *p);
void parse_set_variable(Program *p,char flag);

void check_mark(Program *p, char* mark); /*把check函数 变成 传递对应的东西，而不是p*/
void check_strcon(Program *p);
void check_numcon(Program *p);
void check_var(Program *p,char flag);

void interp_set_var(Program *p);
void interp_rnd(Program *p);
void interp_innum(Program *p);
void interp_in2str(Program *p);
void interp_file(Program *p);
void interp_jump (Program *p);
void interp_inc (Program *p);
void interp_ifcondition(Program *p);

void not_meet(Program *p);
char *take_quota(char *content);
char *translate_hashes(char *content);



void Prog(Program *p);
void Instrs(Program *p);
void Instruct(Program *p);

int main(int argc,char **argv)
{

    Program p;
  /*  int i;*/
    char *str;

    check_argc(argc);

    init_program(&p);

    input_in_array(&p,argv[SECOND]);

/*    printf("p.count = %d\n",p.count);
    for(i=0;i<p.count;i++){
        printf("%s\n",p.array[i]);
    }*/
    #ifdef INTERP
    srand((unsigned)time(NULL));
    #endif
    Prog(&p);
    printf("Parsed OK!\n");

 str = mvm_print(p.map);
    printf("%s\n",str);
    free(str);

    free_program(&p);
    return 0;
}

void init_program(Program *p)
{
    p->cw=0;
    p->count=0;
    p->map = mvm_init();
    p->array = (char **)malloc(sizeof(char *));
    if(p->array==NULL){
        ERROR_1("Cannot allocate memory");
    }
    p->array[p->count]= (char *)calloc(DEFAULTSIZE, sizeof(char));
    if(p->array[p->count]==NULL){
        ERROR_1("Cannot allocate memory");
    }
}
void free_program(Program *p)
{
    int i;
    for(i=0;i<p->count+OFFSET;i++){
        free(p->array[i]);
    }
    free(p->array);
    mvm_free(&(p->map));

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
void check_allocate(char *str)
{
    if(str==NULL){
        ERROR_1("Cannot allocate memory");
    }
}
void resize_array(Program *p)
{
    p->array = (char **)realloc(p->array,(p->count+OFFSET)*sizeof(char*));
    if(p->array==NULL){
        ERROR_1("Cannot allocate memory");
    }
}

void input_in_array(Program *p,char *filename)
{
    FILE *fp;
    if( !(fp = fopen(filename,"r"))){
        ERROR_1("Cannot open file");
    }
    while(fscanf(fp,"%s",p->array[p->count])==1){
        if(strlen(p->array[p->count])>=DEFAULTSIZE-OFFSET){
            ERROR_2("This instruction's length should be less than 19",\
            p->array[p->count],p->count);
        }
        whether_print(fp,p);
        whether_setvar(fp,p);
        whether_ifcondition(fp,p);
        whether_file(fp,p);
        p->count++;
        resize_array(p);
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        check_allocate(p->array[p->count]);
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
    if(p->array[p->count][0]!='$'&&p->array[p->count][0]!='%'){
        return;
    }

    p->count++;
    resize_array(p);
    p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    check_allocate(p->array[p->count]);

    if(fscanf(fp,"%s",p->array[p->count])!=1){
        ERROR_1("Need a closing } to finish file");
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
        check_allocate(p->array[p->count]);
        if(fscanf(fp,"%s",p->array[p->count])!=1){
            ERROR_1("Need a closing } to finish file");
        }
        p->count++;
        resize_array(p);
        read_varcon(fp,p);
    }
}
void whether_file(FILE *fp, Program *p) /*可以用read_varcon吗,可以，之后再*/
{
    if(!strsame(p->array[p->count],"FILE")){
        return;
    }
    p->count++;
    resize_array(p);
    read_varcon(fp,p);
}
void read_varcon(FILE *fp,Program *p)
{
    int c;
    int i = FIRST;
    char *str = (char *)calloc(TWO,sizeof(char));
    check_allocate(str);

    while((c=getc(fp))==' '&& c != EOF);
    if(c==EOF){
        ERROR_1("Expect beginning \" or # or % or $ or digit to start VARCON");
    }
    str[i++] =c;
    if(c == '%' ||c == '$'||(c>='0'&&c<='9')||c == '.'){
        read_var_or_numcon(fp,str,p,i);
        /*free(str);*/
        /*不需要再free str 因为 指针指向的是堆，当read_var_or_num函数中reallocate，原来这块地方已经free了*/
    }else if(c=='#'||c == '\"'){
        read_strcon(fp,str,p,i,c);
    }else{
        ERROR_1("Illegal input for VARCON");
    }
}
void read_var_or_numcon(FILE *fp,char *str,Program *p,int i)
{
    int c;
    while((c=getc(fp))!=' '&& c!= '\n'&& c!=EOF){
        str = (char *)realloc(str,(strlen(str)+TWO)* sizeof(char));
        check_allocate(str);
        str[i++]=c;
        str[i]='\0';
    }
    p->array[p->count] = str;

}
void read_strcon(FILE *fp,char *str,Program *p,int i,char flag)
{
    int c;
    while((c=getc(fp))!= '\"'&&c != '#' && c!=EOF){
        str = (char *)realloc(str,(strlen(str)+TWO)* sizeof(char));
        check_allocate(str);
        str[i++]=c;
        str[i]='\0';
    }
    if(c != flag){
        ERROR_1("Expect a matched closing \" or # to finish CON");
    }
    str = (char *)realloc(str,(strlen(str)+TWO)* sizeof(char));
    check_allocate(str);
    str[i++]=c;
    str[i]='\0';
    p->array[p->count] = str;
}

void Prog(Program *p)
{
    if(!strsame(p->array[p->cw],"{")){
        ERROR_2("Cannot find { in beginning of file",p->array[p->cw],p->cw);
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

    if(strsame(p->array[p->cw],"FILE")){
        parse_file(p);
        return;
    }
    if(strsame(p->array[p->cw],"ABORT")){
        #ifdef INTERP
        printf("Interpreted OK\n");
        exit(0);
        #endif
        return;
    }
    if(strsame(p->array[p->cw],"IN2STR")){
        parse_in2str(p);
        return;
    }
    if(strsame(p->array[p->cw],"INNUM")){
        parse_innum(p);
        return;
    }
    if(strsame(p->array[p->cw],"JUMP")){
        parse_jump(p);
        return;
    }
    if(strsame(p->array[p->cw],"PRINT")||strsame(p->array[p->cw],"PRINTN")){
        parse_print(p);
        #ifdef INTERP
        interp_print(p);
        #endif
        return;
    }
    if(strsame(p->array[p->cw],"RND")){
        parse_rnd(p);
        return;
    }
    if(strsame(p->array[p->cw],"IFEQUAL")||strsame(p->array[p->cw],"IFGREATER")){
        parse_ifcondition(p);
/*        p->cw++;
        Prog(p);*/
        return;
    }
    if(strsame(p->array[p->cw],"INC")){
        parse_inc(p);
        return;
    }
    if(p->array[p->cw][FIRST]=='%' || p->array[p->cw][FIRST] == '$'){
        parse_set_variable(p,p->array[p->cw][FIRST]);
        return;
    }

    ERROR_2("Undefined instruction",p->array[p->cw],p->cw);
}

void check_mark(Program *p, char* mark)
{
    p->cw++;
    if(!strsame(p->array[p->cw],mark)){
        fprintf(stderr,"Expect a \"%s\" here: %s(WORD %d) in %s, line %d\n",mark,p->array[p->cw],p->cw,__FILE__,__LINE__);
        exit(2);
    }
}
void check_strcon(Program *p)
{
    int len = (int)strlen(p->array[p->cw]);
    if(p->array[p->cw][FIRST]=='\"'){
        if(p->array[p->cw][len-OFFSET]!='\"'){
            ERROR_2("Expect a closing \" to finish STRCON",p->array[p->cw],p->cw);
        }
    }else if(p->array[p->cw][FIRST]=='#'){
        if(p->array[p->cw][len-OFFSET]!='#'){
            ERROR_2("Expect a closing # to finish STRCON",p->array[p->cw],p->cw);
        }
    }else{
        ERROR_2("Expect a beginning \" or # to start STRCON",p->array[p->cw],p->cw);
    }
}
void check_numcon(Program *p)
{
    int len = (int)strlen(p->array[p->cw]);
    int i;
    int flag=0;
    for(i=0;i<len;i++){
        if((p->array[p->cw][i]<'0'||p->array[p->cw][i]>'9')&&p->array[p->cw][i]!='.'){
            ERROR_2("Expect only digit or . in NUMCON",p->array[p->cw],p->cw);
        }
        if(p->array[p->cw][i] =='.'){
            flag++;
        }
        if(flag>1){
            ERROR_2("No more than 1 dot in NUMCON",p->array[p->cw],p->cw);
        }
    }
}
void check_var(Program *p,char flag)
{
    int len = (int)strlen(p->array[p->cw]);
    int i;
    if(p->array[p->cw][FIRST] != flag){
        ERROR_2("Expect a matched \"%\" or \"$\" to start VAR",p->array[p->cw],p->cw);
    }
    for(i=1;i<len;i++){
        if(p->array[p->cw][i]<'A'||p->array[p->cw][i]>'Z'){
            ERROR_2("Expect only [A-Z]+ in VAR",p->array[p->cw],p->cw);
        }
    }
}

void parse_file(Program *p) /*其他情况 已经在读文件时候考虑了*/
{
    p->cw++;
    check_strcon(p);
    #ifdef INTERP
    interp_file(p);
    #endif
}



void parse_in2str(Program *p)
{
    check_mark(p,"(");
    p->cw++;
    check_var(p,'$');
    check_mark(p,",");
    p->cw++;
    check_var(p,'$');
    check_mark(p,")");
    #ifdef INTERP
    interp_in2str(p);
    #endif
}
void parse_innum(Program *p)
{
    check_mark(p,"(");
    p->cw++;
    check_var(p,'%');
    check_mark(p,")");
    #ifdef INTERP
    interp_innum(p);
    #endif
}
void parse_jump(Program *p)
{
    int i;
    int len;
    p->cw++;
    check_numcon(p);
    len = (int)strlen(p->array[p->cw]);
    for(i=0;i<len;i++){
        if(p->array[p->cw][i]=='.'){
            ERROR_2("Must be a INT NUM after JUMP",p->array[p->cw],p->cw);
        }
    }
#ifdef INTERP
    interp_jump(p);
#endif
}
void parse_print(Program *p)
{
    char flag;
    p->cw++;
    flag = p->array[p->cw][FIRST];
    if(flag =='%'){
        check_var(p,'%');
    }else if (flag == '$'){
        check_var(p,'$');
    }else if (flag == '\"' || flag == '#'){
        check_strcon(p);
    }else{
        check_numcon(p);
    }
}
void parse_rnd(Program *p)/*和parse_innum 一样*/
{
    check_mark(p,"(");
    p->cw++;
    check_var(p,'%');
    check_mark(p,")");
    #ifdef INTERP
    interp_rnd(p);
    #endif
}
void parse_ifcondition(Program *p)
{
    char flag;
    check_mark(p,"(");
    p->cw++;
    flag = p->array[p->cw][FIRST];
    if(flag =='%'){
        check_var(p,'%');
    }else if (flag == '$'){
        check_var(p,'$');
    }else if (flag == '\"' || flag == '#'){
        check_strcon(p);
    }else{
        check_numcon(p);
    }
    check_mark(p,",");
    p->cw++;
    flag = p->array[p->cw][FIRST];
    if(flag =='%'){
        check_var(p,'%');
    }else if (flag == '$'){
        check_var(p,'$');
    }else if (flag == '\"' || flag == '#'){
        check_strcon(p);
    }else{
        check_numcon(p);
    }
    check_mark(p,")");
#ifdef INTERP
    interp_ifcondition(p);
#endif
}

void interp_ifcondition(Program *p)
{
    char flag;
    int mark_1;
    int mark_2;
    char *str0;
    char *str1;
    char *str2;
    float num1;
    float num2;
    int success = 0;
    p->cw = p->cw -OFFSET - TWO - TWO;
    str0 = p->array[p->cw];
    p->cw = p->cw + TWO;
    flag = p->array[p->cw][FIRST];
    if(flag =='%'){
        mark_1 = 0;
        str1 = mvm_search(p->map,p->array[p->cw]);
        if(str1 == NULL){
            ERROR_2("Please define VAR before using",p->array[p->cw],p->cw);
        }
    }else if (flag == '$'){
        mark_1 = 1;
        str1 = mvm_search(p->map,p->array[p->cw]);
        if(str1 == NULL){
            ERROR_2("Please define VAR before using",p->array[p->cw],p->cw);
        }
        str1 = take_quota(str1);
    }else if (flag == '\"' || flag == '#'){
        mark_1 = 1;
        str1 = p->array[p->cw];
        str1 = take_quota(str1);
    }else{
        mark_1 = 0;
        str1 = p->array[p->cw];
    }

    p->cw = p->cw +TWO;
    flag = p->array[p->cw][FIRST];
    if(flag =='%'){
        mark_2 = 0;
        str2 = mvm_search(p->map,p->array[p->cw]);
        if(str2 == NULL){
            ERROR_2("Please define VAR before using",p->array[p->cw],p->cw);
        }
    }else if (flag == '$'){
        mark_2 = 1;
        str2 = mvm_search(p->map,p->array[p->cw]);
        if(str2 == NULL){
            ERROR_2("Please define VAR before using",p->array[p->cw],p->cw);
        }
        str2 = take_quota(str2);
    }else if (flag == '\"' || flag == '#'){
        mark_2 = 1;
        str2 = p->array[p->cw];
        str2 = take_quota(str2);
    }else{
        mark_2 = 0;
        str2 = p->array[p->cw];
    }
    if(mark_2 != mark_1){
        ERROR_2("The types in IFCOND is not matched",p->array[p->cw],p->cw);
    }

    if(strsame(str0,"IFEQUAL") && mark_1 == 0){
        num1 = atof(str1);
        num2 = atof(str2);
        if(fabs((double)(num1-num2))<=0.0005){
            success = 1;
        }else{
            success = 0;
        }
    }else if (strsame(str0,"IFEQUAL") && mark_1 == 1){
        if(strsame(str1,str2)){
            success = 1;
        }else{
            success = 0;
        }
        free(str1);
        free(str2);
    }else if (strsame(str0,"IFGREATER") && mark_1 == 0){
        num1 = atof(str1);
        num2 = atof(str2);
        if(fabs((double)(num1-num2))>0.0005 && num1 > num2){
            success = 1;
        }else{
            success = 0;
        }
    }else if (strsame(str0,"IFGREATER") && mark_1 == 1){
        ERROR_2("Cannot compare str in IFGREATER",p->array[p->cw],p->cw);
    }

    if(success == 1){
        p->cw = p->cw + TWO;
        Prog(p);
    }else{
        p->cw = p->cw + TWO;
        not_meet(p);
    }

}

void not_meet(Program *p) /*不能嵌套判断*/
{
    while(!strsame(p->array[p->cw],"}")){
        p->cw++;
    }
}





void parse_inc(Program *p)/*和parse_innum,parse_rnd 一样*/
{
    check_mark(p,"(");
    p->cw++;
    check_var(p,'%');
    check_mark(p,")");
#ifdef INTERP
    interp_inc(p);
#endif
}
void parse_set_variable(Program *p,char flag)
{
    check_var(p,flag);
    check_mark(p,"=");
    p->cw++;
    if(flag == '%'){
        check_numcon(p);
    }else{
        check_strcon(p);
    }
    #ifdef INTERP
    interp_set_var(p);
    #endif
}


void interp_print(Program *p)
{
    int flag = 0;
    char *str;
    char tempc = p->array[p->cw][FIRST];
    char *temps;
    if( tempc == '%'){
        str = mvm_search(p->map,p->array[p->cw]);
        if(str == NULL){
            ERROR_2("Please define variable before using",p->array[p->cw],p->cw);
        }
        flag = 1;
    }else if (tempc == '$'){
        temps = mvm_search(p->map,p->array[p->cw]);
        if(temps == NULL){
            ERROR_2("Please define variable before using",p->array[p->cw],p->cw);
        }
        str = take_quota(temps);
    }else {
        str = take_quota(p->array[p->cw]);
    }
    temps = p->array[p->cw-OFFSET];
    if(strsame(temps,"PRINT")){
        printf("%s\n",str);
    }else{
        printf("%s",str);
    }
    if(flag == 0){
        free(str);
    }
}
 char *take_quota(char *content)
 {
    char *str,*temp;
    int i,j;
    int len = strlen(content);
    str = (char *)calloc(len+OFFSET,sizeof(char));
    check_allocate(str);
    if(content[FIRST]=='#'){
        temp = translate_hashes(content);
        for(i=0,j=1;i<len-TWO;i++,j++){
            str[i]=temp[j];
        }
        free(temp);
        return str;
    }else if (content[FIRST]=='\"'){
        for(i=0,j=1;i<len-TWO;i++,j++){
            str[i]=content[j];
        }
    }else{
        for(i=0;i<len;i++){
            str[i]=content[i];
        }
    }

     return str;
 }
char *translate_hashes(char *content)
{
    char *str;
    int i;
    int len = strlen(content);
    char temp;
    str = (char *)calloc(len+OFFSET,sizeof(char));
    check_allocate(str);
    for(i=0;i<len;i++)
    {
        temp = content[i];
        if(temp == '#'){
            str[i] = '\"';
        }else if((temp >= 'a'&& temp <'n')||(temp >= 'A'&& temp <'N')){
            str[i] = temp +ROT13;
        }else if((temp >= 'n'&& temp <= 'z')||(temp >= 'N'&& temp <= 'Z')) {
            str[i] = temp -ROT13;
        }else if (temp >= '0' && temp < '5') {
            str[i] = temp + ROT5;
        }else if (temp >= '5' && temp <= '9'){
            str[i] = temp -ROT5;
        }else{
            str[i] = temp;
        }
    }
    return str;
}


void interp_set_var(Program *p)
{
    p->cw = p->cw - TWO;
    if(mvm_search(p->map,p->array[p->cw]) != NULL){
        mvm_delete(p->map,p->array[p->cw]);
    }
    mvm_insert(p->map,p->array[p->cw],p->array[p->cw+TWO]);
    p->cw = p->cw + TWO;
}
void interp_rnd(Program *p)
{
    char *data;
    int random;
    p->cw--;
    data = (char *)calloc(3,sizeof(char));
    if(data == NULL){
        ERROR_1("Failed to allocate memory");
    }
    random = rand() % RNDBASE;
    sprintf(data,"%d",random);
    if(mvm_search(p->map,p->array[p->cw]) != NULL){
        mvm_delete(p->map,p->array[p->cw]);
    }
    mvm_insert(p->map,p->array[p->cw],data);
    free(data);
    p->cw++;
}

void interp_innum(Program *p) /*怎么处理可能的越界,能否直接读一个str 而不是 float,然后判断str合不合法*/
{
    /*float number;*/
    char *data;
    int len;
    int i;
    int flag=0;
    data = (char *)calloc(DEFAULTSIZE*TWO,sizeof(char));
    p->cw--;
    if(scanf("%s",data)!=1){
        ERROR_2("Need input a float number",p->array[p->cw],p->cw);
    }
    /*sprintf(data,"%f",number);*/
    if(data[DEFAULTSIZE*TWO-OFFSET] !='\0'){
        ERROR_2("Scanned Float Number is too long, if you really need, "\
                "please manually increase the allocated memory",p->array[p->cw-OFFSET],p->cw-OFFSET);
    }
    len = strlen(data);

    for(i=0;i<len;i++){
        if((data[i]<'0'||data[i]>'9')&&data[i]!='.'){
            ERROR_2("Expect only digit or . in NUM",p->array[p->cw],p->cw);
        }
        if(data[i] =='.'){
            flag++;
        }
        if(flag>1){
            ERROR_2("No more than 1 dot in NUM",p->array[p->cw],p->cw);
        }
    }

    if(mvm_search(p->map,p->array[p->cw]) != NULL){
        mvm_delete(p->map,p->array[p->cw]);
    }
    mvm_insert(p->map,p->array[p->cw],data);
    free(data);
    p->cw++;
}

void interp_in2str(Program *p)/*怎么改成动态的*/
{
    char *str1 = calloc(DEFAULTSIZE*TWO,sizeof(char));
    char *str2 = calloc(DEFAULTSIZE*TWO,sizeof(char));
    if(scanf("%s %s",str1,str2)!=2){
        ERROR_2("Need input two strings",p->array[p->cw],p->cw);
    }
    if(str1[DEFAULTSIZE*TWO-OFFSET] !='\0'){
        ERROR_2("Scanned String is too long, if you really need, "\
                "please manually increase the allocated memory",p->array[p->cw-OFFSET-TWO],p->cw-OFFSET-TWO);
    }
    if(str2[DEFAULTSIZE*2-OFFSET] !='\0'){
        ERROR_2("Scanned String is too long, if you really need, "\
                "please manually increase the allocated memory",p->array[p->cw-OFFSET],p->cw-OFFSET);
    }
    p->cw = p->cw -3;
    if(mvm_search(p->map,p->array[p->cw]) != NULL){
        mvm_delete(p->map,p->array[p->cw]);
    }
    mvm_insert(p->map,p->array[p->cw],str1);
    p->cw = p->cw + 2;
    if(mvm_search(p->map,p->array[p->cw]) != NULL){
        mvm_delete(p->map,p->array[p->cw]);
    }
    mvm_insert(p->map,p->array[p->cw],str2);
    free(str1);
    free(str2);
    p->cw++;
}

void interp_file(Program *p)
{
    Program p2;
    int i;
    char *filename = take_quota(p->array[p->cw]);
    init_program(&p2);
    mvm_free(&(p2.map));
    p2.map = p->map;
    input_in_array(&p2,filename);
    free(filename);
/*    printf("p2.count = %d\n",p2.count);
    for(i=0;i<p2.count;i++){
        printf("%s\n",p2.array[i]);
    }*/
    Prog(&p2);

    for(i=0;i<p2.count+OFFSET;i++){
        free(p2.array[i]);
    }
    free(p2.array);
/*
    free_program(&p2);*//*不能free mvm*/
}


void interp_jump (Program *p)
{
    int number = atoi(p->array[p->cw]);
    p->cw = number - OFFSET;
}
/*
void str2num (char *content)
{

}*/

void interp_inc (Program *p)
{
    float number;
    char *temp;
    p->cw--;
    temp = mvm_search(p->map,p->array[p->cw]);
    if(temp == NULL){
        ERROR_2("Please define var before using",p->array[p->cw],p->cw);
    }
    number = atof(temp);
    number = number + OFFSET;
    temp = (char *)calloc(DEFAULTSIZE*2,sizeof(char));
    if(temp[DEFAULTSIZE*TWO-OFFSET] !='\0'){
        ERROR_2("Increasing number is out of bound",p->array[p->cw],p->cw);
    }
    sprintf(temp,"%f",number);
    mvm_delete(p->map,p->array[p->cw]);
    mvm_insert(p->map,p->array[p->cw],temp);
    free(temp);
    p->cw++;
}
