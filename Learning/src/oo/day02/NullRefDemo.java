package oo.day02;

public class NullRefDemo {

	public static void main(String[] args) {
		//��ʾnull�Ϳ�ָ���쳣��
		Student zs = new Student("����", 25, "BT");
		System.out.println(zs.age);
		zs = null ;
		//System.out.println(zs.age);
		
		//��ʾ�������ͻ��Ⱥţ�
		Student ls = new Student ("����", 27, "ZJ");
		Student lss = ls ; 
		lss.age = 30 ; 
		System.out.println(ls.age); //ָ��ͬһ�����󣻽��Ϊ30��
		
		//��ʾ��������֮�仭�Ⱥţ�
		int a = 5 ; 
		int b = a ;
		b = 26 ; 
		System.out.println(a);
		
		
		

	}

}
