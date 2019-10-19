package Live2;
import java.util.Arrays;

public class ArrayPractice {

	public static void main(String[] args) {
		int[] arr1 = new int[20];
		for(int i=0;i<arr1.length;i++){
			arr1[i]= (int)(Math.random()*10);
			
		}
		
		int[] arr2 = new int[10];
		for (int i =0; i< arr1.length; i++){
			arr2[arr1[i]]++;
		}
		for(int i =0;i<arr2.length;i++){
			System.out.println("数组arr1中"+i+"的个数为"+ arr2[i]);
		}
		int[] arr3 = new int[5];
		arr3 = Arrays.copyOf(arr1, 15) ;
		
       
	}

}
