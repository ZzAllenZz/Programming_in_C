package Live2;

import java.util.Arrays;

public class BubbleSequenceDemo {

	public static void main(String[] args) {
		int[] ary = new int[]{10086,95588,25,2,265,76,89,3,5};
		for(int i = 0; i<ary.length-1;i++){
			for(int j = 0; j<ary.length-1-i;j++){
			if(ary[j]>=ary[j+1]){
				int save = ary[j+1];
				ary[j+1] = ary[j];
				ary[j] = save;
				 
			}
		}
		
		}
		System.out.println(Arrays.toString(ary));
	} 
}
