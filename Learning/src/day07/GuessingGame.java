package day07;
import java.util.Scanner;

public class GuessingGame {
	//������
	/* 1.����һ���������
	 * 2.�����û���������
	 * 3.�Ƚϣ�������֣����˼���������λ�úͶԵĸ���
	 * 
	 */
	public static void main(String[] args) {
		char[] chs = generate();
		System.out.println(chs); //����
		Scanner scan = new Scanner(System.in);
		int score = 0 ; 
		int count = 0;
		while(true){
			String str = scan.next().toUpperCase();
			if ( str.equals("EXIT")){
				System.out.println("�´�������");
				break;
			}
			char[] input = str.toCharArray();
			int [] result = check(chs,input);
			if(result[1] == chs.length){
				score = 500 - 10* count;
				System.out.println("��ϲ��¶��ˣ��ܵ÷�Ϊ��"+ score);
				break;
				
			}else{
				System.out.println("����ˣ��ַ�����"+ result[0]+", λ�ö���" + result[1]);
				count ++;
				
				
			}
			
		}

		
		
		


	}


//��������ַ����� chs
    public static char[] generate(){
    	char[] chs = new char[5] ;
    	char[] letters = {'A','B','C','D','E','F','G','H','I','J',
    			'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    	boolean[] flags = new boolean[letters.length];//����һ����letterһһ��Ӧ��boolean���飬Ĭ�϶�Ϊfalse��
    	for(int i =0; i< chs.length;i++){
    		int index;
    		
    		do{
    			index = (int)(Math.random()*26);
    			
    		} while (flags[index] == true);
    		flags[index] = true ;
    		chs[i] = letters[index];
    		
    	
    	}
    	return chs;
    }
//�Աȣ������������chs���û���������input��
    public static int[] check (char[] chs,char[] input){
    	int[] result = new int[2]; //��ŶԱȽ����result[1]����λ�öԣ�result[0]�����ַ���
    	for(int i= 0 ; i< chs.length;i++){ //��chs���б���
    		for (int j = 0; j< input.length;j++){ //��input������б���
    			if(chs[i]==input[j]){//����ַ����ˣ��ַ��Լ�һ
    				result[0]++;
    				if(i==j){//λ�ö�
    					result[1]++;//λ�öԵ�ǰ�����ַ��ǶԵģ�������һ��Ƕ�׵�����
    				}
    				break;//����Ҫ�Ժ�ߵ��ڽ��бȽ�
    				
    			}
    			
    		}
    		
    	}
    	
    	return result;
    	
    }
}