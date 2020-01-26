#include "nal.h"
#include <assert.h>

/*In order to test every line of code, I write a test-function for almost each function;
 * and deploy the required environment before test each functions;
 * For some untestable functions like interp_print (print out something)
 * and interp_in2str(scanf from keyboards), I have test them in .nal file;*/
void test_init_and_free_program();
void test_check_argc();
void test_resize_array();
void test_read_varcon();
void test_is_xxx();
void test_input_in_array();
void test_parse_print();
void test_parse_and_interp_file();
void test_parse_and_interp_jump();
void test_rnd_and_inc();
void test_set_and_ifcond();
void test_in2str_and_innum();
void test_function_with_return_value();
void testmvm();
#ifdef EXTENT
void teststack();
#endif
void test()
{
    printf("Basic Function Tests ... Start\n");
    check_argc(2);
    test_init_and_free_program();
    test_check_argc();
    test_resize_array();
    test_read_varcon();
    test_is_xxx();
    test_input_in_array();
    test_parse_print();
    test_parse_and_interp_file();
    test_parse_and_interp_jump();
    test_rnd_and_inc();
    test_set_and_ifcond();
    test_in2str_and_innum();
    test_function_with_return_value();
    testmvm();
#ifdef EXTENT
    teststack();
#endif
    printf("Basic Function Tests ... Finish\n");
}

void test_function_with_return_value()
{
    char *str;
    int i;

    assert(is_strcon("hello") == FALSE);
    assert(is_strcon("\"hello\"") == TRUE);
    assert(is_strcon("\"hello#") == FALSE);
    assert(is_strcon("#hello\"") == FALSE);
    assert(is_strcon("#hello#") == TRUE);
    assert(is_strcon("#hello 123 word#") == TRUE);


    assert(is_numcon(".a123") == FALSE);
    assert(is_numcon(".123") == TRUE);
    assert(is_numcon("1.23.4") == FALSE);


    assert(is_var("%ABC",'%') == TRUE);
    assert(is_var("$ABC",'%') == FALSE);
    assert(is_var("%aBC",'%') == FALSE);
    assert(is_var("%ABC12",'%') == FALSE);
    assert(is_var("ABC",'%') == FALSE);


    assert(is_var("$ABC",'$') == TRUE);
    assert(is_var("$abc",'$') == FALSE);
    assert(is_var("$ABC123",'$') == FALSE);
    assert(is_var("%ABC",'$') == FALSE);
    assert(is_var("ABC",'$') == FALSE);



    str = translate_hashes("#nopqrstuvwxyzabcdefghijklm#");
    i = strsame(str,"\"abcdefghijklmnopqrstuvwxyz\"");
    assert(i);
    free(str);

    str = translate_hashes("#NOPQRSTUVWXYZABCDEFGHIJKLM#");
    i = strsame(str,"\"ABCDEFGHIJKLMNOPQRSTUVWXYZ\"");
    assert(i);
    free(str);

    str = translate_hashes("#5678901234#");
    i = strsame(str,"\"0123456789\"");
    assert(i);
    free(str);

    str = take_quota("\"hello world\"");
    i = strsame(str,"hello world");
    assert(i);
    free(str);

    str = take_quota("#nopqr#");
    i = strsame(str,"abcde");
    assert(i);
    free(str);

    str = take_quota("#IJKLM#");
    i = strsame(str,"VWXYZ");
    assert(i);
    free(str);

    str = take_quota("123456");
    i = strsame(str,"123456");
    assert(i);
    free(str);

    str = take_quota("#123#");
    i = strsame(str,"678");
    assert(i);
    free(str);
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
    int i;
    init_program(&p);
    p.count = ONE;
    resize_array(&p);
    /*if we do not resize array, we cannot access to p.array[1]
     *and Sanitize and Valgrind will report heap-buffer-overflow.
     * */
    p.array[p.count] = "HELLO WORLD";
    assert(p.array[p.count]!=NULL);
    i = strsame(p.array[p.count],"HELLO WORLD");
    assert(i);
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

void test_parse_print()
{
    Program p;
    int i;
    init_program(&p);
    input_in_array(&p,"PRINT.testf");
    p.cw = ONE;
    parse_print(&p);
    assert(p.cw==TWO);
    i = is_strcon(p.array[p.cw]);
    assert(i);
    p.cw = THREE;
    parse_print(&p);
    i = is_strcon(p.array[p.cw]);
    assert(i);
    assert(p.cw==4);


    p.cw = 8;
    parse_print(&p);
    i = is_var(p.array[p.cw],'$');
    assert(i);
    assert(p.cw==9);

    p.cw = 13;
    parse_print(&p);
    i = is_var(p.array[p.cw],'%');
    assert(i);
    assert(p.cw==14);

    free_program(&p);
}

void test_parse_and_interp_file()
{
    Program p;
    int i;
    init_program(&p);
    input_in_array(&p,"FILE+JUMP.testf");

    p.cw = ONE;
    parse_file(&p);
    assert(p.cw==TWO);
    i = is_strcon(p.array[p.cw]);
    assert(i);

    /*test function of interp_file */
    interp_file(&p);
    /*actually,because we do not # define INTERP,
     * the sub-file is just act like a parser*/
    assert(p.cw==2);

    p.cw = THREE;
    parse_file(&p);
    i = is_strcon(p.array[p.cw]);
    assert(i);
    assert(p.cw==4);

    free_program(&p);
}

void test_parse_and_interp_jump()
{
    Program p;
    int i;
    init_program(&p);
    input_in_array(&p,"FILE+JUMP.testf");
    p.cw = 5;
    parse_jump(&p);
    assert(p.cw==6);
    i = is_numcon(p.array[p.cw]);
    assert(i);

    p.cw = 6;
    interp_jump(&p);
    /*JUMP 2 make p.cw = 1
     * because p.cw will +1 before it goes into next Instruct;*/
    assert(p.cw==1);

    free_program(&p);
}

void test_rnd_and_inc()
{
    Program p;
    int i,number1,number2;
    char *str;
    init_program(&p);
    input_in_array(&p,"RND+INC.testf");
    /*test parser and interpreter of RND*/
    p.cw = ONE;
    parse_rnd(&p);
    assert(p.cw==4);
    interp_rnd(&p);

    str = mvm_search(p.map,p.array[THREE]);
    assert(str != NULL);
    number1 = atoi(str);
    i = (number1>=0 &&number1<=99);
    assert(i);

    /*test parser and interpreter of INC*/
    p.cw = 5;
    parse_inc(&p);
    assert(p.cw==8);
    interp_inc(&p);

    str = mvm_search(p.map,p.array[THREE]);
    assert(str != NULL);
    number2 = atoi(str);
    i = (number2 == number1+1);
    assert(i);

    free_program(&p);
}


void test_set_and_ifcond()
{
    Program p;
    int i,mark = 0,success;
    char *str;
    char *temp[THREE];
    init_program(&p);
    input_in_array(&p,"SET+IF.testf");

    p.cw = ONE;
    parse_set_variable(&p,'%');
    assert(p.cw == 3);
    interp_set_var(&p,'1');
    str = mvm_search(p.map,p.array[ONE]);
    assert(str != NULL);
    i = (strsame(str,p.array[p.cw]));
    assert(i);

    p.cw = 4;
    parse_set_variable(&p,'%');
    assert(p.cw == 6);
    interp_set_var(&p,'1');
    str = mvm_search(p.map,p.array[4]);
    assert(str != NULL);
    i = (strsame(str,p.array[p.cw]));
    assert(i);


    p.cw = 7;
    parse_ifcondition(&p);
    assert(p.cw == 17);
    /*Test sub-function in interp_ifcond*/
    p.cw = 7;
    temp[ZERO] = p.array[p.cw];
    p.cw = p.cw + TWO;
    is_ifmatched(&p,temp,&mark);
    assert(mark != 2);
    success = is_meet(&p,temp,mark);
    assert(success==0);

    /*Test interp_ifcond*/
    p.cw = 12;
    interp_ifcondition(&p);
    assert(p.cw == 17 );

    free_program(&p);
}

void test_in2str_and_innum()
{
    Program p;
    init_program(&p);
    input_in_array(&p,"INPUT.testf");

    p.cw = ONE;
    parse_in2str(&p);
    assert(p.cw == 6);
    p.cw = 7;
    parse_innum(&p);
    assert(p.cw == 10);

    free_program(&p);
}



void testmvm()
{

    int i, j;
    mvm *m;
    char* str;
    char** av;
    char animals[5][10] = {"cat",  "dog",  "bird",  "horse", "frog"};
    char  noises[5][10] = {"meow", "bark", "tweet", "neigh", "croak"};

    /* Set up empty array */
    m = mvm_init();
    assert(m != NULL);
    assert(mvm_size(m)==0);

    /* Building and Searching */
    for(j=0; j<5; j++){
        mvm_insert(m, animals[j], noises[j]);
        assert(mvm_size(m)==j+1);
        i = strcmp(mvm_search(m, animals[j]), noises[j]);
        assert(i==0);
    }

    /* Test building & printing */
    str = mvm_print(m);
    i = strcmp(str, "[frog](croak) [horse](neigh) [bird](tweet) [dog](bark) [cat](meow) ");
    assert(i==0);
    free(str);

    /* Search for non-existent key */
    /* No-one knows what the fox says ? */
    assert(mvm_search(m, "fox") == NULL);

    /* Deletions - middle, then front */
    mvm_delete(m, "dog");
    assert(mvm_size(m)==4);
    str = mvm_print(m);
    i = strcmp(str, "[frog](croak) [horse](neigh) [bird](tweet) [cat](meow) ");
    assert(i==0);
    free(str);
    mvm_delete(m, "frog");
    assert(mvm_size(m)==3);
    str = mvm_print(m);
    i = strcmp(str, "[horse](neigh) [bird](tweet) [cat](meow) ");
    assert(i==0);
    free(str);

    /* Insert Multiple Keys */
    mvm_insert(m, "frog", "croak");
    mvm_insert(m, "frog", "ribbit");
    assert(mvm_size(m)==5);
    str = mvm_print(m);
    i = strcmp(str, "[frog](ribbit) [frog](croak) [horse](neigh) [bird](tweet) [cat](meow) ");
    free(str);
    assert(i==0);

    /* Search Multiple Keys */
    str = mvm_search(m, "frog");
    i = strcmp(str, "ribbit");
    assert(i==0);

    /* Multisearching */
    av = mvm_multisearch(m, "cat", &i);
    assert(i==1);
    i = strcmp(av[0], "meow");
    assert(i==0);
    free(av);
    av = mvm_multisearch(m, "horse", &i);
    assert(i==1);
    i = strcmp(av[0], "neigh");
    assert(i==0);
    free(av);
    av = mvm_multisearch(m, "frog", &i);
    assert(i==2);
    i = strcmp(av[0], "ribbit");
    j = strcmp(av[1], "croak");
    assert((i==0)&&(j==0));
    free(av);

    /* Delete Multiple Keys */
    mvm_delete(m, "frog");
    assert(mvm_size(m)==4);
    mvm_delete(m, "frog");
    assert(mvm_size(m)==3);
    str = mvm_print(m);
    i = strcmp(str, "[horse](neigh) [bird](tweet) [cat](meow) ");
    assert(i==0);
    free(str);

    /* Weird NULL insert() edge cases */
    mvm_insert(m, NULL, "quack");
    assert(mvm_size(m)==3);
    mvm_insert(NULL, "duck", "quack");
    assert(mvm_size(m)==3);
    mvm_insert(m, "duck", NULL);
    assert(mvm_size(m)==3);

    /* Weird NULL delete() edge cases */
    mvm_delete(m, "");
    assert(mvm_size(m)==3);
    mvm_delete(m, NULL);
    assert(mvm_size(m)==3);
    mvm_delete(NULL, "frog");
    assert(mvm_size(m)==3);
    mvm_delete(m, "bird");
    assert(mvm_size(m)==2);
    str = mvm_print(m);
    i = strcmp(str, "[horse](neigh) [cat](meow) ");
    assert(i==0);
    free(str);

    /* Freeing */
    mvm_free(&m);
    assert(m==NULL);
    assert(mvm_size(m)==0);

}
#ifdef EXTENT
void teststack()
{
    Stack *s;
    int i,j;
    char *str;
    float num;
    char animals[5][10] = {"cat",  "dog",  "bird",  "horse", "frog"};

    assert(is_operator('+'));
    assert(is_operator('-'));
    assert(is_operator('*'));
    assert(is_operator('/'));
    num = operation('+',1.1,2.2);
    assert(num-3.3<0.00005);
    num = operation('*',2,10);
    assert(num-20<0.00005);



    s= init_stack();
    assert(s->top == 0);
    for(i = 0; i< 5; i++){
        push_stack(s,animals[i]);
        j = strsame(s->data[s->top-OFFSET],animals[i]);
        assert(j == 1);
    }
    assert(s->top == 5);

    for(i = 0; i< 5; i++){
        pop_stack(s,&str);
        j = strsame(str,animals[5-OFFSET - i]);
        assert(j == 1);
    }
    assert(is_empty(s));
    free(s);


}
#endif
