#include <stdio.h>
#include <assert.h>

int romanToArabic(char *);
int roman_calculate(char **);
void test(void);

int main(int argc, char **argv)
{
    test();
    if (argc == 2)
    {
        printf("The roman numeral %s is equal to %d\n", \
        argv[1], romanToArabic(argv[1]));
    }
    else
    {
        printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
    }
    return 0;
}

void test(void)
{
    char five[] = "V";
    char fifty[] = "L";
    char five_hrd[] = "D";
    char one_thous[] = "M";
    char one[] = "I", four[] = "IV", nine[] = "IX";
    char ten[] = "X", fourty[] = "XL", ninty[] = "XC";
    char one_hrd[] = "C", four_hrd[] = "CD", nine_hrd[] = "CM";
    char fourfourfour[] = "CDXLIV";
    char *pointer = four_hrd;
    char **cursor = &pointer;

    assert(roman_calculate(cursor) == 400);
    assert(pointer - four_hrd == 2);
    pointer = one_hrd;
    cursor = &pointer;
    assert(roman_calculate(cursor) == 100);
    assert(pointer - one_hrd == 1);

    assert(romanToArabic(five) == 5);
    assert(romanToArabic(fifty) == 50);
    assert(romanToArabic(five_hrd) == 500);
    assert(romanToArabic(one_thous) == 1000);
    assert(romanToArabic(one) == 1);
    assert(romanToArabic(four) == 4);
    assert(romanToArabic(nine) == 9);
    assert(romanToArabic(ten) == 10);
    assert(romanToArabic(fourty) == 40);
    assert(romanToArabic(ninty) == 90);
    assert(romanToArabic(one_hrd) == 100);
    assert(romanToArabic(four_hrd) == 400);
    assert(romanToArabic(nine_hrd) == 900);
    assert(romanToArabic(fourfourfour) == 444);
}

/* 
Called by main function
pass a char pointer to this function 
return the arabic value of roman number in base 10
*/
int romanToArabic(char *roman_str)
{
    int count = 0;
    char *str_end;
    char **cursor = &roman_str; /*cursor is a pointer that points to a pointer*/
    str_end = roman_str;
    /* Move the pointer str_end to the end */
    while (*str_end != '\0')
    {
        str_end++;
    }
    while (*cursor < str_end)
    {
        count += roman_calculate(cursor);
    }
    return count;
}

/* Identify every roman number and return the value */
int roman_calculate(char **cursor)
{
    char now_char = **cursor;
    /* flag is the step length of the pointer that the cursor points to*/
    int arabic_num = 0, flag = 1; 
    switch(now_char)
    {
        case 'V': 
        arabic_num = 5; 
        break;

        case 'L': 
        arabic_num = 50;
        break;

        case 'D': 
        arabic_num = 500;
        break;

        case 'M': 
        arabic_num = 1000;
        break;

        case 'I':
            if (*(*cursor + 1) == 'V')
            {
                arabic_num = 4;
                flag = 2;
            }
            else
            {
                if (*(*cursor + 1) == 'X')
                {
                    arabic_num = 9;
                    flag = 2;
                }
                else
                {
                    arabic_num = 1;
                }
            }
        break;

        case 'X':
            if (*(*cursor + 1) == 'L')
            {
                arabic_num = 40;
                flag = 2;
            }
            else
            {
                if (*(*cursor + 1) == 'C')
                {
                    arabic_num = 90;
                    flag = 2;
                }
                else
                {
                    arabic_num = 10;
                }
            }
        break;

        case 'C':
            if (*(*cursor + 1) == 'D')
            {
                arabic_num = 400;
                flag = 2;
            }
            else
            {
                if (*(*cursor + 1) == 'M')
                {
                    arabic_num = 900;
                    flag = 2;
                }
                else
                {
                    arabic_num = 100;
                }
            }
        break;
    }
    /* Move the pointer 'roman_str' according to the flag
    if the roman number just identified in this function is two chars long,
    then move the roman_str by 2 chars long.
    if it is one char long,
    then move the roman_str by 1 char long.
    */
    (*cursor) += flag; 
    return arabic_num;
}
