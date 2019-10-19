package cn.tedu.shoot;

import java.awt.image.BufferedImage;

public class Bullet extends FlyingObject {
	private static BufferedImage image ;
	static{ //给image赋值；
		image = loadImage("bullet.png");
	}
	private int speed ; //子弹冲着y方向移动速度；值越大，步长越大，移动越快
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
