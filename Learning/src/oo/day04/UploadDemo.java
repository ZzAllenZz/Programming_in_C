package oo.day04;

public class UploadDemo {

	public static void main(String[] args) {
		Aoo a = new Aoo();
		a.a = 2;
		a.show();
		//a.b = 6; //������󣬳��಻�ܷ������������
		
		Boo b = new Boo();
		b.a = 6; // ��������Է��ʳ������
		b.show();
		b.b = 1;
		b.test();
		
		Aoo oo = new Boo(); //���Ϸ��ʣ�
		oo.a = 7;
		oo.show();
		//oo.b; // ��������ܵ����ʲô��Ҫ�������ࣻ
		
		//Boo bb = new Aoo();
		//�������ֻ�������������Ϸ��ʳ��࣬���ܷ�֮��
		
		
		
	

	}

}

class Aoo{
	int a ;
	void show(){}
	
}
class Boo extends Aoo{
	int b ;
	void test(){}
	
}