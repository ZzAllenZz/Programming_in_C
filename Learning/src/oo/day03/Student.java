package oo.day03;

public class Student {
	String name ;
	int age ;
	String address;
	//���췽��
	Student(String name , int age , String address){
		this.name = name ;
		this.age = age ; 
		this.address = address;
	}
	Student (String name, int age ){
		this(name, age, null);	
	}
	Student (String name){
		this(name, 0 ); //���δ���
	}
	void sayHi(){
		System.out.println("��Һã�����"+ this.name+ "�� ����" + this.age +"���ˣ� ��ס " + this.address +"��");
	}
	void study(){
		System.out.println(name +"����ѧϰ��~");
	}

}
