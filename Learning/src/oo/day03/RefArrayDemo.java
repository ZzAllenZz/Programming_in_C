package oo.day03;
import java.util.Arrays;

public class RefArrayDemo {

	public static void main(String[] args) {
		Student[] stus = new Student[3];
		stus[0] = new Student("zhangsan",25,"BT");
		stus[1] = new Student ("lisi");
		stus[2] = new Student ( "wangwu", 23);
		stus[0].sayHi();
		stus[1].study();
		System.out.println(Arrays.toString(stus));//��ӡ�������ǵ�ַ��
		
		Student[] ss = new Student[]{
				new Student("yyh"),
				new Student("zz",25,"BT"),
				new Student("pp", 20, "ZJ")
		 };
		ss[0].study();
		ss[2].sayHi();
		
		int[][] arr = new int[3][]; //����һ����������飬��������Ԫ�أ��������飩��
		arr[0] = new int[4];
		arr[1] = new int [2];
		arr[2] = new int[3];
		System.out.println(Arrays.toString(arr[0]));
		
		int[][] matrix =  new int[3][4];//����һ����������飬�����ͣ��������С�
		for( int i = 0 ;  i< matrix.length; i++){
			for(int j = 0 ; j < matrix[i].length; j++){
				matrix[i][j] = (int)(Math.random()*100);
			}
		}
		System.out.println(Arrays.toString(matrix[1]));
		
		
		
		
		


	}

}
