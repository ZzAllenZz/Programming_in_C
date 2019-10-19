package day05;
import java.util.Scanner;
public class Addition {

	public static void main(String[] args) {
		int score = 0 ;
		
		for ( int i=1; i<=10; i++){
			//1.出题 2 .答题 3.判题，
			Scanner scan = new Scanner( System.in);
			int a = (int)(100* Math.random());
			int b = (int)(100*Math.random());
			int result = a+b ;
			System.out.println("("+i+")"+ a +"+" + b +"=?"+"      算吧！");
			int calculate = scan.nextInt();
			if (calculate == -1){
				System.out.println("已退出");
				break;
			}
			if ( calculate == result ){
				System.out.println("答对了");
				score += 10 ;
			} else {
				System.out.println("答错了");
			}
			
			
			
			
		}
		System.out.println("您的得分为："+ score);
			


	}

}
