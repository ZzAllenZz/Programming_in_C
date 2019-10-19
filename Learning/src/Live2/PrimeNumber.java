package Live2;

public class PrimeNumber {

	public static void main(String[] args) {
		
		for(int i =2; i<= 100;i++){ // i代表判断的数字
			int count =0 ;
			for(int j =2 ; j<=i; j++){
				//j 代表除数
				//判断是否能被整除; 
				//如果能，统计次数加1
				if(i%j==0){
					count++;
				}
				
				
			}
			if(count ==1){
				System.out.println(i);
			}
			
		}
		


	}

}
