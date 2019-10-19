package day06;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Scanner;
public class Homework {

	public static void main(String[] args) {
		Scanner scan = new Scanner (System.in);
		System.out.println("请输入整数（例如10）：");
		int n = scan.nextInt();
		double sum = 0;
		double [] arr = new double[n];
		for (int i=0; i< arr.length; i++){
			arr[i] = 1.0/(i+1);
			sum += arr[i];
			
			
			System.out.println(arr[i]);

			
		}
		System.out.println("sum=" +sum);
		

		
		
		
		
		
		
		/*难，把数列9,99,999，.....9999999999找到，然后求和。
		long [] arr =  new long [10];
		long sum = 0 ;
		for (int i=0;i<arr.length;i++){
			for (long j =1;j<(long)(Math.pow(10,i+1));j = j*10){
				arr[i] +=9*j;
				
						
			}
			System.out.println(arr[i]);
			
			
		
		  }	
		for (int i=0;i<arr.length;i++){
			sum += arr[i];
			
		}
		System.out.println("sum="+sum);
		*/
		}
	
}
		
		
		
		
		
		
		/*
		int[] arr = new int[10];
		for(int i=0;i<arr.length;i++){
			
			/* arr[0] = 9*1
			 * arr[1] = 9+ 9*10
			 * arr[2]= 9+9*10+9*100
			 */
			
		

		
		
		
		
		
		
		
		
		
		
		/*数组中的最小值
		int[] arr =  new int[10];
		for (int i =0 ; i< arr.length; i++){
			arr[i] = (int)(Math.random()*100);
			System.out.println(arr[i]);
		}
		int min = arr[0];
		for(int i=1;i< arr.length;i++){
			if(arr[i]< min){
				min = arr[i];
			}
			
		}
		System.out.println("最小值为："+min);
         */
	


