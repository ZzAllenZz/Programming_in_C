#include "nal.h"
#include <assert.h>

/*In order to test every line of code, I write a test-function for each function,
 * and deploy the required environment before test each function*/
void test_init_and_free_program();
void test_check_argc();
void test_resize_array();
void test_read_varcon();
void test_is_xxx();
void test()
{

    Program p;
    check_argc(2);
    test_init_and_free_program();
    test_check_argc();
    test_resize_array();
    test_read_varcon();
    test_is_xxx();
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

}
/*Test init_program and free_program*/
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
/*Test check_argc*/
void test_check_argc()
{
    int i = TWO;
    check_argc(TWO);
    /*Ensure above function is done without ERROR_1  */
    assert(i==TWO);
}
/*Test resize_array*/
void test_resize_array()
{
    Program p;
    init_program(&p);
    p.count = ONE;
    resize_array(&p);
    /*if we do not resize array, we cannot access to p.array[1]
     *and Sanitize and Valgrind will report heap-buffer-overflow.
     * */
    p.array[p.count] = "HELLO WORLD";
    assert(p.array[p.count]!=NULL);
    assert(strsame(p.array[p.count],"HELLO WORLD"));
    /*in order to use function:free_program*/
    p.array[p.count] =(char *)calloc(DEFAULTSIZE, sizeof(char));

    free_program(&p);
}


/*Test read_varcon and nested read_var_or_numcon and nested read_strcon;
 * we need to deploy a environment where it is ready to read in a VARCON;
 * So, we need a file which is on purpose of test read_varcon,
 * named "read_varcon.testf"
 * */
void test_read_varcon()
{
    Program p;
    FILE *fp;
    int i;
    init_program(&p);
    free(p.array[ZERO]);
    fp = fopen("read_varcon.testf","r");
    assert(fp!=NULL);

    for(i=0;i<7;i++){
        read_varcon(fp,&p);
        p.count++;
        resize_array(&p);
    }
    /*in order to use function:free_program,
     * which free from p.array[0] to p.array[count]  */
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    assert(p.count==7);
    i = strsame(p.array[0],"\"Neill\"");
    assert(i);
    i = strsame(p.array[1],"%A");
    assert(i);
    i = strsame(p.array[2],"%a");
    assert(i);
    i = strsame(p.array[3],"$B");
    assert(i);
    i = strsame(p.array[4],"$b");
    assert(i);
    i = strsame(p.array[5],"16.11");
    assert(i);
    i = strsame(p.array[6],"#ABC#");
    assert(i);
    fclose(fp);
    free_program(&p);
}
/*Test read_varcon and nested read_var_or_numcon and nested read_strcon;
 * we need to deploy a environment where it is ready to read in a VARCON;
 * So, we need a file which is on purpose of test read_varcon,
 * named "read_varcon.testf"
 * */
void test_is_xxx()
{
    Program p;
    FILE *fp;
    int i;
    init_program(&p);

    fp = fopen("is_print.testf","r");
    assert(fp!=NULL);

    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);
    assert(p.count == ZERO);
    is_print(fp,&p);
    /*If it is not "PRINT" OR "PRINTN", do nothing*/
    assert(p.count == ZERO);

    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);
    assert(p.count == ONE);
    is_print(fp,&p);
    /*If it is "PRINT" OR "PRINTN", do nothing, p.count++*/
    assert(p.count == TWO);

    i = strsame(p.array[0],"ABC");
    assert(i);
    i = strsame(p.array[1],"PRINT");
    assert(i);
    i = strsame(p.array[2],"#D E F#");
    assert(i);

/*
    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);





    assert(p.count == THREE);
    is_print(fp,&p);
    */
/*If it is "PRINT" OR "PRINTN", do nothing, p.count++*//*

    assert(p.count == TWO);



*/


    fclose(fp);
    free_program(&p);
}


