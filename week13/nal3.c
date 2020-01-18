#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<time.h>
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
void check_allocate(char *str);
void resize_array(Program *p);


void input_in_array(Program *p,char *filename);
void whether_print(FILE *fp,Program *p); /*Ҫ˵�� ��Ϊ�� space����ô���ӵĴ���*/
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

void check_mark(Program *p, char* mark);
void check_strcon(Program *p);
void check_numcon(Program *p);
void check_var(Program *p,char flag);

void interp_set_var(Program *p);
void interp_rnd(Program *p);
void interp_innum(Program *p);
void interp_in2str(Program *p);
void interp_file(Program *p);

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
void whether_file(FILE *fp, Program *p) /*������read_varcon��,���ԣ�֮����*/
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
        /*����Ҫ��free str ��Ϊ ָ��ָ����Ƕѣ���read_var_or_num������reallocate��ԭ�����ط��Ѿ�free��*/
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
        p->cw++;
        Prog(p);
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

void parse_file(Program *p) /*������� �Ѿ��ڶ��ļ�ʱ������*/
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
void parse_rnd(Program *p)/*��parse_innum һ��*/
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
}
void parse_inc(Program *p)/*��parse_innum,parse_rnd һ��*/
{
    check_mark(p,"(");
    p->cw++;
    check_var(p,'%');
    check_mark(p,")");
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
        flag = 1;
    }else if (tempc == '$'){
        temps = mvm_search(p->map,p->array[p->cw]);
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
    }
    for(i=0,j=1;i<len-TWO;i++,j++){
        str[i]=content[j];
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

void interp_innum(Program *p) /*��ô�������ܵ�Խ��,�ܷ�ֱ�Ӷ�һ��str ������ float*/
{
    float number;
    char *data;
    data = (char *)calloc(DEFAULTSIZE*TWO,sizeof(char));
    p->cw--;
    if(scanf("%f",&number)!=1){
        ERROR_2("Need input a float number",p->array[p->cw],p->cw);
    }
    sprintf(data,"%f",number);
    if(data[DEFAULTSIZE*TWO-OFFSET] !='\0'){
        ERROR_2("Scanned Float Number is too long, if you really need, "\
                "please manually increase the allocated memory",p->array[p->cw-OFFSET],p->cw-OFFSET);
    }
    if(data[DEFAULTSIZE-1] != '\0'){
        ERROR_2("Input of float is too long",p->array[p->cw],p->cw);
    }
/*    while (data[size-1] != '\0'){
        free(data);
        size *= 2;
        data = (char *)calloc(size,sizeof(char));
        sprintf(data,"%f",number);
    }*/
    if(mvm_search(p->map,p->array[p->cw]) != NULL){
        mvm_delete(p->map,p->array[p->cw]);
    }
    mvm_insert(p->map,p->array[p->cw],data);
    free(data);
    p->cw++;
}

void interp_in2str(Program *p)/*��ô�ĳɶ�̬��*/
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
    free_program(&p2);*//*����free mvm*/
}