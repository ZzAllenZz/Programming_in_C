package cn.tedu.shoot;

import java.awt.image.BufferedImage;

public class Airplane extends FlyingObject {
	private static BufferedImage[] images ;
	static{ //��image��ֵ��
		images = new BufferedImage[4];
		for(int i =0; i<images.length;i++){
			images[i] = loadImage("airplane"+i+".png");
		}
		
	}

	private int speed ; //С�л�����y�����ƶ��ٶȣ�ֵԽ�󣬲���Խ���ƶ�Խ��
    public Airplane(){
    	super(49,36);
    	speed = 2;
    }
    public void step(){
    	y += speed;
    }
    int index = 1;
    public BufferedImage getImage(){//��дgetImage
    	if(isLife()){
    		return images[0];
    	}else if(isDead()){
    		if(index >= images.length){
    			state = REMOVE;
    		}
    		return images[index++];
    		
    	}
    	return null;
    	/*�Ժ��ʵ�֣�û��10MS��������һ�Σ�ֱ������null��
    	 * index = 1
    	 * 10M ����image[1], index=2;
    	 * 20M ����image[2], index=3;
    	 * 30M ����image[3], index=4;
    	 * 40M state = REMOVE, ����image[4];
    	 * 50M return null;
    	 */
    }
}
