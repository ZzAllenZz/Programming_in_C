package oo.day03;

public class SuperDemo {

	public static void main(String[] args) {
		Boo b =  new Boo();

	}

}
class Aoo {
	Aoo(){
		System.out.println("超类的构造方法");
	}
}
class Boo extends Aoo{
	Boo(){
		//super();
		System.out.println("派生类的构造方法");
		
	}
	
}

class Coo {
	Coo(int a ){
		
	}
	
}
class Doo extends Coo{
	Doo(){
		super(5);
	}
}