package day07;
import java.util.Scanner;

public class GuessingGame {
	//主方法
	/* 1.生成一个随机数组
	 * 2.接受用户输入数组
	 * 3.比较，对了算分，错了继续，报告位置和对的个数
	 * 
	 */
	public static void main(String[] args) {
		char[] chs = generate();
		System.out.println(chs); //作弊
		Scanner scan = new Scanner(System.in);
		int score = 0 ; 
		int count = 0;
		while(true){
			String str = scan.next().toUpperCase();
			if ( str.equals("EXIT")){
				System.out.println("下次再来吧");
				break;
			}
			char[] input = str.toCharArray();
			int [] result = check(chs,input);
			if(result[1] == chs.length){
				score = 500 - 10* count;
				System.out.println("恭喜你猜对了，总得分为："+ score);
				break;
				
			}else{
				System.out.println("答错了，字符对了"+ result[0]+", 位置对了" + result[1]);
				count ++;
				
				
			}
			
		}

		
		
		


	}


//生成随机字符数组 chs
    public static char[] generate(){
    	char[] chs = new char[5] ;
    	char[] letters = {'A','B','C','D','E','F','G','H','I','J',
    			'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    	boolean[] flags = new boolean[letters.length];//生成一个和letter一一对应的boolean数组，默认都为false。
    	for(int i =0; i< chs.length;i++){
    		int index;
    		
    		do{
    			index = (int)(Math.random()*26);
    			
    		} while (flags[index] == true);
    		flags[index] = true ;
    		chs[i] = letters[index];
    		
    	
    	}
    	return chs;
    }
//对比：随机生成数组chs和用户输入数组input；
    public static int[] check (char[] chs,char[] input){
    	int[] result = new int[2]; //存放对比结果，result[1]代表位置对，result[0]代表字符对
    	for(int i= 0 ; i< chs.length;i++){ //对chs进行遍历
    		for (int j = 0; j< input.length;j++){ //对input数组进行遍历
    			if(chs[i]==input[j]){//如果字符对了，字符对加一
    				result[0]++;
    				if(i==j){//位置对
    					result[1]++;//位置对的前提是字符是对的，所以是一个嵌套的条件
    				}
    				break;//不需要对后边的在进行比较
    				
    			}
    			
    		}
    		
    	}
    	
    	return result;
    	
    }
}