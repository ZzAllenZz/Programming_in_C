package cn.tedu.shoot;

import java.awt.image.BufferedImage;

public class Hero extends FlyingObject{
	private static BufferedImage[] images ;
	static{ //给image赋值；
		images = new BufferedImage[2];
		for(int i = 0;i<images.length;i++){
			images[i] = loadImage("hero"+i+".png");
		}

	}
	private	int life ; 
	private int doubleFire;
	public Hero(){
		super(97,124,140,400);
		life = 3;
		doubleFire = 0;
				
	}
	public void moveTo(int x , int y){
		System.out.println("英雄机随着鼠标动了");
		
	}
	public void step(){
    
    }
	int index = 0 ;
	public BufferedImage getImage(){
		if(isLife()){
		
			return images[index++%images.length];
			/*
			 *                     index=0
			 * 10M,   images[0],   index=1;
			 * 20M,   images[1],   index=2;
			 * 30M,   images[0],   index=3;
			 * 40M,   images[1],   index=4;
			 * 
			 */
			
		}
		return null;
	}
    public Bullet[] shoot(){//英雄机发射子弹（生成子弹对象）
    	int xStep = this.width/4;
    	int yStep = 20 ;
    	if(doubleFire > 0 ){
    		Bullet[] bs = new Bullet[2];
    		bs[0] = new Bullet(this.x+xStep, this.y-yStep);
    		bs[1] = new Bullet(this.x+xStep*3, this.y-yStep);
    		doubleFire -= 2 ;
    		return bs;
    	}else{
    		Bullet[] bs = new Bullet[1];
    		bs[0] = new Bullet(this.x+xStep*2, this.y-yStep);
    		return bs;
    	}
    }

}
