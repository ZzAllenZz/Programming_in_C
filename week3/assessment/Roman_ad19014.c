/* Feedback from tl19232: Code works and compiles correctly and does not break
** house-style guidelines. Simple and short solution. 
** Could have checked if user input was valid roman numerals
** maybe? i.e. 'AB' prints error statement. Overall: 70%.
*/
/* Feedback from uh19168: Very good logic in coding;
   Very good in house-style;
   Just a little bit complicated in function RomanToArabic when reading it.
   Overall: 69% */
/*Feedback from ir19195
1. Include #define NDEBUG above the assert header to ignore the test function
    after code has been finalised.
2. The programme should only read roman numeral from range 1-3999.
3. Does not check that user only input upper case letters. (could be easily
    remedied by toupper())
4. Does not check to make sure the largest roman letter is always on the left
    (eg: CMM should have
    not been valid but return 1900).

overall : 65%. code complies correctly with satisfying result for most cases
*/
#include<stdio.h>
#include<string.h>
#include<assert.h>
int romanToArabic(char *roman);
void test();
int main(int argc, char **argv)
{
    test();
    if(argc==2){
        printf("The roman number %s is euqal to %d\n",argv[1],romanToArabic(argv[1]));
        }else{
            printf("ERROR:Incorrect usage,try e.g. %s XXI\n",argv[0]);
        }
    return 0;
}
int romanToArabic(char *roman)
{
    /*len is used to get the length of roman number*/
    int len = strlen(roman),i,arabic=0;

    for(i=0;i<len;i++){
        /* use switch case to choose paired value. 
        but there are six cases in subtraction system, which need we use 'if' to judge the sign.
        for example if 'I' is followed by a 'V' or 'X', it should be -1. */
        /*arabic is the final number we want.*/
        switch (roman[i])
        {
        case 'I':
            if (roman[i+1]=='V'||roman[i+1]=='X') {
                arabic -=1;
              }else {
                arabic +=1;
              }
            break;
        case 'V': 
            arabic +=5; 
            break;
        case 'X':
            if (roman[i+1]=='L'||roman[i+1]=='C') {
                arabic -=10;
            }else {
                arabic +=10;
            }
            break;
        case 'L': 
            arabic +=50;
            break;
        case 'C':
            if (roman[i+1]=='D'||roman[i+1]=='M') {
                arabic -=100;
            }else {
                arabic +=100;
            }
            break;
        case 'D': 
            arabic +=500;
            break;
        case 'M':
            arabic += 1000;
            break;
        }
    }
    return arabic;
}

void test(){
    assert(romanToArabic("MCMXCIX")==1999);
    assert(romanToArabic("MCDXCI")==1491);
    assert(romanToArabic("MCMLXVII")==1967);

}
