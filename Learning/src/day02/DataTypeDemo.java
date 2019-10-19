package day02;

public class DataTypeDemo {

	public static void main(String[] args) {
	
    int a = 5 ; 
    long  b = a ;
    int c = (int) b ;
    long d = 10000000000L;
    int e = (int)d ; // 会溢出
    double f = 45.876 ; 
    int g = (int) f ; // 会丢失，变成45
    System.out.println(g);
    short b1 = 6 ; 
    short b2 = 8 ; 
    short b3 = (short )( b1 + b2 );
    System.out.println(b3);
    
    System.out.println(2+'2'); //52 因为的2对应的字符码是50
    System.out.println('2'+'2'); // 100 50+50
    
    
    
    
		
		
		
		
		
		
		
		
		
		
	/*
	boolean b1 = true; 
	boolean b2 = false ; 
	 // boolean b3 = 36 ; 
	char c1 = '女' ; 
	char c2 = 'f' ; 
	char c3 = '3';
	char c4 = ' ';
	//char c5 = '';
	//char c6 = '女性' ;
	char c7 = 65;
	System.out.println(c7) ;
	char c8 = '\'' ; 
	System.out.println(c8);
	*/
			
	/*
	int 湖人 = 1 ; 
	System.out.println(湖人);
	char a =  67; 
	System.out.println(a);
	boolean b = true;
	System.out.println(b);
	*/		
		
	/*	
	//int a = 25 ; 
	//int b = 10000000000 ; 
	System.out.println(8/3);
	System.out.println (3/8);
	System.out.println(5.0/2);
	int c = 2147483647;
	c= c + 5 ;
	System.out.println(c);
	//long d = 10000000000000;
	long d = 10000000000L ; 
	long e = 1000000000 * 2* 10L ; 
	//long f = 1000000000*3 *10L ; 
	long f = 1000000000L *3 *10 ;
	System.out.println(e);
	System.out.println(f);
	/*long g = 1000000000*3 *10L
	System.out.println(g); 
	long h = System.currentTimeMillis();
	System.out.println(h);
	
	double pi = 3.1415926;
	double i = 6,j = 2.9 ;
	System.out.println(i-j);
	*/
	}

}
