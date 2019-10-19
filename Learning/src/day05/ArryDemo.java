package day05;

public class ArryDemo {

	public static void main(String[] args) {
		int[] arr1 = new int[10];
		int[] arr2 = { 2,4,5,8};
		int[] arr3 = new int[]{2,4,5,8};
		int[] arr4 = new int[3];
		System.out.println(arr4.length);
		arr4 [0] = 100;
		arr4 [1] = 200;
		arr4 [2] = 300;
		//arr4 [3] = 400;数组下标越界溢出；
		System.out.println(arr4 [2]);
		
		

	}

}
