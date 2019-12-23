#include<stdio.h>
#include<stdlib.h>
#define LEN 40
void file2array(char *filename,char first_generation[LEN][LEN]);

void next_state(char first_generation[LEN][LEN],char next_generation[LEN][LEN]);

int surronding_cells(char generation[LEN][LEN],int row,int column);

void create_world(char *filename);

char access(char generation[LEN][LEN],int row,int column);


int main(int argc,char **argv)
{
  if (argc != 2){
        printf("ERROR:Incorrect usage,try e.g. %s wirewcircuit1.txt",argv[0]);
        exit(EXIT_FAILURE);
    }else{
        create_world(argv[1]);
    }
    return 0;
}

void create_world(char *filename)
{
        FILE *fp;
        char *output_filename = "wireworld_output.txt" ;
        int i,j,k;
        char first_generation[LEN][LEN], next_generation[LEN][LEN];

        file2array(filename,first_generation);
        if((fp=fopen(output_filename,"a"))== NULL){
                printf("Failed to open a file named %s",output_filename);
                exit(EXIT_FAILURE);
        }
        for(k=0;k<1000;k++){
                next_state(first_generation,next_generation);
                for(i=0;i<LEN;i++){
                        for(j=0;j<LEN;j++){
                                putc(next_generation[i][j],fp);
                        }
                        putc('\n',fp);
                }
                for(i=0;i<LEN;i++){
                for(j=0;j<LEN;j++){
                        first_generation[i][j] = next_generation[i][j];
            }
        }
        }
        fclose(fp);
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
        if(row<0||row>LEN||column<0||column>LEN){
                return '\0';
        }else{
                return generation[row][column];
        }

}
