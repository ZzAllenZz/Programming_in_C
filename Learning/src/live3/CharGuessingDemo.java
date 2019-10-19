package live3;
import java.util.Arrays;
import java.util.Scanner;

public class CharGuessingDemo {

	public static void main(String[] args) {
/*       难点：1.分为两个方法，generate用来生成 随机字母，test用来判断位置对和字符对的个数；
 *           2.全变大写 scan.next().toUpperCase();
 *             String str = scan.next().toUpperCase;
 *             str.euqals("EXIT"); 判断字符串
 *             str.length(); 
 *             str.toCharArray()
 *           3.利用boolean[]数组都是 false和true的特点，来做一些标记。e.g. boolean[] test
 *             利用int[]数组来计数 e.g. int[] test
 *           4.利用while（true）搞事情
 *           5.随机数 site = (int)(Math.random()*base.length)
 * 
 * 
 * 
 * */
		char[] original = generate();
		System.out.println(Arrays.toString(original));

		int count = 0;
		int score = 100;
		do{
			Scanner scan = new Scanner(System.in);
			String str = scan.next().toUpperCase();
			while(str.length()!=5 ){
				if(str.equals("EXIT")){
					System.out.println("已退出");
					return;
					}
				System.out.println("输入长度不为5，请重新输入");
				str = scan.next().toUpperCase();
				count++;
			}
			

			char[] input = str.toCharArray();
			int[] result = test(original,input);
			if(result[1]== input.length){
				System.out.print("恭喜你，猜对了,得分为"+score);
				break;
				
			} else{
				score -= 10;
				count++;
				System.out.println("没猜对， 字符猜对"+result[0]+"个, 位置猜对"+result[1]+"个，还剩"+(int)(10-count)+"次");
				
			}
			if(count>=10){
				System.out.println("game over");
				break;
			}
			scan.close();
			
		}while(true);
		
		
		
		
		
		
		
		

	}
	public static char[] generate(){
		char[] base = {'A','B','C', 'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		boolean[] check = new boolean[base.length];
		char[] original = new char[5];
		for(int i = 0 ; i<original.length; i++){
			int site;
			do{
				site = (int)(Math.random()*base.length);
			}while(check[site] == true);
			original[i] = base[site];
			check[site] = true ;
		}
		
		return original;
		
	}
	public static int[] test(char[] original, char[] input){
		int[] result = new int[2]; // 1:符号对；2：位置对；
		for(int i =0; i<input.length;i++){
			for(int j =0; j<original.length;j++){
				if(input[i]==original[j]){
					result[0]++;
					if(i==j){
						result[1]++;
						}
					break;
				}
			}
		}
		return result;
		
	}
	

}
