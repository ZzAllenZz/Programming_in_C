#include <stdio.h>

void shell_sort(int k[],int n);

int main (void)
{
    int array[] = {3,2,1,9,7,5,8,4,0,6,10};
    int i;
    shell_sort(array,11);
    printf("array after sort:\n ");
    for(i=0;i<11;i++){
        printf("%d ",array[i]);
    }
    return 0;
}

void shell_sort(int k[],int n) {
    int i, j, temp;
    int gap = n;
    do{
        gap = gap/2;
        for (i = gap; i < n; i++) {
            if (k[i] < k[i - gap]) {
                temp = k[i];
                for (j = i - gap; k[j] > temp && j>= 0; j-= gap) {
                    k[j + gap] = k[j];
                }
                k[j + gap] = temp;
            }
        }
    }while(gap >1);

}