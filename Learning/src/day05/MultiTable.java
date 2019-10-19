package day05;

public class MultiTable {

	public static void main(String[] args) {
		
		int num = 1;
		for(;num <= 9;num++){
			
			for ( int i =1; i<= num;i++){
				System.out.print( i +"*"+ num+"="+ i*num+"\t");
			}
			System.out.println();
			
		}
		/*
		 * num =1 
		 * i=1, 1*1=1
		 * i=2, false
		 * 换行
		 * num= 2 
		 * i=1 1*2=2
		 * i=2 2*2=4
		 * i=3 false
		 * 换行
		 * num =3
		 * i=1 1*3=3
		 * i=2 2*3=6
		 * i=3 3*3=9
		 * i=4 false
		 * 换行
		 * num = 4 
		 * i=1 1*4 =4
		 * i=2 2*4=8
		 * i=3 3*4=12
		 * i=4 4*4=16
		 * i=5 false
		 * 换行
		 * num = 5
		 * i=1 1*5=5
		 * i=2 2*5=10
		 * i=3 3*5=15
		 * i=4 4*5=20
		 * i=5 5*5=25
		 * i=6 false
		 * 换行
		 * .........
		 * 
		 * 
		 */
		
			
		
	}

}
