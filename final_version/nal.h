#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#include <math.h>
#include "mvm.h"
#ifdef EXTENT
#include "extent.h"
#endif

#define LIST_SIZE 256 /*Max number of Programs that can conduct simultaneously  */
#define DEFAULTSIZE  20 /*Default size of array[p->cw]*/
#define GAP 0.00005 /*Used for comparing two float number*/
#define REQUIRED 2 /*Required arguments in command line*/
#define OFFSET 1 /*One location offset*/

#define FIRST 0 /*For indexing*/
#define SECOND 1 /*For indexing*/

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3

#define RNDBASE 100 /*Used in RND*/

#define ROT13 13
#define ROT5 5
#define strsame(A,B) (strcmp((A),(B))==0)

#define ERROR_1(PHRASE) {\
fprintf(stderr,"Fatal Error: %s occured in %s, line %d\n",\
PHRASE,__FILE__,__LINE__);\
exit(1);\
}
#define ERROR_2(EXPLAIN,WORD,NUMBER){\
fprintf(stderr,"%s %s (WORD %d) in %s, line %d\n",\
EXPLAIN,WORD,NUMBER,__FILE__,__LINE__);\
exit(2);\
}
typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct program{
    char **array;/*Used to store tokens*/
    mvm *map;/*Used to store VAR*/
    int count;/*Total tokens read in*/
    int cw;/*Current word to index token in recursion*/
    struct list *lt;
    /*A structure of list used to record how many Programs created*/
} Program;

typedef struct list{
    Program *prog[LIST_SIZE]; /*An array of pointer of Program */
    int size;
} List;


void init_program(Program *p);
void free_program(Program *p);
/*Check the arguments in command line == 2 */
void check_argc(int argc);
/*Check whether it has successfully allocated a memory location for char *str*/
void check_allocate(char *str);
/*Resize the array according to p->count*/
void resize_array(Program *p);


/*Read in tokens from file to p->array */
void input_in_array(Program *p,char *filename);
void check_special_case(FILE *fp,Program *p);
/*is_... functions exist mainly because we need to deal with space ' ' in VARCON */
void check_special_case(FILE *fp,Program *p);
/*Deal with when token is "PRINT" OR "PRINTN" */
void is_print(FILE *fp,Program *p);
/*Deal with when token is to SET VAR*/
void is_setvar(FILE *fp,Program *p);
/*Deal with when token is "IFEQUAL" or "IFGREATER"*/
void is_ifcond(FILE *fp,Program *p);
/*Deal with when token is "FILE"*/
void is_file(FILE *fp, Program *p);


/*Put VARCON from file to p->array*/
void read_varcon(FILE *fp,Program *p);
/*Nested in read_varcon*/
void read_var_or_numcon(FILE *fp,char *str,Program *p,int i);
/*Nested in read_varcon*/
void read_strcon(FILE *fp,char *str,Program *p,int i,char flag);


void parse_file(Program *p);
void interp_file(Program *p);

void interp_abort(Program *p);

void parse_in2str(Program *p);
void interp_in2str(Program *p);

void parse_innum(Program *p);
void interp_innum(Program *p);

void parse_jump(Program *p);
void interp_jump (Program *p);

void parse_print(Program *p);
void interp_print(Program *p);

void parse_rnd(Program *p);
void interp_rnd(Program *p);

void parse_ifcondition(Program *p);
void interp_ifcondition(Program *p);
/*Store two VARCONs in ifcond
 *mark is used to present whether two VARCONs are matched*/
void is_ifmatched(Program *p, char **str,int *mark);
/*Used to present whether IFCOND is met*/
bool is_meet(Program *p, char **str, int mark);
/*Escape a couple { } when IDCOND is not met*/
void escape(Program *p);


void parse_inc(Program *p);
void interp_inc (Program *p);

void parse_set_variable(Program *p,char flag);
void interp_set_var(Program *p,char symbol);

/*check_...function is used to ensure the input is valid
 * if not, report an error*/
void check_symbol(Program *p, char* symbol);
void check_strcon(Program *p);
void check_numcon(Program *p);
void check_var(Program *p,char flag);
/*Make sure VAR has been defined*/
void check_declare(Program *p);

/*Used take off double quota in STRCON*/
char *take_quota(char *content);
/*Used to translate ROT to Plain*/
char *translate_hashes(char *content);
/*Used to translate getchar() to get a str
 * Used in <INPUT>*/
void get_str(char **str);
/*Insert a new key (if it has existed, delete previous one)into map*/
void insert_map (Program *p, char *str);


void Prog(Program *p);
void Instrs(Program *p);
void Instruct(Program *p);

bool is_strcon(char *str);
bool is_numcon(char *str);
bool is_var(char *str,char flag);

#ifdef TEST
void test();
#endif

#ifdef EXTENT
void is_rpnope(FILE *fp, Program *p);
void parse_rpnope(Program *p);
void interp_rpnope(Program *p,int var_location, int start,int finish);
void compute(Program *p, int start, int finish);


void is_swap(FILE *fp,Program *p);
void interp_swap(Program *p);
void parse_swap (Program *p);
#endif
