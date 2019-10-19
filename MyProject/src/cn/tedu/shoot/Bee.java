package cn.tedu.shoot;

import java.awt.image.BufferedImage;
import java.util.Random;

public class Bee extends FlyingObject {
	private static BufferedImage[] images ;
	static{ //给image赋值；	
		images = new BufferedImage[5];
		for(int i = 0 ; i< images.length;i++){
			images[i] = loadImage("bee"+ i +".png");
			
		}
	}
	private int xSpeed ; //小蜜蜂冲着y方向移动速度；值越大，步长越大，移动越快
    private int ySpeed ;//小蜜蜂冲着x方向移动速度
    private int awardType; //奖励类型
    public Bee(){
    	super(60,50);
    	xSpeed = 1;
    	ySpeed = 2;
    	Random rand = new Random();
    	awardType = rand.nextInt(2);
    	
    }
    public void step(){
    	x += xSpeed; // x向左或向右
    	y += ySpeed; // y向下
    	if(x<= 0 || x>=World.WIDTH-this.width){
    		xSpeed *= -1 ;// 正变负，或者负变正。（调换方向）
    	}
    	
    	
    }
	int index = 1;
	public BufferedImage getImage(){
		if(isLife()){
			return images[0];
		} else if (isDead()){
			if(index == images.length){
				state = REMOVE;
			}
			return images[index++];
		}
		return null;
	}

}
