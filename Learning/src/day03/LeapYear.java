package day03;
import java.util.Scanner; 
/*�����жϣ�
 * 1���ܱ�4���������Ҳ��ܱ�100����
 * ����
 * 2���ܱ�400����
 */
public class LeapYear {
	public static void main(String[] args) {
	//��if ���ʵ��
		Scanner scan = new Scanner (System.in) ;
		System.out.println("��������ݣ�");
		int year = scan.nextInt() ; 
		if (year%4==0 && year%100 != 0 || year % 400 == 0 ){
		String str1 =  year + "������" ;
		System.out.println(str1);	
		} else {
			String str2 = year + "��������" ;
			System.out.println(str2);
			
		}
		
	
	
	
	/*��Ŀ���������
	
	Scanner scan = new Scanner (System.in) ;
	System.out.println("��������ݣ�");
	int year = scan.nextInt() ; 
	boolean flag = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	String str = flag? year + "������" :year + "��������" ;
	System.out.println(str);
	*/
	}

}
