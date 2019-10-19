package oo.day02;

public class NullRefDemo {

	public static void main(String[] args) {
		//演示null和空指针异常；
		Student zs = new Student("张三", 25, "BT");
		System.out.println(zs.age);
		zs = null ;
		//System.out.println(zs.age);
		
		//演示引用类型画等号；
		Student ls = new Student ("李四", 27, "ZJ");
		Student lss = ls ; 
		lss.age = 30 ; 
		System.out.println(ls.age); //指向同一个对象；结果为30；
		
		//演示基本类型之间画等号；
		int a = 5 ; 
		int b = a ;
		b = 26 ; 
		System.out.println(a);
		
		
		

	}

}
