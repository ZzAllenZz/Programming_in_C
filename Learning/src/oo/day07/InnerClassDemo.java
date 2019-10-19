package oo.day07;

public class InnerClassDemo {

	public static void main(String[] args) {
		Mama a = new Mama();
		System.out.println(a.a);
		a.show();

	}

}

 class  Mama{
	 Baby b = new Baby();
	 int a  = 20;
	 void show(){
		 System.out.println(b.b);
	
	 }
	class Baby{
		int b = 5 ;
		void showMamaName(){
			System.out.println(a);
		}
	}

}
