package day05;
import java.util.Scanner;
public class Addition {

	public static void main(String[] args) {
		int score = 0 ;
		
		for ( int i=1; i<=10; i++){
			//1.���� 2 .���� 3.���⣬
			Scanner scan = new Scanner( System.in);
			int a = (int)(100* Math.random());
			int b = (int)(100*Math.random());
			int result = a+b ;
			System.out.println("("+i+")"+ a +"+" + b +"=?"+"      ��ɣ�");
			int calculate = scan.nextInt();
			if (calculate == -1){
				System.out.println("���˳�");
				break;
			}
			if ( calculate == result ){
				System.out.println("�����");
				score += 10 ;
			} else {
				System.out.println("�����");
			}
			
			
			
			
		}
		System.out.println("���ĵ÷�Ϊ��"+ score);
			


	}

}
