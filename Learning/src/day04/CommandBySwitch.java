package day04;
import java.util.Scanner;
public class CommandBySwitch {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		System.out.println("��ѡ���ܣ�1.��ʾȫ�� 2.��ѯȫ�� 0 ��ӭ����");
		int command = scan.nextInt() ; 
		switch (command){
		case 1 :
			System.out.println("��ʾȫ����¼");
			break;
		case 2 :
			System.out.println("��ѯ��¼��¼");
			break;
		case 0 :
			System.out.println("��ӭ�´�����");
			break;
		default :
			System.out.println("�������");
			
		
		
	
		}
		
		
		
		


	}

}
