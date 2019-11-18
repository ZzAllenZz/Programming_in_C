#include <stdio.h>

void bubble_sort(int k[],int n);

int main (void)
{
    int array[] = {5,3,8,6,2,1,0,7,4,9};
    int i;
    bubble_sort(array,10);
    printf("array after sort:\n ");
    for(i=0;i<10;i++){
        printf("%d ",array[i]);
    }

}

void bubble_sort(int k[],int n)
{
    int i,j,temp;
    int count1=0,count2=0;
    /*
     * count1 记录比较次数；
     * count2 记录移动（更换）次数；
     * */

    for(i=0;i<n-1;i++){
        for(j=n-1;j>i;j--){/*you can also change the direction of bubble*/
            count1++;
            if(k[j]<k[j-1]){
                temp = k[j];
                k[j] = k[j-1];
                k[j-1] = temp;
                count2++;
            }
        }
    }
    printf("comparision:%d times, exchange: %d times \n",count1,count2);
}