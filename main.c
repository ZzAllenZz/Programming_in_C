#include <stdio.h>

void merge_sort(int k[],int n);
void merging(int *list_left,int list_left_size,int *list_right,int list_right_size);
int main (void)
{
    int array[] = {3,2,1,9,7,5,8,4,0,6};
    int i;
    merge_sort(array,10);
    printf("array after sort:\n ");
    for(i=0;i<10;i++){
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

}