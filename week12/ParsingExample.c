#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXNUMTOKENS    100
#define MAXTTOKENSIZE   7
#define PROGRAM "01.no"
#define strsame(A,B) (strcmp(A,B)==0)
#define ERROR(PHRASE) {fprintf(stderr,"Fatal Error %s occured in %s, line %d\n",PHRASE,__FILE__,__LINE__);exit(2);}

struct prog{
    char wds[MAXNUMTOKENS][MAXTTOKENSIZE];
    int cw;
};
typedef struct prog Program;

void Prog(Program *p);
void Code(Program *p);
void Statement(Program *p);

int main(void)
{
    int i;
    FILE *fp;
    Program prog;
    prog.cw = 0;
    for(i=0;i<MAXNUMTOKENS;i++){
        prog.wds[i][0]='\0';
    }
    i=0;
    while(fscanf(fp,"%s",prog.wds[i++])==1 && i<MAXNUMTOKENS);
    assert(i<MAXNUMTOKENS);
    Prog(&prog);
    printf("Parsed OK!\n");
    return 0;
}

void Prog(Program *p)
{
    if(!strsame(p->wds[p->cw],"BEGIN")){
        ERROR("Cannot find BEGIN statement in begin...\n");
    }
    p->cw++;
    Code(p);
}

void Code(Program *p)
{
    if(strsame(p->wds[p->cw],"END")){
        return;
    }
    Statement(p);
    p->cw++;
    Code(p);
}

void Statement(Program *p)
{
    if(strsame(p->wds[p->cw],"ONE")){
        return;
    }
    if(strsame(p->wds[p->cw],"NOUGHT")){
        return;
    }
    ERROR("Expect a ONE or NOUGHT");
}