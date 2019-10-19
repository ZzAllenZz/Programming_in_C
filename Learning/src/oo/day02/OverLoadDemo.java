package oo.day02;

public class OverLoadDemo {

	public static void main(String[] args) {
		
		Aoo o = new Aoo();
		int age = 0 ;
		String name  =" allen";
		o.say();
		o.say(age);
		o.say(name);
		o.say(age, name);
		
		
	

	}

}

class Aoo {
	void say(){};
	void say(int age){};
	void say(String name){};
	void say(String name, int age){};
	void say(int age, String name){};
	
}
