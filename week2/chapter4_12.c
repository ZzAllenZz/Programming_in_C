    #include<stdio.h>
    int main(void){
        int total, i=0,primes = 2,count,j ,flag;
        printf("how many primes you want totally (from 2 to max)? ");
        scanf("%d",&total);
        for(i;i<total;i++){
            do{
            count = 0;
            flag = 0;
            for (j=1;j<=primes;j++){
                if(primes%j==0)
                   count++;
                }
            if(count<=2) {
                printf("%d\n",primes);
                flag++;}
            primes++;
            }while(flag ==0);


            }
        return 0;
    }
