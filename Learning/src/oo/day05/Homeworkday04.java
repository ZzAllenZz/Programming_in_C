package oo.day05;

public class Homeworkday04 {

	public static void main(String[] args) {
		Person[] p = new Person[5];
		p[0] = new Student("zhangsan",25,"BT",6519300);
		p[1] = new Student("lisi",27,"SD",6519070);
		p[2] = new Teacher("wangwu",35,"ZJ",25102);
		p[3] = new Teacher("yilia",27,"LF",19220);
		p[4] = new Doctor("allen",25,"DH",2);
		for(int i=0;i<p.length;i++){
			p[i].sayHi();
		}

	}

}

class Person {
	String name;
	int age;
	String address;
	Person(String name, int age , String address){
		this.name = name;
		this.age = age ;
		this.address = address;
	}
	void sayHi(){
		System.out.println("大家好，我是"+name+", 今年"+ age +"岁了， 家住"+address+"。");
	}
}
class Student extends Person {
	int stuId;
	Student(String name, int age , String address,int stuId){
		super(name,age,address);
		this.stuId = stuId;
	}
	void sayHi(){
		System.out.println("大家好，我是"+name+", 今年"+ age +"岁了， 家住"+address+", 我的学号是"+stuId+"。");
	}
}
class Teacher extends Person{
	double salary;
	Teacher(String name , int age , String address, double salary){
		super(name,age,address);
		this.salary = salary;
	}
	void sayHi(){
		System.out.println("大家好，我是"+name+", 今年"+ age +"岁了， 家住"+address+", 我的工资是"+salary+"。");
	}
}
class Doctor extends Person{
	int level;
	Doctor(String name, int age , String address, int level){
		super(name,age,address);
		this.level = level;
		
	}
	
}