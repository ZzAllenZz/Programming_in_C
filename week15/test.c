#include "nal.h"
#include <assert.h>

void test()
{

    Program p;
    check_argc(2);

    init_program(&p);
    assert(p->cw == 0);

    input_in_array(&p,"print.test");
    p.array[0] =

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
    return 0;
}