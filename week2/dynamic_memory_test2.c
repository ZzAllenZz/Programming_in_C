#include <stdio.h>
#include <stdlib.h>

int main(){
    int arrLen;  // ���鳤��
    int *array;  // ����ָ��
    int i;  // �����±�

    printf("�������鳤�ȣ�");
    scanf("%d", &arrLen);
    
// ��̬�����ڴ�ռ䣬���ʧ�ܾ��˳�����
    array = (int*)malloc( arrLen*sizeof(int) );
    if(!array){
        printf("��������ʧ�ܣ�\n");
        exit(1); 
    }
// ���ڴ���д������
    for(i=0; i<arrLen; i++){
        array[i] = i+1;
    }
    
    // ѭ���������Ԫ��
    for(i=0; i<arrLen; i++){
        printf("%d  ", array[i]);
    }
    
    printf("\n");
    free(array); 
    
    system("pause");
    return 0;
}
