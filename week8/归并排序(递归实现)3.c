#include <stdio.h>
#define MAXSIZE 10
void merge_sort(int array[],int left,int right);
void merging(int array[],int left,int m, int right);

int main (void)
{
    int array[] = {9,2,8,7,5,3,6,4,1,0};
    int i;
    merge_sort(array,0,MAXSIZE-1);
    printf("array after sort:\n ");
    for(i=0;i<MAXSIZE;i++){
        printf("%d ",array[i]);
    }
    return 0;
}

void merge_sort(int array[],int left,int right)
{
    int m;
    if (left<right){
        m=(left+right)/2;
        merge_sort(array,left,m);
        merge_sort(array,m+1,right);
        merging(array,left,m,right);
    }
}

void merging(int array[],int left,int m, int right)
{
    int i,j,d;
    int temp[MAXSIZE];
    i=left;
    j=m+1;
    d=left;
    while(i<=m&&j<=right){
        if(array[i]<array[j]){
            temp[d++] = array[i++];
        }else{
            temp[d++] = array[j++];
        }
    }
    while(i<=m){
        temp[d++] = array[i++];
    }
    while(j<=right){
        temp[d++] = array[j++];
    }
    for(d=left;d<=right;d++){
        array[d]=temp[d];
    }
}
