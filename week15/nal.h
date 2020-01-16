#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#include <math.h>
#include "mvm.h"

#define LIST_SIZE 256
#define DEFAULTSIZE  20
#define REQUIRED 2 /*required arguments in command line*/
#define OFFSET 1
#define FIRST 0
#define SECOND 1
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define RNDBASE 100
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

typedef struct program{
    char **array;
    mvm *map;
    int count;
    int cw;
    struct list *lt; /*A structure of list used to record how many Programs created*/

} Program;
typedef struct list{
    Program *prog[LIST_SIZE]; /*an array of pointer of Program */
    int size;
} List;

void init_program(Program *p);
void free_program(Program *p);
void check_argc(int argc);
void check_allocate(char *str);
void resize_array(Program *p);


void input_in_array(Program *p,char *filename);
void is_print(FILE *fp,Program *p); /*要说明 是为了 space才这么复杂的处理*/
void is_setvar(FILE *fp,Program *p);
void is_ifcond(FILE *fp,Program *p);
void is_file(FILE *fp, Program *p);
void read_varcon(FILE *fp,Program *p);
void read_var_or_numcon(FILE *fp,char *str,Program *p,int i);
void read_strcon(FILE *fp,char *str,Program *p,int i,char flag);

void interp_print(Program *p);

void parse_file(Program *p);
void parse_in2str(Program *p);
void parse_innum(Program *p);
void parse_jump(Program *p);
void parse_print(Program *p);
void parse_rnd(Program *p);
void parse_ifcondition(Program *p);
void parse_inc(Program *p);
void parse_set_variable(Program *p,char flag);

void check_symbol(Program *p, char* symbol); /*把check函数 变成 传递对应的东西，而不是p...不能 因为要报错用*/
void check_strcon(Program *p);
void check_numcon(Program *p);
void check_var(Program *p,char flag);
void check_declare(Program *p);

void interp_set_var(Program *p,char symbol);
void interp_rnd(Program *p);
void interp_innum(Program *p);
void interp_in2str(Program *p);
void interp_file(Program *p);
void interp_abort(Program *p);
void interp_jump (Program *p);
void interp_inc (Program *p);
void interp_ifcondition(Program *p);
void is_ifmatched(Program *p, char **str,int *mark);

void escape(Program *p);
char *take_quota(char *content);
char *translate_hashes(char *content);
void get_str(char **str);
void insert_map (Program *p, char *str);
int is_meet(Program *p, char **str, int mark);

void Prog(Program *p);
void Instrs(Program *p);
void Instruct(Program *p);
