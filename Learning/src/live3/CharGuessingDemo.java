package live3;
import java.util.Arrays;
import java.util.Scanner;

public class CharGuessingDemo {

	public static void main(String[] args) {
/*       �ѵ㣺1.��Ϊ����������generate�������� �����ĸ��test�����ж�λ�öԺ��ַ��Եĸ�����
 *           2.ȫ���д scan.next().toUpperCase();
 *             String str = scan.next().toUpperCase;
 *             str.euqals("EXIT"); �ж��ַ���
 *             str.length(); 
 *             str.toCharArray()
 *           3.����boolean[]���鶼�� false��true���ص㣬����һЩ��ǡ�e.g. boolean[] test
 *             ����int[]���������� e.g. int[] test
 *           4.����while��true��������
 *           5.����� site = (int)(Math.random()*base.length)
 * 
 * 
 * 
 * */
		char[] original = generate();
		System.out.println(Arrays.toString(original));

		int count = 0;
		int score = 100;
		do{
			Scanner scan = new Scanner(System.in);
			String str = scan.next().toUpperCase();
			while(str.length()!=5 ){
				if(str.equals("EXIT")){
					System.out.println("���˳�");
					return;
					}
				System.out.println("���볤�Ȳ�Ϊ5������������");
				str = scan.next().toUpperCase();
				count++;
			}
			

			char[] input = str.toCharArray();
			int[] result = test(original,input);
			if(result[1]== input.length){
				System.out.print("��ϲ�㣬�¶���,�÷�Ϊ"+score);
				break;
				
			} else{
				score -= 10;
				count++;
				System.out.println("û�¶ԣ� �ַ��¶�"+result[0]+"��, λ�ò¶�"+result[1]+"������ʣ"+(int)(10-count)+"��");
				
			}
			if(count>=10){
				System.out.println("game over");
				break;
			}
			scan.close();
			
		}while(true);
		
		
		
		
		
		
		
		

	}
	public static char[] generate(){
		char[] base = {'A','B','C', 'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		boolean[] check = new boolean[base.length];
		char[] original = new char[5];
		for(int i = 0 ; i<original.length; i++){
			int site;
			do{
				site = (int)(Math.random()*base.length);
			}while(check[site] == true);
			original[i] = base[site];
			check[site] = true ;
		}
		
		return original;
		
	}
	public static int[] test(char[] original, char[] input){
		int[] result = new int[2]; // 1:���Ŷԣ�2��λ�öԣ�
		for(int i =0; i<input.length;i++){
			for(int j =0; j<original.length;j++){
				if(input[i]==original[j]){
					result[0]++;
					if(i==j){
						result[1]++;
						}
					break;
				}
			}
		}
		return result;
		
	}
	

}
