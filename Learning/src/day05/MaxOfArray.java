package day05;
import java.util.Arrays;

public class MaxOfArray {

	public static void main(String[] args) {
		int[] arr = new int[10];
		for(int i=0; i< arr.length; i++){
			arr[i]= (int)(Math.random()*100);
			System.out.println(arr[i]);
		}
		int max = arr[0];
		for (int i = 1 ; i<arr.length; i++){
			if (arr[i]>max){
				max = arr[i];
			}
		}
		System.out.println("���ֵΪ  "+ max);
		
		arr = Arrays.copyOf(arr, arr.length+1);
		arr[arr.length-1] = max;
		
		for (int i =0 ; i<arr.length; i++){
			System.out.println(arr[i]);
		}
		
		//��ϰ2.
		int[] a = {152,52,44,89};
		int[] b = new int[6];
		System.arraycopy(a,0,b,2,4);
		for(int i= 0 ; i< b.length;i++){
			System.out.print(b[i]+"\t");
			

			}
		Arrays.sort(arr); //��������
		for(int i=0;i< arr.length;i++){
		System.out.println(arr[i]);
		}
		
		
		
		
		
		/*
		int[] arr = new int[10]; 
		for (int i = 0 ; i< arr.length; i++){
			arr[i] = (int)(Math.random()*100);
			System.out.println(arr[i]);
		}
		int max = arr[0] ;//�����һ��Ԫ�����
		for(int i =1 ;i<arr.length; i ++){
			if(arr[i]>max){
				max =arr[i];
				
			}
		}
		System.out.println("���ֵΪ��" + max);
		*/
        

	}

}
