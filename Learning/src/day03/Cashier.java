package day03;
import java.util.Scanner;
//柜台收银程序
public class Cashier {

	public static void main(String[] args) {
	Scanner scan = new Scanner ( System.in);
	System.out.println("请输入商品单价：");
	double price = scan.nextDouble();
	System.out.println("请输入购买数量：");
	double number = scan.nextDouble();
	System.out.println("请输入收款金额：");
	double money = scan.nextDouble();
	
	double totalPrice = price * number ;
	
	if ( totalPrice >= 500){
		totalPrice *= 0.8;
	}
	if ( money >= totalPrice){
		
		double change = money - totalPrice;
		
		System.out.println("总价为" + totalPrice + "， 找零为" + change);
		
	} else {
		System.out.println("ERROR! 收款金额不足，还差：" + (totalPrice - money) );
	}
	
	
	}

}
