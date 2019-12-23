#include <stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define NUMBER 2891
#define WIDTH 8
int find_matching_prime(char a);
//void find_word();
void find_result(char *lword);

int main (void){
	char *lword = "compiler";
//	int i,lenl= strlen(lword);
//	long long productl;
//	printf("the length of lword is %d\n",lenl);
//	for(i=0;i<lenl;i++){
//		productl *=find_matching_prime(*(lword+i));
//	}
//	printf("the product of lword is %ld",productl);
//	int i;
//	for(i=0;i<NUMBER;i++){
//		printf("start\n");
//		printf("%d\n",i);
//	}
	find_result(lword);


} 
void find_result(char *lword){
	int lenl,i;
	int lens1,lens2,j,k,m;
	long long products1=1,products2=1,productl=1;
	char **p;
	FILE *fp;
	
	p = (char **)malloc(sizeof(char **)*NUMBER);
	
	for(i=0;i<NUMBER;i++){
		*(p+i) = (char *)malloc(sizeof(char)*WIDTH);
	}	

	fp = fopen("34words.txt","r");
	if(fp==NULL){
		printf("error");
		exit(1);
	}
	
	lenl= strlen(lword);
	for(i=0;i<lenl;i++){
		productl *=find_matching_prime(*(lword+i));
	}
	printf("the product of lword is %lld\n",productl);
	for(i=0;i<NUMBER;i++){
		fscanf(fp,"%s",*(p+i));
	}

	for(i=0;i<NUMBER;i++){
		products1=1;

//		printf("\n");
//		printf("i= %d\n",i);
		lens1= strlen(*(p+i));
//		printf("the len of sword1 = %d\n",lens1);

		for(j=0;j<lens1;j++){
			products1 *= find_matching_prime(*(*(p+i)+j));
//			printf("j= %d\n",j);
		//	printf("the product [%d]=%d\n",j,products1);
		}
//		printf("the product of sword1 = %lld\n",products1);	
		
		if((productl%products1)==0){
			for(k=0;k<NUMBER;k++){
				products2=1;
				lens2=strlen(*(p+k));
				if(lens2==(lenl-lens1)){
					for(m=0;m<lens2;m++){
						products2 *= find_matching_prime(*(*(p+k)+m));
					}
//					printf("the product of sword2 = %lld\n",products2);
//					printf("%lld\n",products1*products2);
					
					if((products2*products1)==productl){
//						printf("yes\n");
//						printf("i= %d\n j= %d\n k=%d\n m=%d\n",i,j,k,m);
						printf("%s %s\n",*(p+i),*(p+k));
//						printf("%s %s",*(p+i)+j,*(p+k)+m);
					}
//					else{
//						printf("%d",i);
//						printf("no\n"); 
//					}
				}
			}
		}
	}
}

int find_matching_prime(char a){
	switch(a){
		case 'a':
			return 2;
		case 'b':
			return 3;
		case 'c':
			return 5;
		case 'd':
			return 7;
		case 'e':
			return 11;
		case 'f':
			return 13;
		case 'g':
			return 17;
		case 'h':
			return 19;
		case 'i':
			return 23;
		case 'j':
			return 29;
		case 'k':
			return 31;
		case 'l':
			return 37; 
		case 'm':
			return 41;
		case 'n':
			return 43;
		case 'o':
			return 47;
		case 'p':
			return 53;
		case 'q':
			return 59;
		case 'r':
			return 61;
		case 's':
			return 67;
		case 't':
			return 71;
		case 'u':
			return 73;
		case 'v':
			return 79;
		case 'w':
			return 83;
		case 'x':
			return 89;
		case 'y':
			return 97;
		case 'z':	
			return 101;	
		default :
			printf("case error\n");
			exit(1);	
	}
}
