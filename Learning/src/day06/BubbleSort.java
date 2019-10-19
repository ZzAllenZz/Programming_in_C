package day06;
import java.util.Scanner;
public class BubbleSort {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		System.out.println("请输入n：" );
		int n = scan.nextInt();
		int[] arr = new int[n];
		for (int i =0; i<arr.length;i++){
			arr[i] = (int)(Math.random()*100);
			System.out.println(arr[i]);
			
		}
		for (int i =0; i< arr.length-1;i++){ //控制轮数为n-1；
			for(int j=0;j<arr.length-1-i;j++){
				if(arr[j]>arr[j+1]){
					int t = arr[j];
					arr[j]= arr[j+1];
					arr[j+1] =t;
				}
				
			}
			
		}
		System.out.println("升序后的排序为：");
		for (int i=0; i<arr.length; i++){
			System.out.println(arr[i]);
		}

	}

}
