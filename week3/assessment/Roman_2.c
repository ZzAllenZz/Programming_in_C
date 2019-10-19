/*Feedback from ad19014: Programe can work correctly and very good logic in coding;
But it get some warning such as  ISO C90 forbids variable length array 'a',ISO C90 forbids mixed declarations and code.
Overall: 65% 
*/ 


#include<stdio.h>
#include<string.h>
#include<assert.h>

enum combinations{I=1,V=5,X=10,L=50,C=100,D=500,M=1000,IV=4,IX=9,XL=40,XC=90,CD=400,CM=900};
int romanToArabic(char *roman );
void test(void);
int main(int argc, char **argv)
{

test();

if
( argc==2 )
	{
	printf("The roman numeral %s is equal to %d\n", argv[1], romanToArabic(argv[1]));
	}
else
	{
	printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
	}


return 0;
}

void test(void)
{
assert(romanToArabic("MCMXCIX")==1999);
assert(romanToArabic("MCMLXVII")==1967);
assert(romanToArabic("MCDXCI")==1491);
assert(romanToArabic("AX")==0);
assert(romanToArabic("DDDD")==0);
assert(romanToArabic("ac")==0);
assert(romanToArabic("c")==0);
}

int romanToArabic(char *roman )
{
/*create an array which copies from the string*/
	int N;
	N = strlen(roman);
	char a[N];
	int i;
	for(i=0;i<=N-1;i++)
	{
	a[i]='0';
	}
	strcpy(a,roman);



	int sum=0;
	for(i=0;i<=N-1;i++)
	{
/*make sure the inputs like MMMM are wrong*/

		if ((N>=4)&&a[i]==a[i+1]&&a[i]==a[i+2]&&a[i]==a[i+3])
		{
		return 0;
		}



		if (a[i]=='I')
		{
			 if(a[i+1]!='V'&&a[i+1]!='X')
			{
				sum=sum+I;
				
			}

			 else if(a[i+1]=='V')
			{
				sum=sum+IV;
				i=i+1;
			}

			 else if(a[i+1]=='X')
			{
				sum=sum+IX;
				i=i+1;
			}

			 else
				return 0;
		}


		else if(a[i]=='V')
		{
		sum=sum+V;
		}


		else if(a[i]=='X')
		{
		 if(a[i+1]!='L'&&a[i+1]!='C')
			sum=sum+X;
		 else if(a[i+1]=='L')
			{sum=sum+XL; i=i+1;}
		 else if(a[i+1]=='C')
			{sum=sum+XC; i=i+1;}
		 else
			return 0;
		}


		else if(a[i]=='L')
		sum=sum+L;


		else if(a[i]=='C')
		{
		 if(a[i+1]!='D'&&a[i+1]!='M')
			sum=sum+C;
		 else if(a[i+1]=='D')
			{
			sum=sum+CD;
			 i=i+1;
			}
		 else if(a[i+1]=='M')
			{sum=sum+CM;
			i=i+1;
			}
		 else
			return 0;
		}



		else if(a[i]=='D')
		{
		sum=sum+D;
		}
		else if(a[i]=='M')
		{
		sum=sum+M;
		}

/*make sure all inputs which does not use roman presentation are wrong */
		else
		{		
		return 0;
		}
	}

	return sum;
}

