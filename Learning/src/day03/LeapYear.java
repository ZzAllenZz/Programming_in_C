package day03;
import java.util.Scanner; 
/*闰年判断：
 * 1）能被4整除，并且不能被100整除
 * 或者
 * 2）能被400整除
 */
public class LeapYear {
	public static void main(String[] args) {
	//用if 语句实现
		Scanner scan = new Scanner (System.in) ;
		System.out.println("请输入年份：");
		int year = scan.nextInt() ; 
		if (year%4==0 && year%100 != 0 || year % 400 == 0 ){
		String str1 =  year + "是闰年" ;
		System.out.println(str1);	
		} else {
			String str2 = year + "不是闰年" ;
			System.out.println(str2);
			
		}
		
	
	
	
	/*三目条件运算符
	
	Scanner scan = new Scanner (System.in) ;
	System.out.println("请输入年份：");
	int year = scan.nextInt() ; 
	boolean flag = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	String str = flag? year + "是闰年" :year + "不是闰年" ;
	System.out.println(str);
	*/
	}

}
