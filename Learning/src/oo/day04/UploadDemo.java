package oo.day04;

public class UploadDemo {

	public static void main(String[] args) {
		Aoo a = new Aoo();
		a.a = 2;
		a.show();
		//a.b = 6; //编译错误，超类不能访问派生类对象；
		
		Boo b = new Boo();
		b.a = 6; // 派生类可以访问超类对象
		b.show();
		b.b = 1;
		b.test();
		
		Aoo oo = new Boo(); //向上访问；
		oo.a = 7;
		oo.show();
		//oo.b; // 编译错误，能点出来什么，要看引用类；
		
		//Boo bb = new Aoo();
		//编译错误，只能是派生类向上访问超类，不能反之。
		
		
		
	

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