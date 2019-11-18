#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void permute(char *a, int l, int r);
void swap(char *a, char *b);
int main()
{
    char str[] = "ABCD";
    int n = strlen(str);
    permute(str, 0, n-1);
    return 0;
}

void permute(char *a, int l, int r)
{
    int i;
    if (l == r){
        printf("%s\n", a);
        return;
    }
    for (i = l; i <= r; i++){
        swap((a+l), (a+i));
        permute(a, l+1, r);

        swap((a+l), (a+i)); /*backtrack*/
    }

}

void swap(char *a, char *b){
    char *temp;
    temp = (char *)malloc(sizeof(char));
    *temp = *a;
    *a = *b;
    *b= *temp;
}