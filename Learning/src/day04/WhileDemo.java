package day04;

public class WhileDemo {

	public static void main(String[] args) {
		/*int num = 9 ;
		while (num >= 1){
			System.out.println(num + " x 9 = " + num*9);
			num -- ;
		}
		System.out.println("OVER");
		*/
		
		int num = 1 ;
		while ( num < 10 ){
			if ( num == 5 ){
				break;
			}
			System.out.println(num + " x 9 = " + num*9);
			num += 2 ;
		}
		System.out.println("over");
		
		
		
		
		
		
		/*int num = 1 ;
		while ( num <=9 ){
			System.out.println( num +" x 9 = "+ num*9 );
			num ++ ;
			
		}
		System.out.println("OVER");
		*/
		
		
		
		
		
		/*int times = 0 ; 
		while ( times < 10){
			System.out.println("行动是成功的阶梯");
			times ++  ;
		
			
		}
		System.out.println("over"); */
	/*
	 * 输出十次行动是成功的阶梯
	 *                        次数0
	 * 够十次吗？ 不够，输出，次数1
	 * 够十次吗？ 不够，输出，次数2
	 * 够十次吗？ 不够，输出，次数3
	 * 够十次吗？ 不够，输出，次数4
	 * 够十次吗？ 不够，输出，次数5
	 * 够十次吗？ 不够，输出，次数6
	 * 够十次吗？ 不够，输出，次数7
	 * 够十次吗？ 不够，输出，次数8
	 * 够十次吗？ 不够，输出，次数9
	 * 够十次吗？ 不够，输出，次数10时结束。
	 *            
	 */ 

	}

}
