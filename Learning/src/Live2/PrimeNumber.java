package Live2;

public class PrimeNumber {

	public static void main(String[] args) {
		
		for(int i =2; i<= 100;i++){ // i�����жϵ�����
			int count =0 ;
			for(int j =2 ; j<=i; j++){
				//j �������
				//�ж��Ƿ��ܱ�����; 
				//����ܣ�ͳ�ƴ�����1
				if(i%j==0){
					count++;
				}
				
				
			}
			if(count ==1){
				System.out.println(i);
			}
			
		}
		


	}

}
