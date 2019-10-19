package oo.day01;
//学生类的测试类
public class StudentTest {

	public static void main(String[] args) {
		//创建一个对象
		Student zz = new Student();
		//访问成员变量
		zz.name = "Allen";
		zz.age = 23;
		zz.gender  = "男";
		zz.address = "内蒙古包头市" ; 
		zz.study();
		zz.SayHi();
		
		//
		Student yyh = new Student();
		yyh.name = "Yilia";
		yyh.gender = "女";
		yyh.age = 22;
		yyh.address = "辽宁省丹东市";
		yyh.study();
		yyh.SayHi();
		
		//看看默认值；
		Student aa = new Student();
		aa.study();
		aa.SayHi();
		

	}

}
