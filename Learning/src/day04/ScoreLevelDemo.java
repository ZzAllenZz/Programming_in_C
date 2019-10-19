package day04;
import java.util.Scanner;

public class ScoreLevelDemo {

	public static void main(String[] args) {
		Scanner scan = new Scanner ( System.in);
		System.out.println("请输入成绩：");
		int score = scan.nextInt();
		if ( score > 100 || score < 0 ) {
			System.out.println("输入不合法！");
			
			
		} else if ( score >= 90){ 
			System.out.println("A-优秀");
			
		} else if  ( score >= 80) {
			System.out.println("B-良好");
			
		} else if ( score >=60 ) {
			System.out.println("C-及格");
			
		} else {
			System.out.println("不及格");
			
		}

	}

}
