package day07;
import java.util.Arrays;
import java.util.Scanner;

public class GuessingGameSelfPractice {
	/*
	 * 需求:随机生成一个不重复的五个字符，A到Z.
	 * 接受用户输入的一个五个字符数组，
	 * 对比
	 * 判断，给分
	 * 数据结构：
	 * char[] chs
	 * char[] input
	 * int[] result 对比结果
	 * int score 给分数的
	 * 
	 * 方法：
	 * 1.随机数组的生成
	 * 2.对比的算法
	 * 3.接受用户输入就不需要一个单独的算法了
	 */

	public static void main(String[] args) {
		char[] chs = generate();
		System.out.println(chs);; //作弊；
		Scanner scan = new Scanner (System.in);
		int score = 0;
		int count = 0;
		while (true){
			System.out.println("猜吧，请输入五个不重复的字母");
			String str = scan.next().toUpperCase();
			if(str.equals("EXIT")){
				System.out.println("下次再来吧");
				break;
				
			}
			char [] input = str.toCharArray();
			
			int[] result = check(chs,input);
			if(result[1] == chs.length){
				score = 500 - 10* count;
				System.out.println("恭喜你答对了，总得分为：" + score );
				break;
				
			}else{
				count++;
				System.out.println("对不起答错了，字符对了"+ result[0]+ ", 位置对了"+ result[1]);
				continue;
				
			}
			
		}
		scan.close();


    }
    public static char[] generate(){
    	char[] letters = {'A','B','C','D','E','F','G','H',
    			'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} ;
    	boolean [] flags = new boolean[letters.length];
    	
    	char[] chs = new char[5];
 
    	for(int i = 0 ; i< chs.length; i++){
    		int index ;
    		do{
        		index = (int)(Math.random()*26) ;

    			
    		} while(flags[index] == true);
    		flags[index] = true;
    		chs[i] = letters[index] ;
    	}
    	return chs;
    }
    public static int[] check(char[] chs, char[] input){
    	int[] result = new int[2]; //result[0]代表字符对数，result[1] 代表位置对数；
    	for( int i = 0 ; i< input.length; i++){
    		for(int j =0 ; j<chs.length;j++){
    			if( input[i] == chs [j]){
    				result[0] ++;
    				if(i == j){
    					result[1]++;
    				}
    				break;
    				
    			}
    		}
    	}
    	return result ; 
    }


}
