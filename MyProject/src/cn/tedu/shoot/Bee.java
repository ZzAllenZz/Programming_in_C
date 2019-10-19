package cn.tedu.shoot;

import java.awt.image.BufferedImage;
import java.util.Random;

public class Bee extends FlyingObject {
	private static BufferedImage[] images ;
	static{ //��image��ֵ��	
		images = new BufferedImage[5];
		for(int i = 0 ; i< images.length;i++){
			images[i] = loadImage("bee"+ i +".png");
			
		}
	}
	private int xSpeed ; //С�۷����y�����ƶ��ٶȣ�ֵԽ�󣬲���Խ���ƶ�Խ��
    private int ySpeed ;//С�۷����x�����ƶ��ٶ�
    private int awardType; //��������
    public Bee(){
    	super(60,50);
    	xSpeed = 1;
    	ySpeed = 2;
    	Random rand = new Random();
    	awardType = rand.nextInt(2);
    	
    }
    public void step(){
    	x += xSpeed; // x���������
    	y += ySpeed; // y����
    	if(x<= 0 || x>=World.WIDTH-this.width){
    		xSpeed *= -1 ;// ���为�����߸�����������������
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
