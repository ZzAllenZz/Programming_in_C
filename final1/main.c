# include <stdio.h>
# include <stdlib.h>

int main (void)
{
/*    int num;
    char * str = "100";
    int a = 123;
    char *b  = (char *)calloc(10,sizeof(char));
    num = atoi(str);
    printf("The string 'str' is %s and the number 'num' is %d. \n",
           str, num);
    itoa(a, b, 10);
    printf("The number 'a' is %d and the string 'b' is %s. \n" ,
           a, b);
    free(b);*/

    char *str = calloc(5,sizeof(char));
    printf("input a str\n");
    scanf("%s",str);
    printf("the str is %s",str);
    free(str);







    return 0;
}
