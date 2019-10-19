package cn.tedu.shoot;

import java.awt.image.BufferedImage;

public class BigAirplane extends FlyingObject {
	private static BufferedImage[] images ;
	static{ //给image赋值；
		images = new BufferedImage[4];
		for(int i =0; i<images.length;i++){
			images[i] = loadImage("bigplane"+i+".png");
		}
		
	}

	private int speed ; //大敌机冲着y方向移动速度；值越大，步长越大，移动越快
    public BigAirplane(){
    	super(47,99);
    	speed = 2;
    }
    public void step(){
    	y += speed;
    }
    int index = 1 ;
    public BufferedImage getImage(){
    	if( isLife()){
    		return images[0];
    	}if (isDead()){
    		if(index == images.length){
    			state = REMOVE;
    		}
    		return images[index++];
    	}
    	return null;
    }
 

}
