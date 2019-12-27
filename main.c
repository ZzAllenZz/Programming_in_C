#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

#define MAXNUMTOKENS    100
#define MAXTTOKENSIZE   100
#define PROGRAM "test1.txt"
#define strsame(A,B) (strcmp(A,B)==0)
#define ERROR(PHRASE) {fprintf(stderr,"Fatal Error %s occured in %s, line %d\n",PHRASE,__FILE__,__LINE__);exit(2);}

struct program{
    char wds[MAXNUMTOKENS][MAXTTOKENSIZE];
    int cw;
};

typedef struct program Program;

void Prog(Program *p);
void Instrs(Program *p);
void Instruct(Program *p);

int main(void)
{
    int i;
    FILE *fp;
    Program prog;
    prog.cw = 0;
    for(i=0;i<MAXNUMTOKENS;i++){
        prog.wds[i][0]='\0';
    }
    if( !(fp = fopen(PROGRAM,"r"))){
        fprintf(stderr,"Cannot open %s\n",PROGRAM);
        exit(2);
    }

    i=0;
    fscanf(fp,"%s",prog.wds[i++]);
    printf("%s\n",prog.wds[0]);

    fscanf(fp,"%s",prog.wds[i++]);
    printf("%s\n",prog.wds[1]);

    fscanf(fp,"%s",prog.wds[i++]);
    printf("%s\n",prog.wds[2]);

    fscanf(fp,"%s",prog.wds[i++]);
    printf("%s\n",prog.wds[2]);
    printf("%s\n",prog.wds[3]);


    for(i=0;i<4;i++){
        printf("%s\n",prog.wds[i]);
    }
    printf("%s\n",prog.wds[2]);

/*    assert(i<MAXNUMTOKENS);
    for(i=0;i<MAXNUMTOKENS;i++){
        printf("%s\n",prog.wds[i]);
    }
    printf("111\n");*/
/*    assert(i<MAXNUMTOKENS);*/
    i=0;
    Prog(&prog);
    printf("Parsed OK!\n");
    return 0;
}

void Prog(Program *p)
{
    if(!strsame(p->wds[p->cw],"{")){
        ERROR("Cannot find { in begin...\n");
    }
    p->cw++;
    Instrs(p);
}

void Instrs(Program *p)
{
    if(strsame(p->wds[p->cw],"}")){
        return;
    }
    Instruct(p);
    p->cw++;
    Instrs(p);
}

void Instruct(Program *p)
{
    if(strsame(p->wds[p->cw],"PRINT")){
        return;
    }
    if(strcmp(p->wds[p->cw],"\"HELLOFUCKYOU\"")==0){
        printf("111\n");
        printf("%s\n",p->wds[p->cw]);
        printf("222\n");
        return;
    }
    ERROR("Expect \"HELLO\"");
}