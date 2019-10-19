package oo.day04;

public class OverrideOverleadDemo {

	public static void main(String[] args) {
		Zoo z = new Zoo();
		Eoo e = new Hoo();
		z.test(e); //重载看参数、引用类型
		           //重写看对象类型

	}

}

class Zoo {
	void test(Eoo o){
		System.out.println("超类型参数");
		o.show();
	}
	void test(Hoo o){
		System.out.println("派生类型参数");
		o.show();
	}
}

class Eoo {
	void show(){
		System.out.println("超类show");
	}
	
}

class Hoo extends Eoo {
	void show(){
		System.out.println("派生类show");
	}
	
}

