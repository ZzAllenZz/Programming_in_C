#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
/* #define NDEBUG 这句话重要！！！*/

int romanToArabic( char *roman );

void test(void)
{
    assert(romanToArabic("I") == 1);
    assert(romanToArabic("MCMLXVII") == 1967);
    assert(romanToArabic("MCDXCI") == 1491);
}

int main(int argc, char **argv)
{
    test();
    if( argc==2 )
    {
        printf("The roman numeral %s is equal to %d\n", argv[1], romanToArabic(argv[1]));
    }
    else
    {
        printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
    }
    return 0;
    
}

int romanToArabic( char *roman )
{
    int i, result = 0;
    /*printf("Please enter a Roman number(use capital alphabet and maximum length is 20): \n");
    //scanf("%s", &roman[20]); error:如果没有给数组赋值，那么这里必须定义数组的长度！！！并且Roman的占位符不能是%d */
    for(i = 0; i < (int)(strlen(roman)); i++)/* warning:这里不能写strlen(roman[20]) */
    {
        /*roman[i] = toupper(roman[i]);*/
        if(roman[i] == 'I')
        {
            if(roman[i + 1] == 'V' || roman[i + 1] == 'X')
            {
                roman[i] = 'O';
            }
            else
                roman[i] = 'I';
        }
        if(roman[i] == 'X')
        {
            if(roman[i + 1] == 'L' || roman[i + 1] == 'C')
            {
                roman[i] = 'P';
            }
            else
                roman[i] = 'X';
        }
        if(roman[i] == 'C')
        {
            if(roman[i + 1] == 'D' || roman[i + 1] == 'M')
            {
                roman[i] = 'Q';
            }
            else
                roman[i] = 'C';
        }
        switch (roman[i])
        {
            case 'I':  result += 1;
                break;
            case 'O':  result -= 1;
                break;
            case 'V':  result += 5;
                break;
            case 'X':  result += 10;
                break;
            case 'P':  result -= 10;
                break;
            case 'L':  result += 50;
                break;
            case 'C':  result += 100;
                break;
            case 'Q':  result -= 100;
                break;
            case 'D':  result += 500;
                break;
            case 'M':  result += 1000;
                break;
            default: break;
        }
    }
    return result;
    
}
