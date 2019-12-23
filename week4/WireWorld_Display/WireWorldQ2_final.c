#include "neillncurses.h"

#define LEN 40
void file2array(char *filename,char first_generation[LEN][LEN]);

void next_state(char first_generation[LEN][LEN],char next_generation[LEN][LEN]);

int surronding_cells(char generation[LEN][LEN],int row,int column);

void display_color(char *filename);

char access(char generation[LEN][LEN],int row,int column);


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
                                printf("A wrong char enter in row %d,colum %d\n",i+1,j+1);
                                exit(EXIT_FAILURE);
                        }
                }
        }
}



int surronding_cells(char generation[LEN][LEN],int row,int column){
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


char access(char generation[LEN][LEN],int row,int column)
{
        if(row<0||row>=LEN||column<0||column>=LEN){
                return '\0';
        }else{
                return generation[row][column];
        }

}

void display_color(char *filename){
        NCURS_Simplewin sw;
        int i,j;
        char first_generation[LEN][LEN], next_generation[LEN][LEN];
        file2array(filename,first_generation);
        next_state(first_generation,next_generation);

        Neill_NCURS_Init(&sw);
        Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK, COLOR_BLACK, A_NORMAL);
        Neill_NCURS_CharStyle(&sw, "t", COLOR_RED, COLOR_RED, A_NORMAL);
        Neill_NCURS_CharStyle(&sw, "c", COLOR_YELLOW, COLOR_YELLOW, A_NORMAL);
        Neill_NCURS_CharStyle(&sw, "H", COLOR_BLUE, COLOR_BLUE, A_NORMAL);

  do{
        Neill_NCURS_PrintArray(&next_generation[0][0], LEN,LEN, &sw);
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






