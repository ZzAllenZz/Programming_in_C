#include <stdio.h>

void insert_sort(int k[],int n);

int main (void)
{
    int array[] = {3,2,1,9,7,5,8,4,0,6,10};
    int i;
    insert_sort(array,11);
    printf("array after sort:\n ");
    for(i=0;i<11;i++){
        printf("%d ",array[i]);
    }
    return 0;
}

void insert_sort(int k[],int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) {
        if (k[i] < k[i - 1]) {
            temp = k[i];
            for (j = i - 1; k[j] > temp && j>= 0; j--) {
                k[j + 1] = k[j];
            }
            k[j + 1] = temp;
        }
    }
}