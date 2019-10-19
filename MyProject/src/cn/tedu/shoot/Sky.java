package cn.tedu.shoot;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
public class Sky extends FlyingObject{
	private static BufferedImage image ;
	static{ //��image��ֵ��
		image = loadImage("background.png");	
	}
	private int y1; //�ڶ���ͼƬ��y���꣬����ͼ����
	private int speed ; //��ճ���y�����ƶ��ٶȣ�ֵԽ�󣬲���Խ���ƶ�Խ��
	public Sky(){
		super(World.WIDTH,World.HEIGHT,0,0);
		y1 = -World.HEIGHT ; 
		speed = 1 ;
	}
	public void step(){
    	y += speed;
    	y1 += speed;
    	if(y >= World.HEIGHT){
    		y = -World.HEIGHT;
    	}
    	if(y1 >= World.HEIGHT){
    		y1 = -World.HEIGHT;
    	}
    }
    public BufferedImage getImage(){
    	return image;
    }
    public void paintObject(Graphics g){
    	g.drawImage(getImage(), x, y, null);
    	g.drawImage(getImage(), x, y1, null);
    	
    }
	

}
