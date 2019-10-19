package cn.tedu.shoot;

import java.awt.image.BufferedImage;

public class Airplane extends FlyingObject {
	private static BufferedImage[] images ;
	static{ //给image赋值；
		images = new BufferedImage[4];
		for(int i =0; i<images.length;i++){
			images[i] = loadImage("airplane"+i+".png");
		}
		
	}

	private int speed ; //小敌机冲着y方向移动速度；值越大，步长越大，移动越快
    public Airplane(){
    	super(49,36);
    	speed = 2;
    }
    public void step(){
    	y += speed;
    }
    int index = 1;
    public BufferedImage getImage(){//重写getImage
    	if(isLife()){
    		return images[0];
    	}else if(isDead()){
    		if(index >= images.length){
    			state = REMOVE;
    		}
    		return images[index++];
    		
    	}
    	return null;
    	/*以后会实现，没个10MS，会再走一次，直到返回null。
    	 * index = 1
    	 * 10M 返回image[1], index=2;
    	 * 20M 返回image[2], index=3;
    	 * 30M 返回image[3], index=4;
    	 * 40M state = REMOVE, 返回image[4];
    	 * 50M return null;
    	 */
    }
}
