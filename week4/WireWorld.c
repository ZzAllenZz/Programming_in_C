#include<stdio.h>
#include<stdlib.h>
#define LEN 40
void file2array(char *filename,char first_generation[LEN][LEN]);

void next_state(char first_generation[LEN][LEN],char next_generation[LEN][LEN]);

int surronding_cells(char generation[LEN][LEN],int row,int column);

void make_world() ;
int main(int argc,char **argv){
    char first_generation[LEN][LEN];
    char *filename = "wirewinvalid.txt";
    char next_generation[LEN][LEN];
    int i,j,k,n=0;
	file2array(filename,first_generation);

    for(i=0;i<LEN;i++){
        for(j=0;j<LEN;j++){
            printf("%c",first_generation[i][j]);
        }
        printf("\n");
    }
  
for(k=0;k<10;k++){

	next_state(first_generation,next_generation);

   for(i=0;i<LEN;i++){
        for(j=0;j<LEN;j++){
            printf("%c",next_generation[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<LEN;i++){
        for(j=0;j<LEN;j++){
	        first_generation[i][j] = next_generation[i][j];
        }
    }
}

    return 0;
}

void file2array(char *filename,char first_generation[LEN][LEN])
{
    FILE *fp;
    int i,j,c;
    
    if((fp = fopen(filename,"r"))==NULL){
        printf("Cannot open file named %s\n",filename);
        exit(1);
    }
    
    for(i=0;i<LEN;i++){
        for(j=0;j<LEN;){
            if((c=getc(fp))!='\n'){
            first_generation[i][j] = c;
			j++;	
			}
		}
	}
	fclose(fp);
}

void next_state(char first_generation[LEN][LEN],char next_generation[LEN][LEN])
{
	int i,j,n=0;
	for(i=0;i<LEN;i++){
		for(j=0;j<LEN;j++){
			if(first_generation[i][j]==' '){
				next_generation[i][j]=' ';
			}else if(first_generation[i][j]=='H'){
				next_generation[i][j]='t';
			}else if(first_generation[i][j]=='t'){
				next_generation[i][j]='c';
			}else if(first_generation[i][j]=='c'){
				n=surronding_cells(first_generation,i,j);
				if(n==1||n==2){
					next_generation[i][j]='H';
				}else{
					next_generation[i][j]='c';
				}
			}else{
				printf("A wrong char enters in row %d, column %d\n",i+1,j+1);
				exit(EXIT_FAILURE);
			}
		}
	}
}
int surronding_cells(char generation[LEN][LEN],int row,int column){
	int n=0;
	if(generation[row][column-1]=='H'){
		n++;
	}
	if(generation[row][column+1]=='H'){
		n++;
	}
	if(generation[row-1][column-1]=='H'){
		n++;
	}
		if(generation[row-1][column]=='H'){
		n++;
	}
		if(generation[row-1][column+1]=='H'){
		n++;
	}
		if(generation[row+1][column-1]=='H'){
		n++;
	}
		if(generation[row+1][column]=='H'){
		n++;
	}
		if(generation[row+1][column+1]=='H'){
		n++;
	}
	return n;
}

