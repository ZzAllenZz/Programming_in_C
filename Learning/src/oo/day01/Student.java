package oo.day01;
//学生类
public class Student {
	//创建成员变量
	String name; 
	int age ;
	String gender ; 
	String address ; 
	// 创建方法；
	void study (){
		System.out.println(name+"正在学习java，好难呀！");
	}
	void SayHi (){
		System.out.println("我叫"+name+", 性别"+gender+ ", 今年"+age+"岁了， 家住" + address+"。");
	}
	
	

}
