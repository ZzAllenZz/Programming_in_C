package oo.day03;

public class SuperDemo {

	public static void main(String[] args) {
		Boo b =  new Boo();

	}

}
class Aoo {
	Aoo(){
		System.out.println("����Ĺ��췽��");
	}
}
class Boo extends Aoo{
	Boo(){
		//super();
		System.out.println("������Ĺ��췽��");
		
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