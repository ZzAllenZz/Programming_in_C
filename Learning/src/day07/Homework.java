package day07;

import java.util.Arrays;

public class Homework {

	public static void main(String[] args) {
		//bubble sort
		int[] arr =new int[10];
 		for(int i =0;i< arr.length;i++){
 			arr[i] = (int)(Math.random()*100);
 			System.out.println(arr[i]);
 		}
 		for(int i =0; i<arr.length-1;i++){
 			for(int j=0;j<arr.length-1-i;j++){
 				if(arr[j]> arr[j+1]){
 					int a = arr[j];
 					arr[j] = arr[j+1];
 					arr[j+1] = a;
 				}
 			}
 		}
 		System.out.println(Arrays.toString(arr));
 		
 		//扩容；
 		int max = arr[0];
 		for (int i=1;i<arr.length;i++){
 			if(arr[i]>max){
 				max = arr[i];
 			}
 			
 		}
 		arr = Arrays.copyOf(arr, arr.length+1);
 		arr[arr.length-1] =max ;
 		System.out.println(Arrays.toString(arr));
 		
 		//找到最小值
 		int min = arr[0];
 		for(int i =1 ;i<arr.length;i++){
 			if(arr[i]< min){
 				min = arr[i];
 			}
 			
 		}
 		System.out.println(min);
 		
 		int[] a = generateArrays(10,105);
 		System.out.println(Arrays.toString(a));
		

	}
// generateArrays;
	public static int[] generateArrays(int length, int number){
		int[] arr = new int[length];
		for (int i=0 ; i< arr.length;i++){
			arr[i] = (int)(Math.random()*number);
			
		}
		return arr;
		
		
		
	}
}
