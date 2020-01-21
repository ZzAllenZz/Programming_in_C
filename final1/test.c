#include "nal.h"
#include <assert.h>

void first_test()
{

    Program p;
    check_argc(2);

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
