package day03;
import java.util.Scanner;

public class Homework {

	public static void main(String[] args) {
		//�������е����ֵ
		Scanner scan = new Scanner (System.in);
		System.out.println("����������������a��b��c");
		int a = scan.nextInt();
		int b = scan.nextInt();
		int c = scan.nextInt();
	    
		int max = a >= b ? (a >= c ? a : c) : (b >= c ? b : c) ;
		System.out.println("���ֵ�� max = " + max);
		
		/* ��������
		Scanner scan = new Scanner (System.in);
		System.out.println("����������������a��b��c");
		int a = scan.nextInt();
		int b = scan.nextInt();
		int c = scan.nextInt();
	    System.out.println("���������ǣ�a=" + a + " b="+ b + " c="+c);
	    if(a<= b){
	    	if( a <= c){
	    		if(b<= c){
	    			System.out.println("�������к󣬽��Ϊ: a="+ a +" b="+ b + " c="+ c);
	    		} else{
	    			System.out.println("�������к󣬽��Ϊ: a="+ a +" b="+ c + " c="+ b);
	    		}
	    	} else{
	    		System.out.println("�������к󣬽��Ϊ: a="+ c +" b="+ a + " c="+ b);
	    		
	    	}
	    	
	    } else{
	    	if (b<=c){
	    		if(a <= c){
	    			System.out.println("�������к󣬽��Ϊ: a="+ b +" b="+ a + " c="+ c);
	    			
	    			
	    		}else{
	    			System.out.println("�������к󣬽��Ϊ: a="+ b +" b="+ c + " c="+ a);
	    		}
	    		
	    	}else{
	    		System.out.println("�������к󣬽��Ϊ: a="+ c +" b="+ b + " c="+ a);
	    		
	    	}

	    	
	    }
	    */ 
		
		/*   �����������ֵ
		Scanner scan = new Scanner (System.in);
		System.out.println("����������������a��b");
		int a = scan.nextInt();
		int b = scan.nextInt();
		int max = a>=b ? a : b ;
		
		System.out.println("���ֵΪ��" + max);
		*/

	}

}
