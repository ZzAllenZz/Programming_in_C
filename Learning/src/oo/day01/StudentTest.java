package oo.day01;
//ѧ����Ĳ�����
public class StudentTest {

	public static void main(String[] args) {
		//����һ������
		Student zz = new Student();
		//���ʳ�Ա����
		zz.name = "Allen";
		zz.age = 23;
		zz.gender  = "��";
		zz.address = "���ɹŰ�ͷ��" ; 
		zz.study();
		zz.SayHi();
		
		//
		Student yyh = new Student();
		yyh.name = "Yilia";
		yyh.gender = "Ů";
		yyh.age = 22;
		yyh.address = "����ʡ������";
		yyh.study();
		yyh.SayHi();
		
		//����Ĭ��ֵ��
		Student aa = new Student();
		aa.study();
		aa.SayHi();
		

	}

}
