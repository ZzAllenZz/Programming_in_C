package oo.day04;

public class OverrideOverleadDemo {

	public static void main(String[] args) {
		Zoo z = new Zoo();
		Eoo e = new Hoo();
		z.test(e); //���ؿ���������������
		           //��д����������

	}

}

class Zoo {
	void test(Eoo o){
		System.out.println("�����Ͳ���");
		o.show();
	}
	void test(Hoo o){
		System.out.println("�������Ͳ���");
		o.show();
	}
}

class Eoo {
	void show(){
		System.out.println("����show");
	}
	
}

class Hoo extends Eoo {
	void show(){
		System.out.println("������show");
	}
	
}

