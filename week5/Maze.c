#include<stdio.h>
#define SIZE 10
void generate_maze(char array[SIZE][SIZE]);
int find_route(char array[SIZE][SIZE],int y,int x);

int main(void)
{
    char array[SIZE][SIZE];
    int i,j,y=1, x= 0;
    generate_maze(array);
    for (i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }
    if(find_route(array,y,x)==1){
        printf("find the rounte\n");
    }else{
        printf("cannot find the route\n");
    }
    for (i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }


    return 0;

}

void generate_maze(char array[SIZE][SIZE])
{
    int i,j;
    for (i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(i==1&&j!=2&&j!=9){
                array[i][j]= ' ';
            }else if (i==2&&j!=0&&j!=2&&j!=4&&j!=6&&j!=7&&j!=9){
                array[i][j]= ' ';
            }else if (i==3&&j!=0&&j!=2&&j!=4&&j!=6&&j!=5&&j!=7&&j!=9){
                array[i][j]= ' ';
            }else if(i==4&&j!=0&&j!=2&&j!=7&&j!=9){
                array[i][j]= ' ';
            }else if (i==5&&j!=0&&j!=2&&j!=4&&j!=5 && j!=6&&j!=7&&j!=9){
                array[i][j]= ' ';
            }else if (i==6&&j!=0&&j!=2&&j!=7&&j!=9){
                array[i][j]= ' ';
            }else if(i==7&&j!=0&&j!=2&&j!=3&&j!=4&&j!=5&&j!=7&&j!=9){
                array[i][j]= ' ';
            } else if (i==8&&j!=0&&j!=7){
                array[i][j]= ' ';
            } else{
                array[i][j] ='#';
            }

        }
       
    }
}
int find_route(char array[SIZE][SIZE],int y,int x)
{
    if(x==9&&y==8){
        array[y][x]='1';
        return 1;
    }
    array[y][x]='1';
    
    if(array[y][x+1]==' '){
        if(find_route(array,y,x+1)==1) {  
            return 1;
        }
    }
    if(array[y+1][x]==' '){
        if(find_route(array,y+1,x)==1){   
            return 1;
        } 
    }
    if(array[y-1][x]==' '){
        if(find_route(array,y-1,x)==1){
            return 1 ;
        }
    }

    if (array[y][x-1]==' ')
    {
       if(find_route(array,y,x-1)==1) {
           return 1;
       }
    }
    array[y][x]=' ';
    return -1;
    


}
