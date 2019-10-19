package day04;
import java.util.Scanner;

public class GuessingDemo {

	public static void main(String[] args) {
		int num = (int) (Math.random()*1000+1) ;
		System.out.println(num);
		
		Scanner scan = new Scanner ( System.in);
		
		int guess ; 
		do {
			System.out.println("猜吧：");
			guess = scan.nextInt();
			if (guess == 0){
				System.out.println("已退出，下次再来吧。");
				break;
			}
			if (guess > num){
				System.out.println("太大了");
			} else if  (guess < num ){
				System.out.println("太小了");
			} else {
				System.out.println("恭喜你，猜对了。");
				
			}
				
			
			
		}while (guess != num);
		
		
		
		/*
		int num = (int) (Math.random()*1000+1) ; 
		System.out.println(num);
		Scanner scan = new Scanner(System.in);
		System.out.println("请猜一个数：");
		int guess = scan.nextInt();
		while ( guess != num){
			if (guess == 0 ) {
				System.out.println("下次再来吧!");
		
			}
				
			
			if (guess > num )
				System.out.println("太大了，再猜：");
			if (guess < num)
				System.out.println("太小了，再猜：");
			guess = scan.nextInt();
			if (guess == num){
				System.out.println("恭喜你猜对了！");
				break;
			}
				
			
		} */

	}

}
