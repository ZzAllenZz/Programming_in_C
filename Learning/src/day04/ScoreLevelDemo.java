package day04;
import java.util.Scanner;

public class ScoreLevelDemo {

	public static void main(String[] args) {
		Scanner scan = new Scanner ( System.in);
		System.out.println("������ɼ���");
		int score = scan.nextInt();
		if ( score > 100 || score < 0 ) {
			System.out.println("���벻�Ϸ���");
			
			
		} else if ( score >= 90){ 
			System.out.println("A-����");
			
		} else if  ( score >= 80) {
			System.out.println("B-����");
			
		} else if ( score >=60 ) {
			System.out.println("C-����");
			
		} else {
			System.out.println("������");
			
		}

	}

}
