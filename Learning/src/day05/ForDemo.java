package day05;

public class ForDemo {

	public static void main(String[] args) {
		int sum = 0 ;
		for ( int i = 1 ; i<=100; i++){
			sum += i;
			
		}
		System.out.println(sum);
		
		/*
		 *       sum=0
		 * i = 1 sum= 1
		 * i = 2 sum=1+2 
		 * i = 3 sum=1+2+3
		 * i =4 sum = 1+2+3+4
		 * .......
		 * i=100, sum= 1+2+3......+100
		 * i=101,false£¬ÍË³öÑ­»·£¬Êä³ösum£»
		 * */
			

	}

}
