package day03;
import java.util.Scanner;
//��̨��������
public class Cashier {

	public static void main(String[] args) {
	Scanner scan = new Scanner ( System.in);
	System.out.println("��������Ʒ���ۣ�");
	double price = scan.nextDouble();
	System.out.println("�����빺��������");
	double number = scan.nextDouble();
	System.out.println("�������տ��");
	double money = scan.nextDouble();
	
	double totalPrice = price * number ;
	
	if ( totalPrice >= 500){
		totalPrice *= 0.8;
	}
	if ( money >= totalPrice){
		
		double change = money - totalPrice;
		
		System.out.println("�ܼ�Ϊ" + totalPrice + "�� ����Ϊ" + change);
		
	} else {
		System.out.println("ERROR! �տ���㣬���" + (totalPrice - money) );
	}
	
	
	}

}
