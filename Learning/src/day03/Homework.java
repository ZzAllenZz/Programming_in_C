package day03;
import java.util.Scanner;

public class Homework {

	public static void main(String[] args) {
		//三个数中的最大值
		Scanner scan = new Scanner (System.in);
		System.out.println("请输入三个整数，a、b和c");
		int a = scan.nextInt();
		int b = scan.nextInt();
		int c = scan.nextInt();
	    
		int max = a >= b ? (a >= c ? a : c) : (b >= c ? b : c) ;
		System.out.println("最大值是 max = " + max);
		
		/* 升序排列
		Scanner scan = new Scanner (System.in);
		System.out.println("请输入三个整数，a、b和c");
		int a = scan.nextInt();
		int b = scan.nextInt();
		int c = scan.nextInt();
	    System.out.println("您的输入是：a=" + a + " b="+ b + " c="+c);
	    if(a<= b){
	    	if( a <= c){
	    		if(b<= c){
	    			System.out.println("升序排列后，结果为: a="+ a +" b="+ b + " c="+ c);
	    		} else{
	    			System.out.println("升序排列后，结果为: a="+ a +" b="+ c + " c="+ b);
	    		}
	    	} else{
	    		System.out.println("升序排列后，结果为: a="+ c +" b="+ a + " c="+ b);
	    		
	    	}
	    	
	    } else{
	    	if (b<=c){
	    		if(a <= c){
	    			System.out.println("升序排列后，结果为: a="+ b +" b="+ a + " c="+ c);
	    			
	    			
	    		}else{
	    			System.out.println("升序排列后，结果为: a="+ b +" b="+ c + " c="+ a);
	    		}
	    		
	    	}else{
	    		System.out.println("升序排列后，结果为: a="+ c +" b="+ b + " c="+ a);
	    		
	    	}

	    	
	    }
	    */ 
		
		/*   两个数的最大值
		Scanner scan = new Scanner (System.in);
		System.out.println("请输入两个整数，a和b");
		int a = scan.nextInt();
		int b = scan.nextInt();
		int max = a>=b ? a : b ;
		
		System.out.println("最大值为：" + max);
		*/

	}

}
