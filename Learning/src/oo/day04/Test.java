package oo.day04;

public class Test {

	public static void main(String[] args) {
		/*Student ss = new Student("zhangsan",22,"SD",6519000);
		ss.sayHi();
		Person sts = new Student("zhangsan",22,"SD",6519000);
		sts.sayHi();  // 重写方法被调用时，看的是对象的类型。new谁调谁
		*/
		
		Person[] ps = new Person[5];
		ps[0] = new Student("zs",25,"BT",6519300);
		ps[1] = new Student("ls",21,"ZJ",6519388);
		ps[2] = new Teacher("yyh",27,"LF", 56870);
		ps[3] = new Teacher("zz",28,"sh", 12345);
		ps[4] = new Doctor("allen",24,"jms",3);
		for(int i = 0 ; i< ps.length;i++){
			ps[i].sayHi();
		}
		
	}

}

class Person {
	String name ;
	int age ;
	String address;
	Person(String name, int age , String address){
		this.name = name;
		this.age = age ;
		this.address = address;
	}
	void sayHi(){
		System.out.println("大家好， 我是"+ name +", 今年"
	+age+"岁了， 家住" + address +"。 ");
	}
}

class Student extends Person {
	int stuId;
	Student(String name, int age , String address, int stuId){
		super(name,age,address);
		this.stuId = stuId;
		
	}
	void sayHi(){
		System.out.println("大家好， 我是"+ name +", 今年"
	+age+"岁了， 家住" + address +", " + "我的学号是:"+stuId);
	}
}

class Teacher extends Person {
	double salary;
	Teacher(String name, int age,String address, double salary){
		super(name, age, address);
		this.salary = salary;
	}
	void sayHi(){
		System.out.println("大家好， 我是"+ name +", 今年"
	+age+"岁了， 家住" + address +", " + "我的工资是:"+salary);
	}
}
class Doctor extends Person {
	int level;
	Doctor(String name, int age , String address,int level){
		super(name, age, address);
		this.level = level;	
	}
}