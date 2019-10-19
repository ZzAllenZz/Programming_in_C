package cn.tedu.shoot;

import java.awt.image.BufferedImage;

public class Bullet extends FlyingObject {
	private static BufferedImage image ;
	static{ //��image��ֵ��
		image = loadImage("bullet.png");
	}
	private int speed ; //�ӵ�����y�����ƶ��ٶȣ�ֵԽ�󣬲���Խ���ƶ�Խ��
    public Bullet(int x, int y){
    	super(8,14,x,y); 
    	speed = 3;
    }
    public void step(){
    	y -= speed;
    }
    public BufferedImage getImage(){
    	if(isLife()){
    		return image;
    	} else if (isDead()){
    		state = REMOVE;
    	} 
    	return null ;
    }

}
