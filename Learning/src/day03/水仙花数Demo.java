package day03;


public class ˮ�ɻ���Demo {

	public static void main(String[] args) {
		//����Ƕ��ѭ����ɣ�
		
		/*for (int i = 100 ;i>= 100 && i<1000;i++){
	
			if (i== (Math.pow((i%10),3) + Math.pow((i/10)%10,3) + Math.pow((i/100), 3))){
				System.out.println(i);
				
			}
				
		}
		*/
		
		//��Ƕ�����
		for (int i = 100 ; i<1000;i++){
			int sum = 0;
			//j��ʾ�жϵ�����
			for(int j =i;j>0;j/=10){
				int tmp = j%10;
				sum += tmp*tmp*tmp;	
			}
			if(sum == i){
				System.out.println(i);
			}
			
		}
		
		
		
		

	}

}
