//列主元高斯消去法
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int j,j1,j2,j3,j4,j5,j6,j7,j8,j9,j10;
    double temp;
    double SUM=0;
    printf("请输入未知解的个数：");
    scanf("%d",&n);
    double A[n][n+1];
    double x[n];
    printf("请输入系数矩阵增广后的矩阵：\n");
    for( j=0;j<n;j++)
        for( j1=0;j1<n+1;j1++)
            scanf("%lf",&A[j][j1]);
    for(j2=0;j2<n-1;j2++)    //完全主元素
    {
        for(j3=j2+1;j3<n;j3++)
        {
            if(A[j2][j2]>=A[j3][j2])
                continue;
            else
            {
                for(j4=j2;j4<n+1;j4++)
                {
                    temp = A[j2][j4];
                    A[j2][j4] = A[j3][j4];
                    A[j3][j4] = temp;
                }
            }
        }
        if(A[j2][j2]==0)
            printf("no unique solution!\n");
        for(j5=j2+1;j5<n;j5++)
        {
            for(j6=j2+1;j6<n+1;j6++)
                A[j5][j6]=A[j5][j6]-((A[j5][j2]*A[j2][j6])/A[j2][j2]);

        }
    }
    for(j7=n-1;j7>=0;j7--)  //回代
    {
        x[j7]=(A[j7][n]-SUM)/A[j7][j7];
        SUM = 0;
        j9 = j7-1;
        for(j8=j7-1;j8<n-1;j8++)
        {
            SUM = SUM+x[++j9]*A[j7-1][j9];
        }
    }
    printf("所求解分别为(保留五位小数)：");  //输出解
    for(j10 = 0;j10<n;j10++)
        printf("%.5lf",x[j10]);
    return 0;
}
