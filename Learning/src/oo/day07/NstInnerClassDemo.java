package oo.day07;

public class NstInnerClassDemo {

	public static void main(String[] args) {
		Doo do1 = new Doo(){
			void show (){
				System.out.println("showshow");
			}
		};
		do1.show();
		
		Coo co1 = new Coo(){
			
		};


	}

}

abstract class  Coo {
	
}

 abstract class Doo{
	 abstract void show();
}