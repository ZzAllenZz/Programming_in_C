package day04;
import java.util.Scanner;

public class Homework {

	public static void main(String[] args) {
		Scanner scan =  new Scanner ( System.in);
		System.out.println("���������");
		int year = scan.nextInt();
		System.out.println("�������·�");
		int month = scan.nextInt();
		int day ;
		switch (month){
		case 1:
			day = 31 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 2:
			if(year%4 == 0 && year% 100 !=0 || year %400 ==0){
				day = 29 ;
				
			} else {
				day = 28;
			}
			
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 3:
			day = 31 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 4:
			day = 30 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 5:
			day = 31 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 6:
			day = 30 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 7:
			day = 31 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 8:
			day = 31 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 9:
			day = 30 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 10:
			day = 31 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 11:
			day = 30 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		case 12:
			day = 31 ;
			System.out.println(year+"��"+ month+"����"+day+"��");
			break;
		
		
		}
		
		
		
		
		/*
		System.out.println("��������Ĺ��ʵ�˰ǰ��RMB��");
		Scanner scan = new Scanner (System.in);
		double wage = scan.nextInt() - 3500 ;
		double tax ;
		if (wage <= 0){
			System.out.println("����˰");
		}else if (wage <= 1500){
			tax = wage * 0.03 -0 ;
			System.out.println("��Ӧ�ý��ɵĸ�������˰�ǣ�" + tax + "RMB");
	
		} else if ( wage <= 4500){
			tax = wage * 0.1 -105 ;
			System.out.println("��Ӧ�ý��ɵĸ�������˰�ǣ�" + tax + "RMB");
		} else if (wage <= 9000){
			tax = wage * 0.2 -555 ;
			System.out.println("��Ӧ�ý��ɵĸ�������˰�ǣ�" + tax + "RMB");
		}else if (wage <=35000){
			tax = wage * 0.25 -1005 ;
			System.out.println("��Ӧ�ý��ɵĸ�������˰�ǣ�" + tax + "RMB");
		}else if (wage <= 55000){
			tax = wage * 0.3 - 2755 ;
			System.out.println("��Ӧ�ý��ɵĸ�������˰�ǣ�" + tax + "RMB");
		}else if (wage <= 80000){
			tax = wage * 0.35 -5505 ;
			System.out.println("��Ӧ�ý��ɵĸ�������˰�ǣ�" + tax + "RMB");
		}else {
			tax = wage * 0.45 - 13505 ;
			System.out.println("��Ӧ�ý��ɵĸ�������˰�ǣ�" + tax + "RMB");
		}
		*/
	}

}
