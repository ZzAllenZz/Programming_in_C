package day04;
import java.util.Scanner;

public class GuessingDemo {

	public static void main(String[] args) {
		int num = (int) (Math.random()*1000+1) ;
		System.out.println(num);
		
		Scanner scan = new Scanner ( System.in);
		
		int guess ; 
		do {
			System.out.println("�°ɣ�");
			guess = scan.nextInt();
			if (guess == 0){
				System.out.println("���˳����´������ɡ�");
				break;
			}
			if (guess > num){
				System.out.println("̫����");
			} else if  (guess < num ){
				System.out.println("̫С��");
			} else {
				System.out.println("��ϲ�㣬�¶��ˡ�");
				
			}
				
			
			
		}while (guess != num);
		
		
		
		/*
		int num = (int) (Math.random()*1000+1) ; 
		System.out.println(num);
		Scanner scan = new Scanner(System.in);
		System.out.println("���һ������");
		int guess = scan.nextInt();
		while ( guess != num){
			if (guess == 0 ) {
				System.out.println("�´�������!");
		
			}
				
			
			if (guess > num )
				System.out.println("̫���ˣ��ٲ£�");
			if (guess < num)
				System.out.println("̫С�ˣ��ٲ£�");
			guess = scan.nextInt();
			if (guess == num){
				System.out.println("��ϲ��¶��ˣ�");
				break;
			}
				
			
		} */

	}

}
