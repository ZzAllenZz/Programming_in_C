#include "nal.h"
#include <assert.h>


void test_init_and_free_program();
void test_check_argc();
void test_resize_array();
void test_read_varcon();
void test()
{

    Program p;
    check_argc(2);
    test_init_and_free_program();
    test_check_argc();
    test_resize_array();
    test_read_varcon();
    init_program(&p);
    assert(p.cw == 0);
    assert(p.count == 0);
    assert(p.map != NULL);
    assert(p.array != NULL);
    assert(p.array[0] != NULL);
    assert(p.lt != NULL);
    assert(p.lt->size == ONE);
    input_in_array(&p,"print.test");
    assert(p.count == 19 );
    assert(strcmp(p.array[p.cw++],"{")==0);
    assert(strcmp(p.array[p.cw++],"$A")==0);
    assert(strcmp(p.array[p.cw++],"=")==0);
    assert(strcmp(p.array[p.cw++],"\"COOL\"")==0);
    assert(strcmp(p.array[p.cw++],"$B")==0);
    assert(strcmp(p.array[p.cw++],"=")==0);
    assert(strcmp(p.array[p.cw++],"#PBBY#")==0);
    assert(strcmp(p.array[p.cw++],"%B")==0);
    assert(strcmp(p.array[p.cw++],"=")==0);
    assert(strcmp(p.array[p.cw++],"12")==0);
    assert(strcmp(p.array[p.cw++],"PRINT")==0);
    assert(strcmp(p.array[p.cw++],"\"Hello\"")==0);
    assert(strcmp(p.array[p.cw++],"PRINTN")==0);
    assert(strcmp(p.array[p.cw++],"#Uv#")==0);
    assert(strcmp(p.array[p.cw++],"PRINT")==0);
    assert(strcmp(p.array[p.cw++],"$A")==0);
    assert(strcmp(p.array[p.cw++],"PRINTN")==0);
    assert(strcmp(p.array[p.cw++],"%B")==0);
    assert(strcmp(p.array[p.cw++],"}")==0);
    p.cw = 0;

    free_program(&p);
/*    p.array[0] =*/

/*
#ifdef INTERP
    srand((unsigned)time(NULL));
#endif
    Prog(&p);

#ifdef INTERP
    printf("Interpreted OK!\n");
#else
    printf("Parsed OK!\n");
#endif

    free_program(&p);*/
}

void test_init_and_free_program()
{
    Program p;
    init_program(&p);

    assert(p.cw == ZERO);
    assert(p.count == ZERO);
    assert(p.map != NULL);
    assert(p.map->head == NULL);
    assert(p.map->numkeys == ZERO);
    assert(p.array != NULL);
    assert(p.array[ZERO] != NULL);
    assert(p.lt != NULL);
    assert(p.lt->prog[FIRST] == &p);
    assert(p.lt->size == ONE);

    free_program(&p);

    assert(p.map==NULL);
    assert(p.array==NULL);
    assert(p.lt==NULL);

}
void test_check_argc()
{
    int i = TWO;
    check_argc(TWO);
    /*Ensure above function is done without ERROR_1  */
    assert(i==TWO);
}

void test_resize_array()
{
    Program p;
    init_program(&p);
    p.count = ONE;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    assert(p.array[p.count]!=NULL);
    strcpy(p.array[p.count],"HELLO WORLD");
    assert(strsame(p.array[p.count],"HELLO WORLD"));
    free_program(&p);
}

void test_read_varcon()
{
    Program p;
    FILE *fp;
    int i;
    init_program(&p);
    free(p.array[ZERO]);
    fp = fopen("read_varcon.testf","r");
    assert(fp!=NULL);

    for(i=0;i<2;i++){
        read_varcon(fp,&p);
        p.count++;
       resize_array(&p);
    }

    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    assert(p.count==2);
    assert(strsame(p.array[0],"\"Neill\""));
    assert(strsame(p.array[1],"16.11"));

    fclose(fp);
    free_program(&p);
}




