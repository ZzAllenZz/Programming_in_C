#include "neillncurses.h"
#define NDEGUB
#define LEN 40

/*Display the wireworld in a colorful board*/ 
void display_color(char *filename);

/*Read a file into a 40*40 2D array*/
void file2array(char *filename,char first_generation[LEN][LEN]);

/*Save next generation into next_generation[LEN][LEN]  */
void next_state(char first_generation[LEN][LEN],char next_generation[LEN][LEN]);

/*Calculate the number of 'H' in 8-surrounding cells */
int surrounding_cells(char generation[LEN][LEN],int row,int column);

/*Ensure the calculation can do correctly */
char access(char generation[LEN][LEN],int row,int column);

void test(void);

int main(int argc,char **argv)
{
  if (argc != 2){
        printf("ERROR:Incorrect usage,try e.g. %s wirewcircuit1.txt",argv[0]);
        exit(EXIT_FAILURE);
    }else{
        display_color(argv[1]);
    }
    return 0;
}

void display_color(char *filename){
	NCURS_Simplewin sw;
    int i,j;
    char first_generation[LEN][LEN], next_generation[LEN][LEN];
    file2array(filename,first_generation);
    next_state(first_generation,next_generation);
	/*
	Set each element in 2D array into a colorful unit
	*/
    Neill_NCURS_Init(&sw);
    Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK, COLOR_BLACK, A_NORMAL);
    Neill_NCURS_CharStyle(&sw, "t", COLOR_RED, COLOR_RED, A_NORMAL);
    Neill_NCURS_CharStyle(&sw, "c", COLOR_YELLOW, COLOR_YELLOW, A_NORMAL);
    Neill_NCURS_CharStyle(&sw, "H", COLOR_BLUE, COLOR_BLUE, A_NORMAL);

	do{
        Neill_NCURS_PrintArray(&next_generation[0][0], LEN,LEN, &sw);
        
        /*After display this generation,transfer the next_generation to 
		  become the first_generation for next time
		*/
		for(i=0;i<LEN;i++){
            for(j=0;j<LEN;j++){
                first_generation[i][j] = next_generation[i][j];
            }
        }
        next_state(first_generation,next_generation);
        Neill_NCURS_Delay(1000.0);
        Neill_NCURS_Events(&sw);
	}while(!sw.finished);
	atexit(Neill_NCURS_Done);

	exit(EXIT_SUCCESS);

}

void file2array(char *filename,char first_generation[LEN][LEN])
{
    FILE *fp;
    int i,j,c;

    if((fp = fopen(filename,"r"))==NULL){
        printf("Cannot open file named %s\n",filename);
        exit(1);
    }
	/*
	i means the row;
	j means the column;
	*/ 
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
    /*
	n is used to receive the number of 'H' in 8-surrounding cells;
	*/
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
                n=surrounding_cells(first_generation,i,j);
                if(n==1||n==2){
                    next_generation[i][j]='H';
                }else{
                    next_generation[i][j]='c';
                }
            }else{
				/*Ensure character in original file is legal and valid */
                printf("A wrong char enter in row %d,colum %d\n",i+1,j+1);
                exit(EXIT_FAILURE);
            }
        }
    }
}


int surrounding_cells(char generation[LEN][LEN],int row,int column)
{
    int n=0,i,j;
    for(i=-1;i<2;i++){
        for(j=-1;j<2;j++){
            if(access(generation,row+i,column+j)=='H'){
            	n++;
            }
        }
    }
    return n;
}

/*if row or column is out of bound, return '\0';
  if not, it return a normal character that is in the 2D array;	
*/
char access(char generation[LEN][LEN],int row,int column)
{
    if(row<0||row>=LEN||column<0||column>=LEN){
        return '\0';
    }else{
        return generation[row][column];
    }

}

void test(void)
{
	char first_generation[LEN][LEN], next_generation[LEN][LEN];
	file2array("wirewcircuit1.txt",first_generation);
	assert(first_generation[4][4]=='t');
	assert(first_generation[5][2]=='c');
	assert(first_generation[0][0]==' ');
	assert(first_generation[4][5]=='H');
	assert(surrounding_cells(first_generation,10,3)==2);
	assert(access(first_generation,40,40)=='\0');
	assert(access(first_generation,-1,-1)=='\0');
	assert(access(first_generation,4,5)=='H');
	next_state(first_generation,next_generation);
	assert(next_generation[4][4]=='c');
	assert(next_generation[4][5]=='t');	
}



