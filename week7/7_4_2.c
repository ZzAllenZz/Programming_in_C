#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define LEN 3
#define N 10

typedef struct boards{
  char board[N];
  struct boards *next;
}boards;

typedef enum bool{false, true}bool;

void test(void);
bool haveSolution(char* str);
void execute(char* str);
int manhatton(char* str);
boards *AllocateNode(char *s);
int findNull(char* str);
bool isValid(int index);
void swap(char* a, char* b);
bool find(char* s);
void printList(boards *l);
char *nextGeneration(char* s, int* step, boards* closelist_start,
                    boards* openlist_start, boards* openlist_current);

void put2openList(char* str, boards* openlist_current);
void put2closeList(char* str, boards* closelist_current);
bool InCloseList(char* s, boards* closelist_start);
bool InOpenList(char* s, boards* openlist_start);

int main(int argc, char *argv[])
{
  test();
  if (argc != 2 || strlen(argv[1]) != 9) {
    fprintf(stderr,"ERROR: Incorrect usage. try e.g %s 123456 78\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (haveSolution(argv[1]) == false) {
    printf("This input do not have solution.\n");
    exit(EXIT_FAILURE);
  }
  execute(argv[1]);
  return 0;
}
/***************************************************************/
void execute(char* str)
{
  boards* closelist_start = NULL, *closelist_current = NULL;
  boards* openlist_start = NULL, *openlist_current = NULL;
  char* puzzle = NULL;
  int step = 0;
  int* p_step = &step;

  openlist_start = openlist_current = AllocateNode(str);
  closelist_start = closelist_current = AllocateNode(str);
  puzzle = str;
  while(!find(puzzle)) {
    puzzle = nextGeneration(puzzle, p_step, closelist_start,
                            openlist_start, openlist_current);
    put2closeList(puzzle, closelist_current);
    printf("out3: %s\n", puzzle);
  }
  printList(closelist_start);
}
/************************找出当前节点的下一个最优节点********************/
char *nextGeneration(char* s, int* step, boards* closelist_start,
                    boards* openlist_start, boards* openlist_current)
{
  int i, index, new_index, n[4] = {-1, 1, -3, 3};
  int distance = 40, temp_distance;
  char str[N];
  static char next_step[N];

  (*step)++;
  index = findNull(s);
  printf("step = %d, null = %d\n", *step, index);
  for (i = 0; i <= 3; i++) {
    new_index = index + n[i];
    if (isValid(new_index)) {
      strcpy(str, s);
      swap(&str[index], &str[new_index]);
      if (!InCloseList(str, closelist_start) &&
          !InOpenList(str, openlist_start)) {
        put2openList(str, openlist_current);
        temp_distance = *step + manhatton(str);
        if (temp_distance < distance) {
          distance = temp_distance;
          strcpy(next_step, str);
          printf("ine1: %s\n", next_step);
        }
      }
    }
  }
  printf("ine2: %s\n", next_step);
  return next_step;
}
/*******************判断是否在openlist里面*********************/
bool InOpenList(char* s, boards* openlist_start)
{
  boards* l;

  l = openlist_start;
  do{
    if (strcmp(l->board, s) == 0) {
      return true;
    }
    l = l->next;
  }while(l != NULL);
  return false;
}
/*******************判断是否在closelist里面*********************/
bool InCloseList(char* s, boards* closelist_start)
{
  boards* l;

  l = closelist_start;
  do{
    if (strcmp(l->board, s) == 0) {
      return true;
    }
    l = l->next;
  }while(l != NULL);
  return false;
}
/********************放入closelist*********************/
void put2closeList(char* str, boards* closelist_current)
{
  closelist_current->next = AllocateNode(str);
  closelist_current = closelist_current->next;
}
/********************放入openlist*********************/
void put2openList(char* str, boards* openlist_current)
{
  openlist_current->next = AllocateNode(str);
  openlist_current = openlist_current->next;
}
/**************************print***********************************/
void printList(boards *l)
{
  if (l == NULL ) return;

  printf("%s\n", l->board);
  printList(l->next);
}
/*****************判断是否成功*****************/
bool find(char* s)
{
  char s1[] = "12345678 ";
  if(strcmp(s, s1) == 0)
    return true;
  return false;
}
/**************交换两个位置***********************/
void swap(char* a, char* b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
/**********************判断某位置是否可以移动***********************/
bool isValid(int index)
{
  if (index < 0 || index >= 9)
    return false;
  return true;
}
/*********************找到空格的位置***********************/
int findNull(char* str)
{
  int i;

  for (i = 0; i < N; i++) {
    if (*str++ == ' ') {
      return i;
    }
  }
  return -1;
}
/************************计算Manhatton距离**********************/
int manhatton(char* str)
{
  char puzzle[LEN][LEN];
  char target[LEN][LEN] = {{'1','2','3'},{'4','5','6'},{'7','8',' '}};
  int i, j, m, n, manhatton = 0;

  for (i = 0; i < LEN; i++) {
    for (j = 0; j < LEN; j++) {
      puzzle[i][j] = *str++;
    }
  }
  for (i = 0; i < LEN; i++) {
    for (j = 0; j < LEN; j++) {
      for (m = 0; m < LEN; m++) {
        for (n = 0; n < LEN; n++) {
          if (puzzle[i][j] != ' ' && puzzle[i][j] == target[m][n]) {
            manhatton += (abs(m - i) + abs(n - j));
          }
        }
      }
    }
  }
  return manhatton;
}
/***************************************************************/
boards *AllocateNode(char *s)
{
  boards *p;

  p = (boards *)malloc(sizeof(boards));
  if(p== NULL){
    printf("cannot Allocate Node.\n");
    exit(EXIT_FAILURE);
  }
  strcpy(p->board, s);
  p->next = NULL;
  return p;
}
/***********************判断输入是否有解***********************/
bool haveSolution(char* str)
{
  char s[9];
  int i, j, count = 0;

  for (i = 0; i < 9; i++) {
    s[i] = *str++;
    if (s[i] == ' ')
      s[i] = '0';
  }
  for (i = 1; i < 9; i++) {
    for (j = 0; j < i; j++) {
      if (s[i] != '0' && s[j] > s[i]) {
        count++;
      }
    }
  }
  if (count % 2 != 0)
    return false;
  return true;
}
/**************************************************************/
void test(void)
{
  char s1[] = "12345678 ";
  char s2[] = "1234567 8";
  char s3[] = " 12345678";

  assert(manhatton(s1) == 0);
  assert(manhatton(s2) == 1);
  assert(findNull(s1) == 8);
  assert(findNull(s2) == 7);
  assert(findNull(s3) == 0);
  assert(isValid(4) == true);
  assert(isValid(9) == false);
  assert(find(s1) == true);
  assert(find(s2) == false);

}
