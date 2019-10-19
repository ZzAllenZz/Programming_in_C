package oo.day03;

public class Student {
	String name ;
	int age ;
	String address;
	//构造方法
	Student(String name , int age , String address){
		this.name = name ;
		this.age = age ; 
		this.address = address;
	}
	Student (String name, int age ){
		this(name, age, null);	
	}
	Student (String name){
		this(name, 0 ); //两次传递
	}
	void sayHi(){
		System.out.println("大家好，我是"+ this.name+ "， 今年" + this.age +"岁了， 家住 " + this.address +"。");
	}
	void study(){
		System.out.println(name +"正在学习呢~");
	}

}
