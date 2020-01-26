#include "nal.h"

int main(int argc,char **argv)
{
    Program p;
    check_argc(argc);
    init_program(&p);

    input_in_array(&p,argv[SECOND]);
    #ifdef INTERP
    srand((unsigned)time(NULL));
    #endif
    Prog(&p);
    #ifndef INTERP
    printf("Parsed OK!\n");
    #endif
    free_program(&p);
#ifdef TEST
    test();
#endif

    return 0;
}
void init_program(Program *p)
{
    p->cw=ZERO;
    p->count=ZERO;

    /*Initialize the map*/
    p->map = mvm_init();

    /*Initialize the array*/
    p->array = (char **)malloc(sizeof(char *));
    if(p->array==NULL){
        ERROR_1("Cannot allocate memory");
    }
    p->array[p->count]= (char *)calloc(DEFAULTSIZE, sizeof(char));
    check_allocate(p->array[p->count]);

    /*Initialize the list*/
    p->lt = (List *)malloc(sizeof(List));
    if(p->lt == NULL){
        ERROR_1("Cannot allocate memory");
    }
    p->lt->prog[FIRST] = p;
    p->lt->size = ONE;

}

void free_program(Program *p)
{
    int i;
    for(i=0;i<p->count+OFFSET;i++){
        free(p->array[i]);
    }
    free(p->array);
    p->array = NULL;
    mvm_free(&(p->map));
    free(p->lt);
    p->lt = NULL;
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
        if(p->array[p->count][DEFAULTSIZE-OFFSET] != '\0'){
            ERROR_2("This instruction's length should be less than "
                    "Default Size (20) : ",p->array[p->count],p->count);
        }
        is_print(fp,p);
        is_setvar(fp,p);
        is_ifcond(fp,p);
        is_file(fp,p);
#ifdef EXTENT
        is_rpnope(fp,p);
        is_swap(fp,p);
#endif
        p->count++;
        resize_array(p);
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        check_allocate(p->array[p->count]);
    }
    fclose(fp);
}
#ifdef EXTENT
void is_rpnope(FILE *fp, Program *p)
{
    if(!strsame(p->array[p->count],"RPNOPE")){
        return;
    }
    p->count++;
    resize_array(p);
    read_varcon(fp,p);
}
void is_swap(FILE *fp,Program *p)
{
    int i;
    if(!strsame(p->array[p->count],"SWAP")){
        return;
    }
    for(i=ZERO;i<TWO;i++){
        p->count++;
        resize_array(p);
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        check_allocate(p->array[p->count]);
        if(fscanf(fp,"%s",p->array[p->count])!=ONE){
            ERROR_1("Need a closing } to finish file");
        }
        p->count++;
        resize_array(p);
        read_varcon(fp,p);
    }
}
#endif



void is_print(FILE *fp,Program *p)
{
    if(!strsame(p->array[p->count],"PRINT")&&!strsame(p->array[p->count],"PRINTN")){
        return;
    }
    p->count++;
    resize_array(p);
    read_varcon(fp,p);

}


void is_setvar(FILE *fp,Program *p)
{
    if(p->array[p->count][FIRST]!='$'&&p->array[p->count][FIRST]!='%'){
        return;
    }
    p->count++;
    resize_array(p);
    p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    check_allocate(p->array[p->count]);

    if(fscanf(fp,"%s",p->array[p->count]) != 1){
        ERROR_1("Need a closing } to finish file");
    }
    if(!strsame(p->array[p->count],"=")){
        return;
    }
    p->count++;
    resize_array(p);
    read_varcon(fp,p);
}

void is_ifcond(FILE *fp,Program *p)
{
    int i;
    if(!strsame(p->array[p->count],"IFEQUAL")&&!strsame(p->array[p->count],"IFGREATER")){
        return;
    }
    for(i=ZERO;i<TWO;i++){
        p->count++;
        resize_array(p);
        p->array[p->count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
        check_allocate(p->array[p->count]);
        if(fscanf(fp,"%s",p->array[p->count])!=ONE){
            ERROR_1("Need a closing } to finish file");
        }
        p->count++;
        resize_array(p);
        read_varcon(fp,p);
    }
}
void is_file(FILE *fp, Program *p) /*可以用read_varcon吗,可以，之后再*/
{
    if(!strsame(p->array[p->count],"FILE")){
        return;
    }
    p->count++;
    resize_array(p);
    read_varcon(fp,p);
}
/*Used to read the VARCON into p->array[p->count];
 * we need to use c=getc(fp) to catch since we need to deal with space ' ' '\n' '\r' '\t'
 * and after the if statement, it will divided into read_var_or_numcon or read_strcon
 * also, we need dynamic size for these.
 * */
void read_varcon(FILE *fp,Program *p)
{
    char c;
    int i = FIRST; /*Used for the index of str*/
    char *str = (char *)calloc(TWO,sizeof(char));
    check_allocate(str);/*str is used to receive VARCON, dynamic size */
    /*Discard ' ' '\n''\r''\t'*/
    while(((c=getc(fp))==' '|| c =='\n'||c == '\t'||c == '\r')&& c != EOF);
    if(c==EOF){
        ERROR_2("Expect beginning \" or # or % or $ or digit to start VARCON after ",\
        p->array[p->count-OFFSET],p->count-OFFSET);
    }
    str[i++] =c;
    if(c == '%' ||c == '$'||(c>='0'&&c<='9')||c == '.'){
        read_var_or_numcon(fp,str,p,i);
        /*free(str); no need to free, because realloc will free previous one*/
    }else if(c=='#'||c == '\"'){
        read_strcon(fp,str,p,i,c);
    }else{
        ERROR_2("Illegal input for VARCON after ",\
        p->array[p->count-OFFSET],p->count-OFFSET);
    }
}
void read_var_or_numcon(FILE *fp,char *str,Program *p,int i)
{
    int c;
    while((c=getc(fp))!=' '&& c!= '\n'&& c!= '\t'&&c!= '\r'&& c!=EOF){
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
        ERROR_2("Expect a matched closing \" or # to finish STRCON after ",\
        p->array[p->count-OFFSET],p->count-OFFSET);
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
        interp_abort(p);
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

        return;
    }
    if(strsame(p->array[p->cw],"RND")){
        parse_rnd(p);
        return;
    }
    if(strsame(p->array[p->cw],"IFEQUAL")||strsame(p->array[p->cw],"IFGREATER")){
        parse_ifcondition(p);

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
#ifdef EXTENT
    if(strsame(p->array[p->cw],"RPNOPE")){
        parse_rpnope(p);
        return;
    }
    if(strsame(p->array[p->cw],"SWAP")){
        parse_swap(p);
        return;
    }

#endif

    ERROR_2("Undefined instruction",p->array[p->cw],p->cw);
}

void check_symbol(Program *p, char* symbol)
{
    p->cw++;
    if(!strsame(p->array[p->cw],symbol)){
        fprintf(stderr,"Expect a \"%s\" here: %s(WORD %d) in %s, line %d\n",symbol,p->array[p->cw],p->cw,__FILE__,__LINE__);
        exit(2);
    }
}

void check_strcon(Program *p)
{
    if(!is_strcon(p->array[p->cw])){
        ERROR_2("It is not a STRCON:",p->array[p->cw],p->cw);
    }
}
bool is_strcon(char *str)
{
    int len = (int)strlen(str);
    if(str[FIRST]!= '\"'&& str[FIRST]!= '#'){
        return FALSE;
    }
    if(str[FIRST]!=str[len-OFFSET]){
        return FALSE;
    }
    return TRUE;
}

void check_numcon(Program *p)
{
    if(!is_numcon(p->array[p->cw])){
        ERROR_2("It is not a NUMCON:",p->array[p->cw],p->cw);
    }
}

bool is_numcon(char *str)
{
    int i,flag = 0,len = (int)strlen(str);
    for(i=0;i<len;i++){
        if((str[i]<'0'||str[i]>'9')&&str[i]!='.'){
            return FALSE;
        }
        if(str[i] =='.'){
            flag++;
        }
        if(flag>1){
            return FALSE;
        }
    }
    return TRUE;;
}

void check_var(Program *p,char flag)
{
    if(!is_var(p->array[p->cw],flag)){
        ERROR_2("It is an illegal VAR:",p->array[p->cw],p->cw);
    }
}
bool is_var(char *str,char flag)
{
    int len = (int)strlen(str);
    int i;
    if(str[FIRST] != flag){
        return FALSE;
    }
    for(i=1;i<len;i++){
        if(str[i]<'A'||str[i]>'Z'){
            return FALSE;
        }
    }
    return TRUE;
}
void parse_file(Program *p)
{
    p->cw++;
    check_strcon(p);
    #ifdef INTERP
    interp_file(p);
    #endif
}
void interp_file(Program *p)
{
    Program p2;
    int i;
    char *filename = take_quota(p->array[p->cw]);
    init_program(&p2);
    mvm_free(&(p2.map));
    free(p2.lt);
    p2.map = p->map;
    p2.lt = p->lt;
    p->lt->size++;
    if(p->lt->size>= LIST_SIZE){
        ERROR_1("Expect less than 256 Programs existed at same time");
    }
    p->lt->prog[p->lt->size-OFFSET] = &p2;
    input_in_array(&p2,filename);
    free(filename);
    Prog(&p2);
    for(i=0;i<p2.count+OFFSET;i++){
        free(p->lt->prog[p->lt->size-OFFSET]->array[i]);
    }
    free(p2.array);
    p->lt->size--;
}

void interp_abort(Program *p)
{
    int i,j,size;
    size = p->lt->size;
    for(i=0;i<size;i++){
        for(j=0;j<p->lt->prog[i]->count+OFFSET;j++){
            free(p->lt->prog[i]->array[j]);
        }
        free(p->lt->prog[i]->array);
    }
    mvm_free(&(p->map));
    free(p->lt);
    exit(0);
}

void parse_in2str(Program *p)
{
    check_symbol(p,"(");
    p->cw++;
    check_var(p,'$');
    check_symbol(p,",");
    p->cw++;
    check_var(p,'$');
    check_symbol(p,")");
    #ifdef INTERP
    interp_in2str(p);
    #endif
}

void interp_in2str(Program *p)/*怎么改成动态的*/
{
    /*i is used to control the round, total round = 2;*/
    int i;
    char *str;

    p->cw = p->cw - TWO - ONE;
    for(i=FIRST;i<TWO;i++){
        str = (char *)calloc(ONE,sizeof(char));
        check_allocate(str);
        get_str(&str);
        insert_map(p,str);
        free(str);
        p->cw = p->cw +TWO;
    }
    p->cw = p->cw - TWO;
    p->cw++;
}

void get_str(char **str)
{
    char c;
    int j = FIRST;
    /*j is used to index str;*/
    while((c= getchar()) != ' ' && c != '\n' && c != EOF){
        *str = (char *)realloc(*str,(strlen(*str)+TWO)* sizeof(char));
        check_allocate(*str);
        (*str)[j++]=c;
        (*str)[j]='\0';
    }
}
void insert_map(Program *p, char *str)
{
    if(mvm_search(p->map,p->array[p->cw]) != NULL){
        mvm_delete(p->map,p->array[p->cw]);
    }
    mvm_insert(p->map,p->array[p->cw],str);
}

void parse_innum(Program *p)
{
    check_symbol(p,"(");
    p->cw++;
    check_var(p,'%');
    check_symbol(p,")");
    #ifdef INTERP
    interp_innum(p);
    #endif
}
void interp_innum(Program *p)
{
    int i,len,flag = ZERO;
    char *str;
    p->cw = p->cw - OFFSET;
    str = (char *)calloc(ONE,sizeof(char));
    check_allocate(str);
    get_str(&str);
    len = (int) strlen(str);
    for(i=ZERO;i<len;i++){
        if((str[i]<'0'||str[i]>'9')&&str[i]!='.'){
            ERROR_2("Expect only digit or . in NUM",p->array[p->cw],p->cw);
        }
        if(str[i] =='.'){
            flag++;
        }
        if(flag>1){
            ERROR_2("No more than 1 dot in NUM",p->array[p->cw],p->cw);
        }
    }
    insert_map(p,str);
    free(str);
    p->cw = p->cw + OFFSET;
}

void parse_jump(Program *p)
{
    p->cw++;
    check_numcon(p);

#ifdef INTERP
    interp_jump(p);
#endif
}
void interp_jump (Program *p)
{
    int len,i,number;
    len = (int)strlen(p->array[p->cw]);
    for(i=0;i<len;i++){
        if(p->array[p->cw][i]=='.'){
            ERROR_2("Must be a integer after JUMP :",\
            p->array[p->cw],p->cw);
        }
    }
    number = atoi(p->array[p->cw]);
    if(number >= p->count){
        ERROR_2("Jump number must be smaller than total count :",\
        p->array[p->cw],p->cw);
    }
    p->cw = number - OFFSET;
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
    #ifdef INTERP
    interp_print(p);
    #endif
}

void interp_print(Program *p)
{
    int flag = 0;/*flag used to identify whether str need be freed.*/
    char *str,*temps;
    char tempc = p->array[p->cw][FIRST];
    if( tempc == '%'){
        check_declare(p);
        str = mvm_search(p->map,p->array[p->cw]);
        flag = 1;
    }else if (tempc == '$'){
        check_declare(p);
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
        free(str); /*Because take_quota will allocate a memory for str*/
    }
}
void parse_rnd(Program *p)/*和parse_innum 一样*/
{
    check_symbol(p,"(");
    p->cw++;
    check_var(p,'%');
    check_symbol(p,")");
    #ifdef INTERP
    interp_rnd(p);
    #endif
}
void interp_rnd(Program *p)
{
    char *data;
    int random;
    p->cw--;
    data = (char *)calloc(THREE,sizeof(char));
    check_allocate(data);
    random = rand() % RNDBASE;
    sprintf(data,"%d",random);
    insert_map(p,data);
    free(data);
    p->cw++;
}
void parse_ifcondition(Program *p)
{
    char flag;
    int i;
    check_symbol(p,"(");
    p->cw++;
    for(i=0;i<TWO;i++){
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
        p->cw = p->cw + TWO;
    }
    p->cw = p->cw - TWO -TWO;
    check_symbol(p,",");
    p->cw = p->cw + ONE;
    check_symbol(p,")");
    /*Now,p->array[p->cw] points to ")"*/
#ifdef INTERP
    interp_ifcondition(p);
#endif
#ifndef INTERP
    p->cw++;
    Prog(p);
#endif
}

void interp_ifcondition(Program *p)
{
    int success, mark = 0;
    char *str[THREE];/*Used to store IFCOND, First VARCON and Second VARCON*/
    p->cw = p->cw - OFFSET - TWO - TWO;/*Put p->cw to IFCOND*/
    str[ZERO] = p->array[p->cw];
    p->cw = p->cw + TWO; /*Put p->cw to first VARCON*/
    is_ifmatched(p,str,&mark);/*Store two VARCONs and give mark*/
    /*mark==0 means they are NUMVAR or NUMCON---needn't be freed
     *mark==2 means they are STRVER or STRCON---need be freed*/
    if(mark != 0 && mark != 2){
        ERROR_2("The types of VARCON in IFCOND is not matched",\
        p->array[p->cw],p->cw);
    }
    success = is_meet(p,str,mark);/*success==1 means IFCOND is met*/
    if(mark == 2){
        free(str[ONE]);
        free(str[TWO]);
    }
    if(success == 1){
        p->cw = p->cw + TWO;
        Prog(p);
    }else{
        p->cw = p->cw + ONE;/*Since check_symbol begins with p->cw++;*/
        check_symbol(p,"{");
        escape(p);
    }
}

void is_ifmatched(Program *p, char **str,int *mark)
{
    char flag;
    int i;
    for(i=0;i<TWO;i++){
        flag = p->array[p->cw][FIRST];
        if(flag =='%'){
            check_declare(p);

            str[i+OFFSET] = mvm_search(p->map,p->array[p->cw]);
        }else if (flag == '$'){
            (*mark)++;
            check_declare(p);
            str[i+OFFSET] = mvm_search(p->map,p->array[p->cw]);
            str[i+OFFSET] = take_quota(str[i+OFFSET]);
        }else if (flag == '\"' || flag == '#'){
            (*mark)++;
            str[i+OFFSET] = p->array[p->cw];
            str[i+OFFSET] = take_quota(str[i+OFFSET]);
        }else{
            str[i+OFFSET] = p->array[p->cw];
        }
        p->cw = p->cw + TWO;
    }
    p->cw = p->cw - TWO;
}

bool is_meet(Program *p, char **str, int mark)
{
    int success = FALSE;
    float num1,num2;
    if(strsame(str[ZERO],"IFEQUAL") && mark == 0){
        num1 = atof(str[ONE]);
        num2 = atof(str[TWO]);
        success = (fabs((double)(num1-num2))<=0.0005);
    }else if (strsame(str[ZERO],"IFEQUAL") && mark == 2){
        success = strsame(str[ONE],str[TWO]);
    }else if (strsame(str[ZERO],"IFGREATER") && mark == 0){
        num1 = atof(str[ONE]);
        num2 = atof(str[TWO]);
        success = (fabs((double)(num1-num2))>0.0005 && num1 > num2);
    }else if (strsame(str[ZERO],"IFGREATER") && mark == 2){
        ERROR_2("Cannot compare str in IFGREATER",\
        p->array[p->cw],p->cw);
    }
    return success;
}

void escape(Program *p)
{
    int flag = ONE;
    p->cw++;
    while((p->cw < p->count) && flag != ZERO){
        if(strsame(p->array[p->cw],"{")){
            flag++;
        }
        if(strsame(p->array[p->cw],"}")){
            flag--;
        }
        p->cw++;
    }
    if(p->cw >= p->count){
        ERROR_2("Expect a \"}\" to conclude IFCOND",\
        p->array[p->cw],p->cw);
    }
    p->cw--;
}


void parse_inc(Program *p)/*和parse_innum,parse_rnd 一样*/
{
    check_symbol(p,"(");
    p->cw++;
    check_var(p,'%');
    check_symbol(p,")");
    #ifdef INTERP
    interp_inc(p);
    #endif
}
void interp_inc (Program *p)
{
    float number;
    char *temp;
    p->cw--;
    check_declare(p);
    temp = mvm_search(p->map,p->array[p->cw]);

    number = atof(temp);
    number = number + OFFSET;
    temp = (char *)calloc(DEFAULTSIZE*TWO,sizeof(char));
    sprintf(temp,"%f",number);
    if(temp[DEFAULTSIZE*TWO-OFFSET] !='\0'){
        ERROR_2("Increasing number is out of bound",\
        p->array[p->cw],p->cw);
    }
    insert_map(p,temp);
    free(temp);
    p->cw++;
}
void parse_set_variable(Program *p,char flag)
{
    char symbol;
    check_var(p,flag);
    check_symbol(p,"=");
    p->cw++;
    symbol = p->array[p->cw][FIRST];
    if(symbol =='%'){
        check_var(p,'%');

    }else if (symbol == '$'){
        check_var(p,'$');
    }else if (symbol == '\"' || symbol == '#'){
        check_strcon(p);
    }else{
        check_numcon(p);
    }
    #ifdef INTERP
    if(flag == '%'){
        if(symbol != '%' && !(symbol <= '9' && symbol>='0') && symbol != '.'){
            ERROR_2("Expect matched types of VARCON in SET",p->array[p->cw],p->cw);
        }
    }else if(flag == '$'){
        if(symbol != '$' && symbol != '\"' && symbol !='#'){
            ERROR_2("Expect matched types of VARCON in SET",p->array[p->cw],p->cw);
        }
    }
    interp_set_var(p,symbol);
    #endif
}
void interp_set_var(Program *p,char symbol)
{
    char *temp;
    if(symbol == '%' || symbol == '$'){
        check_declare(p);
        temp = mvm_search(p->map,p->array[p->cw]);
        p->cw = p->cw - TWO;
        if(mvm_search(p->map,p->array[p->cw]) != NULL){
            mvm_delete(p->map,p->array[p->cw]);
        }
        mvm_insert(p->map,p->array[p->cw],temp);
        p->cw = p->cw + TWO;
    }else{
        p->cw = p->cw - TWO;
        if(mvm_search(p->map,p->array[p->cw]) != NULL){
            mvm_delete(p->map,p->array[p->cw]);
        }
        mvm_insert(p->map,p->array[p->cw],p->array[p->cw+TWO]);
        p->cw = p->cw + TWO;
    }


}


void check_declare (Program *p)
{
   char *str;
   str = mvm_search(p->map,p->array[p->cw]);
   if(str == NULL){
        ERROR_2("Please define variable before using :",\
        p->array[p->cw],p->cw);
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



#ifdef EXTENT
void parse_rpnope(Program *p)
{
    int temp0,temp1,temp2;/*record the index of "{" and "}"*/
    char mark;
    p->cw++;
    check_var(p,'%');
    temp0 = p->cw;
    check_symbol(p,"=");
    check_symbol(p,"[");
    p->cw++;
    temp1 = p->cw;

    while((p->cw<p->count) && p->array[p->cw][FIRST] != ']'){
        mark = p->array[p->cw][FIRST];
        if(mark =='%'){
            check_var(p,'%');
        }else if((mark>='0'&&mark <='9')|| mark =='.'){

            check_numcon(p);
        }else if (is_operator(mark)==0){

            ERROR_2("Ilegal input in RPNOPE",p->array[p->cw],p->cw);
        }
        p->cw++;
    }
    if(p->cw >= p->count){
        ERROR_2("Expect a \"}\" to conclude RPNOPE",\
        p->array[p->cw],p->cw);
    }
    temp2 = --(p->cw);
    p->cw++;
#ifdef INTERP
    interp_rpnope(p,temp0,temp1,temp2);
#endif
}




void interp_rpnope(Program *p,int var_location, int start,int finish)
{
    int temp = p->cw;
    p->cw = var_location;
    compute(p,start,finish);
    p->cw = temp;
}


void compute(Program *p, int start, int finish)
{
    int i;
    Stack *s;
    char *str1, *str2;
    float num1,num2,num3;
    char *str3[MAXSIZE];
    for(i=0;i<MAXSIZE;i++){
        str3[i] = calloc(DEFAULTSIZE*TWO,sizeof(char));
    }
    s = init_stack();
    for(i=start;i<=finish;i++){
        if(is_operator(p->array[i][FIRST])){
            pop_stack(s,&str1);
            pop_stack(s,&str2);
            num1 = atof(str1);
            num2 = atof(str2);
            num3 = operation(p->array[i][FIRST],num1,num2);
            sprintf(str3[s->top],"%f",num3);
            push_stack(s,str3[s->top]);
        }else if (p->array[i][FIRST] == '%'){
            str1 = mvm_search(p->map,p->array[i]);
            push_stack(s,str1);
        }else{
            push_stack(s,p->array[i]);
        }
    }
    insert_map(p,s->data[s->top-OFFSET]);
    free(s);
    for(i=0;i<MAXSIZE;i++){
        free(str3[i]);
    }
}


void parse_swap (Program *p)
{
    char flag1, flag2;
    check_symbol(p,"(");
    p->cw++;
    flag1 = p->array[p->cw][FIRST];
    if(flag1 =='%'){
        check_var(p,'%');
    }else{
        check_var(p,'$');
    }
    check_symbol(p,",");
    p->cw++;
    flag2 = p->array[p->cw][FIRST];
    if(flag2 =='%'){
        check_var(p,'%');
    }else{
        check_var(p,'$');
    }
    check_symbol(p,")");
    #ifdef INTERP
    if(flag1 != flag2){
        ERROR_2("Expect a matched VAR type",p->array[p->cw-THREE],p->cw-THREE);
    }
    interp_swap(p);
    #endif
}
void interp_swap(Program *p)
{
    int len;
    char *str,*temp1,*temp2;
    p->cw = p->cw -THREE;

    check_declare(p);
    temp1 = mvm_search(p->map,p->array[p->cw]);
    len = (int)strlen(temp1);
    str = (char *)calloc(len+OFFSET,sizeof(char));
    strcpy(str,temp1);
    mvm_delete(p->map,p->array[p->cw]);
    p->cw = p->cw + TWO;
    check_declare(p);
    temp2 = mvm_search(p->map,p->array[p->cw]);
    mvm_insert(p->map,p->array[p->cw-TWO],temp2);
    mvm_delete(p->map,p->array[p->cw]);
    mvm_insert(p->map,p->array[p->cw],str);
    free(str);
    p->cw++;
}

#endif





