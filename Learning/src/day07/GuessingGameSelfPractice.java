package day07;
import java.util.Arrays;
import java.util.Scanner;

public class GuessingGameSelfPractice {
	/*
	 * ����:�������һ�����ظ�������ַ���A��Z.
	 * �����û������һ������ַ����飬
	 * �Ա�
	 * �жϣ�����
	 * ���ݽṹ��
	 * char[] chs
	 * char[] input
	 * int[] result �ԱȽ��
	 * int score ��������
	 * 
	 * ������
	 * 1.������������
	 * 2.�Աȵ��㷨
	 * 3.�����û�����Ͳ���Ҫһ���������㷨��
	 */

	public static void main(String[] args) {
		char[] chs = generate();
		System.out.println(chs);; //���ף�
		Scanner scan = new Scanner (System.in);
		int score = 0;
		int count = 0;
		while (true){
			System.out.println("�°ɣ�������������ظ�����ĸ");
			String str = scan.next().toUpperCase();
			if(str.equals("EXIT")){
				System.out.println("�´�������");
				break;
				
			}
			char [] input = str.toCharArray();
			
			int[] result = check(chs,input);
			if(result[1] == chs.length){
				score = 500 - 10* count;
				System.out.println("��ϲ�����ˣ��ܵ÷�Ϊ��" + score );
				break;
				
			}else{
				count++;
				System.out.println("�Բ������ˣ��ַ�����"+ result[0]+ ", λ�ö���"+ result[1]);
				continue;
				
			}
			
		}
		scan.close();


    }
    public static char[] generate(){
    	char[] letters = {'A','B','C','D','E','F','G','H',
    			'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} ;
    	boolean [] flags = new boolean[letters.length];
    	
    	char[] chs = new char[5];
 
    	for(int i = 0 ; i< chs.length; i++){
    		int index ;
    		do{
        		index = (int)(Math.random()*26) ;

    			
    		} while(flags[index] == true);
    		flags[index] = true;
    		chs[i] = letters[index] ;
    	}
    	return chs;
    }
    public static int[] check(char[] chs, char[] input){
    	int[] result = new int[2]; //result[0]�����ַ�������result[1] ����λ�ö�����
    	for( int i = 0 ; i< input.length; i++){
    		for(int j =0 ; j<chs.length;j++){
    			if( input[i] == chs [j]){
    				result[0] ++;
    				if(i == j){
    					result[1]++;
    				}
    				break;
    				
    			}
    		}
    	}
    	return result ; 
    }


}
