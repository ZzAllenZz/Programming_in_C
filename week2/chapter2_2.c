#include<stdio.h>
#include<ctype.h>
#include<time.h>
#include<math.h>
void create_consonant_and_count(char *consonant,int *count_consonant);
int testPrimes(int testNumber);
void get_name(char *consonant,int *count_consonantchar,char *vowel,int *count_vowel);

int main(void){
    clock_t start,finish;
    double duration;
    start = clock();
    int i,j;
    char consonant[21],vowel[5]={'a','e','i','o','u'};
    int count_consonant[21],count_vowel[5]={1,5,9,15,21};

    /*because array itself is very likely a pointer,no need to add'*' */
    create_consonant_and_count(consonant,count_consonant);
    for(i =0;i<21;i++){
    	printf("%c  %d\n",consonant[i],count_consonant[i]);
    	
	}
	for(j=0;j<5;j++){
		printf("%c  %d\n",vowel[j],count_vowel[j]);
	}
    get_name(consonant,count_consonant,vowel,count_vowel);
    finish = clock();
    duration = (double)((finish - start)/CLOCKS_PER_SEC);
    printf("%.30f",duration);
    return 0;
}


void create_consonant_and_count(char *consonant,int *count_consonant){
    int i,j;
    for(i=0,j=0;i<21;i++,j++){
        consonant[i]= (char)('a'+j);
        count_consonant[i]=j+1;
        while(consonant[i]=='a'||consonant[i]=='e'||
        consonant[i]=='i'||consonant[i]=='o'||consonant[i]=='u'){
            j++;
            consonant[i]= (char)('a'+j);
            count_consonant[i]=j+1;
        }


    }

}
int testPrimes(int testNumber){
    //to test whether a number is a prime. 1:prime, 0: not a prime
    // count is used to record how many number can exactly devide the testNumber. 
	int i ,count = 0;
	double result;
	if(testNumber%2 ==0) return 0;
	result=fmod(sqrt(testNumber),1.0);
	if(result==0) return 0;
	for(i =1;i<=(int)(sqrt(testNumber));i++){
	if(testNumber%i == 0){
	count++;
	}
	}
	if(count<=1) return 1;
	else return 0; // if count>=3, it is not a prime.
	}

void get_name(char *consonant,int *count_consonant,char *vowel,int *count_vowel){
    int i,j,k,number,count=1;

    for(i=0;i<21;i++){
        for(j=0;j<5;j++){
        	if(testPrimes(count_consonant[i]*2+count_vowel[j])){
        		printf("%d ",count_consonant[i]*2+count_vowel[j]);
        		printf("%d: %c%c%c\n",count,consonant[i],vowel[j],consonant[i]);
        		count++;} 
        	if(testPrimes(count_consonant[i]+count_vowel[j]*2)){
				printf("%d ",count_consonant[i]+count_vowel[j]*2);
				printf("%d: %c%c%c\n",count,vowel[j],consonant[i],vowel[j]);
				count++;
				}
			

        }
    }
} 
