#include <stdio.h>
#define MAXSIZE 10
void quick_sort(int array[],int low,int high);
int partition(int array[],int low, int high);
void swap(int array[],int low, int high);

int main (void)
{
    int array[] = {5,3,8,6,1,2,0,7,4,9};
    int i;
    quick_sort(array,0,MAXSIZE-1);
    printf("array after sort:\n ");
    for(i=0;i<10;i++){
        printf("%d ",array[i]);
    }

}

void quick_sort(int array[],int low, int high)
{
    int point;
    if(low <high){
        point=partition(array,low,high);
        quick_sort(array,low,point-1);
        quick_sort(array,point+1,high);
    }
}

int partition(int array[],int low, int high)
{
    int point;
    point = array[low];
    while(low < high){
        while(low<high && array[high]>=point){
            high--;
        }
        swap(array,low,high);
        while(low<high && array[low]<=point){
            low++;
        }
        swap(array,low,high);
    }
    return low;
}

void swap(int array[],int low, int high)
{
    int temp;
    temp = array[low];
    array[low] = array[high];
    array[high] =temp;
}