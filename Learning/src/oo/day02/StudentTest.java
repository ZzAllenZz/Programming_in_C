package oo.day02;

public class StudentTest {

	public static void main(String[] args) {
		Student zs = new Student("张三");
		Student ls = new Student ("李四", 23);
		Student ww = new Student ("王五", 25, "浙江");
		zs.sayHi();
		ls.sayHi();
		ww.sayHi();

	}

}
