#include "nal.h"
#include <assert.h>

/*In order to test every line of code, I write a test-function for each function,
 * and deploy the required environment before test each function*/
void test_init_and_free_program();
void test_check_argc();
void test_resize_array();
void test_read_varcon();
void test_is_xxx();
void test_input_in_array();
void test()
{

/*    Program p;*/
    check_argc(2);
    test_init_and_free_program();
    test_check_argc();
    test_resize_array();
    test_read_varcon();
    test_is_xxx();
    test_input_in_array();
/*    init_program(&p);
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

    free_program(&p);*/
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
 *
 * read_varcon ensures that we can read in whole thing we expect, including space.
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

    assert(p.count==7);
    /*in order to use function:free_program,
  * which free from p.array[0] to p.array[count]  */
    p.count = 6;
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
/*Used to test function of is_print, is_setvar,is_file and is_ifcond;
 * two testable features:
 * 1.p.count changes correctly
 * 2.the string should be read into p.array[p.count] correctly;
 * */
void test_is_xxx()
{
    Program p;
    FILE *fp;
    int i;
    init_program(&p);

    fp = fopen("is_xxx.testf","r");
    assert(fp!=NULL);


    /*Test is_print*/
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
    /*If it is "PRINT" OR "PRINTN", p.count++ and read VARCON into p.array[p.count]*/
    assert(p.count == TWO);

    i = strsame(p.array[0],"ABC");
    assert(i);
    i = strsame(p.array[1],"PRINT");
    assert(i);
    i = strsame(p.array[2],"#D E F#");
    assert(i);


    /*Test is_setvar*/

    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);
    assert(p.count == THREE);
    is_setvar(fp,&p);
    /*If it is not SET VAR, do nothing*/
    assert(p.count == THREE);


    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);
    assert(p.count == 4);
    is_setvar(fp,&p);
    /*If it is  SET VAR, p.count += 2 and read "=" and VARCON into p.array[p.count]*/
    assert(p.count == 6);

    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);
    assert(p.count == 7);
    is_setvar(fp,&p);
    /*If it is  SET VAR, p.count += 2 and read "=" and VARCON into p.array[p.count]*/
    assert(p.count == 9);

    i = strsame(p.array[3],"abc");
    assert(i);
    i = strsame(p.array[4],"$A");
    assert(i);
    i = strsame(p.array[5],"=");
    assert(i);
    i = strsame(p.array[6],"\"Hello C\"");
    assert(i);
    i = strsame(p.array[7],"%A");
    assert(i);
    i = strsame(p.array[8],"=");
    assert(i);
    i = strsame(p.array[9],"100.100");
    assert(i);

    /*Test is_file*/
    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);
    assert(p.count == 10);
    is_file(fp,&p);
    /*If it is not FILE, do nothing*/
    assert(p.count == 10);

    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);
    assert(p.count == 11);
    is_file(fp,&p);
    /*If it is  FILE, p.count++ and read VARCON into p.array[p.count]*/
    assert(p.count == 12);

    i = strsame(p.array[10],"QQQ");
    assert(i);
    i = strsame(p.array[11],"FILE");
    assert(i);
    i = strsame(p.array[12],"\"is xxx . testf\"");
    assert(i);


    /*Test is_ifcond*/
    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);

    assert(i== ONE);
    assert(p.count == 13);
    is_ifcond(fp,&p);
    /*If it is not IFEQUAL OR IFGREATER, do nothing*/
    assert(p.count == 13);

    p.count++;
    resize_array(&p);
    p.array[p.count] = (char *)calloc(DEFAULTSIZE, sizeof(char));
    i = fscanf(fp,"%s",p.array[p.count]);
    assert(i== ONE);
    assert(p.count == 14);
    is_ifcond(fp,&p);
    /*If it is not IFEQUAL OR IFGREATER, p.count += 4
     * and read "(",VARCON,",","VARCON" into p.array[p.count]*/
    assert(p.count == 18);

    i = strsame(p.array[13],"IFFF");
    assert(i);
    i = strsame(p.array[14],"IFEQUAL");
    assert(i);
    i = strsame(p.array[15],"(");
    assert(i);
    i = strsame(p.array[16],"$A");
    assert(i);
    i = strsame(p.array[17],",");
    assert(i);
    i = strsame(p.array[18],"#Hello C#");
    assert(i);

    fclose(fp);
    free_program(&p);
}

/*input_in_array is the whole function for reading string from file into p.array
 * we have do each sub-function nested in function of input_in_array;
 * Now, we generally test input_in_array to check whether we can store string into p.array.
 * */
void test_input_in_array()
{
    Program p;
    int i;
    init_program(&p);
    input_in_array(&p,"input_in_array.testf");
    /*no useful string in p.array[7]
     * useful string is from 0 to 6;
     * */
    assert(p.count == 7);
    assert(p.cw ==0);
    i = strsame(p.array[p.cw++],"{");
    assert(i);
    i = strsame(p.array[p.cw++],"PRINT");
    assert(i);
    i = strsame(p.array[p.cw++],"\"1 A 2 B\"");
    assert(i);
    i = strsame(p.array[p.cw++],"$A");
    assert(i);
    i = strsame(p.array[p.cw++],"=");
    assert(i);
    i = strsame(p.array[p.cw++],"#1 A 2 B#");
    assert(i);
    i = strsame(p.array[p.cw++],"}");
    assert(i);
    free_program(&p);
}
