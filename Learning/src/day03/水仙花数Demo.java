package day03;


public class 水仙花数Demo {

	public static void main(String[] args) {
		//不用嵌套循环完成；
		
		/*for (int i = 100 ;i>= 100 && i<1000;i++){
	
			if (i== (Math.pow((i%10),3) + Math.pow((i/10)%10,3) + Math.pow((i/100), 3))){
				System.out.println(i);
				
			}
				
		}
		*/
		
		//用嵌套完成
		for (int i = 100 ; i<1000;i++){
			int sum = 0;
			//j表示判断的数字
			for(int j =i;j>0;j/=10){
				int tmp = j%10;
				sum += tmp*tmp*tmp;	
			}
			if(sum == i){
				System.out.println(i);
			}
			
		}
		
		
		
		

	}

}
