package day06;

public class MethodDemo {

	public static void main(String[] args) {
		//say();
		sayHi("Yilia");
		sayHello("Allen",23);
		double a = getNum();
		System.out.println(a);
		int m = 8, n = 9;
		int b = plus (m,n);
		System.out.println(b);
		a();
		

	}
	//�޲��޷���ֵ
	public static void say (){

		System.out.println("��Һã��ҽ�Allen������23����");
	}
	
	public static void sayHi(String name){
		System.out.println("��Һã��ҽ�"+ name +", ����22����");
		return;
	}
	public static void sayHello (String name, int age){

		System.out.println("��Һã��ҽ�"+name+", ����"+age+"����");
	}
	//�޲��з���ֵ
	public static double getNum(){
		double a = 77.77 ;
		return a;
		
	}
	//�в����з���ֵ��
	public static int plus (int num1,int num2){

		int num = num1+ num2;
		return num;
	}
	//Ƕ�׵��ã�
	public static void a(){
		System.out.println(111);
		b();
		System.out.println(222);
	}
	public static void b(){
		System.out.println(333);
		c();
	}
	public static void c(){
		System.out.println(444);
	}

}
