#include <stdio.h>
#define MAXSIZE 10
void merge_sort(int k[],int n);
void merging(int *list_left,int list_left_size,int *list_right,int list_right_size);
int main (void)
{
    int array[] = {9,2,8,7,5,3,6,4,1,0};
    int i;
    merge_sort(array,MAXSIZE);
    printf("array after sort:\n ");
    for(i=0;i<MAXSIZE;i++){
        printf("%d ",array[i]);
    }
    return 0;
}

void merge_sort(int k[],int n) {
    int *list_left = k;
    int list_left_size = n/2;
    int *list_right = k + n/2;
    int list_right_size = n - list_left_size;

    if(n<=1){
        return;
    }
    merge_sort(list_left,list_left_size);
    merge_sort(list_right,list_right_size);
    merging(list_left,list_left_size,list_right,list_right_size);
}

void merging(int *list_left,int list_left_size,int *list_right,int list_right_size)
{
    int i,j,k,m;
    int temp[MAXSIZE];
    i = j = k = 0;
    m = 0;
    while(i < list_left_size && j <list_right_size){
        if(list_left[i]<list_right[j]){
            temp[k] = list_left[i];
            k++;
            i++;
        }else{
            temp[k++] = list_right[j++];
        }
    }
    while(i<list_left_size){
        temp[k++] = list_left[i++];
    }
    while(j<list_right_size){
        temp[k++] = list_right[j++];
    }
    for(m ;m < (list_right_size+list_left_size);m++){
        list_left[m] = temp[m];
    }
}